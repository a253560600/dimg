# This file is mostly based on core/CMakeLists.txt,
# with some stuff taken from the original root CMakeLists.txt that it replaces.
# It should be kept up-to-date with relevant changes in those files.

cmake_minimum_required(VERSION 3.19)

set(DIGIKAM_MAJOR_VERSION "7")
set(DIGIKAM_MINOR_VERSION "2")
set(DIGIKAM_PATCH_VERSION "0")

# Suffix to add at end of version string. Usual values are:
# "-git"   : alpha code unstable from git. Do not use in production
# "-beta1" : beta1 release.
# "-beta2" : beta2 release.
# "-beta3" : beta3 release.
# "-rc"    : release candidate.
# ""       : final release. Can be used in production.
set(DIGIKAM_SUFFIX_VERSION "")

# ==============================================================================
# Set env. variables accordingly.

# NOTE: This string is used to set libdigikamcore and libdigikamdatabase SO version ID
set(DIGIKAM_VERSION_SHORT
    "${DIGIKAM_MAJOR_VERSION}.${DIGIKAM_MINOR_VERSION}.${DIGIKAM_PATCH_VERSION}"
)

set(DIGIKAM_VERSION_STRING
    "${DIGIKAM_VERSION_SHORT}${DIGIKAM_SUFFIX_VERSION}"
)

project(dimg-standalone
    VERSION ${DIGIKAM_VERSION_SHORT}
    LANGUAGES CXX C)

set(QT_MIN_VERSION        "5.9.0")
set(EXIV2_MIN_VERSION     "0.27.0")
set(OPENCV_MIN_VERSION    "3.3.0")
set(LENSFUN_MIN_VERSION   "0.2.6.0")      # For Lens auto-correction plugin

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/core/cmake/modules)

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(CheckFunctionExists)
include(FeatureSummary)

include(MacroBoolTo01)

macro(HEADER_DIRECTORIES return_list)

    file(GLOB_RECURSE new_list *.h)
    set(dir_list "")

    foreach(file_path ${new_list})

        get_filename_component(dir_path ${file_path} PATH)
        set(dir_list ${dir_list} ${dir_path})

    endforeach()

    list(REMOVE_DUPLICATES dir_list)
    set(${return_list} ${dir_list})

endmacro()

macro(kde_enable_exceptions)
endmacro()

macro(DISABLE_GCC_COMPILER_WARNINGS)
endmacro()

macro(DISABLE_CLANG_COMPILER_WARNINGS)
endmacro()

macro(REMOVE_GCC_COMPILER_WARNINGS)
endmacro()

macro(APPLY_COMMON_POLICIES)

    if(POLICY CMP0063)
        # C++ symbols visibility policy introduced in CMake version 3.3
        # Details: https://cmake.org/cmake/help/git-stage/policy/CMP0063.html
        cmake_policy(SET CMP0063 NEW)
    endif()

    if(POLICY CMP0068)
        # MacOS RPATH settings policy introduced in CMake version 3.9
        # Details: https://cmake.org/cmake/help/git-stage/policy/CMP0068.html
        cmake_policy(SET CMP0068 NEW)
    endif()

    if(POLICY CMP0071)
        # Automoc/autouic files handling introduced in CMake version 3.10
        # Details: https://cmake.org/cmake/help/git-stage/policy/CMP0071.html
        cmake_policy(SET CMP0071 NEW)
    endif()

    if(POLICY CMP0092)
        # MSVC warnings flag rules introduced in CMake version 3.16
        # Details: https://cmake.org/cmake/help/git-stage/policy/CMP0092.html
        cmake_policy(SET CMP0092 NEW)
    endif()

endmacro()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED
             NO_MODULE COMPONENTS
             Concurrent
             Core
             Gui
             Xml
)

set(JPEG_LIB_VERSION 84)
find_package(JPEG REQUIRED)

set(DIGIKAM_LIBJPEG_DIR libjpeg/${JPEG_LIB_VERSION})
message(STATUS "Using libjpeg sub-directory: ${DIGIKAM_LIBJPEG_DIR}")

find_package(TIFF)
find_package(PNG)
find_package(LCMS2)
find_package(Threads)  # For DNGWriter and LibRaw which needs native threads support.
find_package(X265)     # For HEIF encoding support.

if(NOT X265_FOUND)
    set(X265_LIBRARIES "")
endif()

find_package(exiv2 REQUIRED)

find_package(OpenCV COMPONENTS core objdetect imgproc imgcodecs dnn flann PATHS /usr/local)

find_package(PkgConfig)
find_package(Jasper)                               # For JPEG 2000 support.
find_package(Eigen3)                               # For Refocus tool.
find_package(ImageMagick COMPONENTS Magick++ MagickCore)

if(ImageMagick_Magick++_FOUND)
    add_definitions(${ImageMagick_Magick++_DEFINITIONS})
endif()

# For LibRaw
if(WIN32)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)
endif()

include(MacroOpenMP)
DETECT_OPENMP()

# For Monitor Profiles management with LCMS
find_package(X11)

if(X11_FOUND)
    find_package(Qt5 ${QT_MIN_VERSION} NO_MODULE COMPONENTS X11Extras)
    set(HAVE_X11 TRUE)
else()
    set(HAVE_X11 FALSE)
endif()

if(JPEG_FOUND)

    # JPEG lib version is done on top level through MacroJPEG.cmake

    if (${JPEG_LIB_VERSION} LESS 80)

        set(JPEG8_FOUND FALSE)

    else()

        set(JPEG8_FOUND TRUE)

    endif()

endif()

# -- Check dependencies for libraw ---------------------------------------------

message(STATUS "")
message(STATUS "--------------------------------------------------")
message(STATUS "digiKam RawEngine dependencies checks:")
message(STATUS "")

include(MacroOpenMP)
DETECT_OPENMP()

if(OPENMP_FOUND)

    message(STATUS "RawEngine will be compiled with OpenMP support")

else()

    # to force libraw to use OpenMP with Macports and MXE.
    if (APPLE OR MINGW)

        add_definitions(-DLIBRAW_FORCE_OPENMP)
        set(OPENMP_FOUND ON)
        message(STATUS "RawEngine will be compiled with OpenMP support")

    else()

        message(STATUS "RawEngine will not be compiled with OpenMP support")

    endif()

endif()

# Flag to use libjasper with LibRaw RedCine codec

if(Jasper_FOUND)

    add_definitions(-DUSE_JASPER)
    include_directories(${JASPER_INCLUDE_DIR})
    message(STATUS "RawEngine will be compiled with RedCine codec")

else()

    message(STATUS "RawEngine will not be compiled with RedCine codec")

endif()

# JPEG library check

message(STATUS "Looking for LibJpeg")

if(JPEG_FOUND)

    # JPEG lib version is done on top level through MacroJPEG.cmake

    if (${JPEG_LIB_VERSION} LESS 80)

        set(JPEG8_FOUND FALSE)

    else()

        set(JPEG8_FOUND TRUE)

    endif()

endif()

# Flag to use libjpeg with LibRaw DNG lossy codec

if(JPEG8_FOUND)

    add_definitions(-DUSE_JPEG)
    add_definitions(-DUSE_JPEG8)
    include_directories(${JPEG_INCLUDE_DIR})
    message(STATUS "RawEngine will be compiled with DNG lossy codec")

else()

    message(STATUS "RawEngine will not be compiled with DNG lossy codec")

endif()

message(STATUS "Looking for PThreads")
set(PTHREADS_FOUND (CMAKE_USE_PTHREADS_INIT OR CMAKE_USE_WIN32_THREADS_INIT))

# Registration of Libraw configuration to a dedicated header

MACRO_BOOL_TO_01(JPEG8_FOUND  LIBRAW_USE_DNGLOSSYCODEC)
MACRO_BOOL_TO_01(OPENMP_FOUND LIBRAW_USE_OPENMP)
MACRO_BOOL_TO_01(Jasper_FOUND LIBRAW_USE_REDCINECODEC)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/libs/rawengine/libraw/libraw_config.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/core/libs/rawengine/libraw/libraw_config.h)

MACRO_BOOL_TO_01(KF5Sane_FOUND                HAVE_KSANE)
MACRO_BOOL_TO_01(KF5FileMetaData_FOUND        HAVE_KFILEMETADATA)
MACRO_BOOL_TO_01(KF5CalendarCore_FOUND        HAVE_KCALENDAR)
MACRO_BOOL_TO_01(KF5Notifications_FOUND       HAVE_KNOTIFICATIONS)
MACRO_BOOL_TO_01(KF5NotifyConfig_FOUND        HAVE_KNOTIFYCONFIG)
MACRO_BOOL_TO_01(KF5KIO_FOUND                 HAVE_KIO)
MACRO_BOOL_TO_01(KF5IconThemes_FOUND          HAVE_KICONTHEMES)
MACRO_BOOL_TO_01(LensFun_FOUND                HAVE_LENSFUN)
MACRO_BOOL_TO_01(Lqr-1_FOUND                  HAVE_LIBLQR_1)
MACRO_BOOL_TO_01(Gphoto2_FOUND                HAVE_GPHOTO2)
MACRO_BOOL_TO_01(Jasper_FOUND                 HAVE_JASPER)
MACRO_BOOL_TO_01(Eigen3_FOUND                 HAVE_EIGEN3)
MACRO_BOOL_TO_01(Marble_FOUND                 HAVE_MARBLE)
MACRO_BOOL_TO_01(ENABLE_AKONADICONTACTSUPPORT HAVE_AKONADICONTACT)
MACRO_BOOL_TO_01(ENABLE_MYSQLSUPPORT          HAVE_MYSQLSUPPORT)
MACRO_BOOL_TO_01(ENABLE_INTERNALMYSQL         HAVE_INTERNALMYSQL)
MACRO_BOOL_TO_01(ENABLE_MEDIAPLAYER           HAVE_MEDIAPLAYER)
MACRO_BOOL_TO_01(ENABLE_DBUS                  HAVE_DBUS)
MACRO_BOOL_TO_01(ENABLE_APPSTYLES             HAVE_APPSTYLE_SUPPORT)
MACRO_BOOL_TO_01(ENABLE_QWEBENGINE            HAVE_QWEBENGINE)
MACRO_BOOL_TO_01(ENABLE_DRMINGW               HAVE_DRMINGW)
MACRO_BOOL_TO_01(ImageMagick_Magick++_FOUND   HAVE_IMAGE_MAGICK)
MACRO_BOOL_TO_01(X265_FOUND                   HAVE_X265)
MACRO_BOOL_TO_01(Qt5XmlPatterns_FOUND         HAVE_QTXMLPATTERNS)
MACRO_BOOL_TO_01(CCACHE_FOUND                 HAVE_CCACHE)

# Set config files accordingly with optional dependencies

configure_file(core/app/utils/digikam_config.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/core/app/utils/digikam_config.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/app/utils/digikam_opencv.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/core/app/utils/digikam_opencv.h)

    # ==========================================================================
    # To prevent warnings from M$ compiler

    if(WIN32 AND MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(-D_ATL_SECURE_NO_WARNINGS)
        add_definitions(-D_AFX_SECURE_NO_WARNINGS)
    endif()

    # translations catalog
    add_definitions(-DTRANSLATION_DOMAIN=\"digikam\")

    # NOTE: with libpgf 6.11.24 OpenMP is not very well supported. We disable
    # it to be safe. See B.K.O #273765 for details.
    add_definitions(-DLIBPGF_DISABLE_OPENMP)

    # Enforce modern Qt code
    add_definitions(-DQT_DEPRECATED_WARNINGS
                    -DQT_USE_QSTRINGBUILDER
                    -DQT_NO_CAST_TO_ASCII
                    -DQT_NO_CAST_FROM_ASCII
                    -DQT_NO_CAST_FROM_BYTEARRAY
                    -DQT_NO_URL_CAST_FROM_STRING
                    -DQT_STRICT_ITERATORS
                    -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
                    -DQT_DEPRECATED_WARNINGS_SINCE=0x060000
#                    -DQT_DISABLE_DEPRECATED_BEFORE=0x050E00
#                    -DQT_NO_FOREACH
#                    -DQT_NO_KEYWORDS
    )

    # ==========================================================================
    # Includes rules

    include_directories(shims)

    # Recursively get all directories which contain header files
    set(DK_INCLUDES_ALL "")

    HEADER_DIRECTORIES(DK_LOCAL_INCLUDES_RAW)

    # This macro will set all paths which do not contain libjpeg-
    # We will add later the directory we need

    foreach(var ${DK_LOCAL_INCLUDES_RAW})
        string(REGEX MATCH "libjpeg/" item ${var})
        if(item STREQUAL "")
            list(APPEND DK_LOCAL_INCLUDES ${var})
        endif()
    endforeach()

    set(DK_LOCAL_INCLUDES ${DK_LOCAL_INCLUDES}
                          core/libs/jpegutils/${DIGIKAM_LIBJPEG_DIR})

    include_directories(${DK_LOCAL_INCLUDES})

    # for config headers digikam_version.h digikam_gitversion.h digikam_config.h
    # digikam_dbconfig.h digikam_opencv.h
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/core/app/utils)

    include_directories(${OpenCV_INCLUDE_DIRS})

    # for libheif version header
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/core/libs/heifutils)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/libs/heifutils)

    if(ImageMagick_FOUND)
        include_directories(${ImageMagick_INCLUDE_DIRS})
    endif()

add_subdirectory(core/app)
add_subdirectory(core/libs/rawengine)
add_subdirectory(core/libs/dplugins)
add_subdirectory(core/libs/dimg)
add_subdirectory(core/libs/threads)
add_subdirectory(core/libs/threadimageio)
add_subdirectory(core/libs/heifutils)
add_subdirectory(core/libs/jpegutils)
add_subdirectory(core/libs/metadataengine)
add_subdirectory(core/dplugins/dimg)
