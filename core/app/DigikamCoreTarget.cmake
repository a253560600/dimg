#
# Copyright (c) 2010-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
# Copyright (c) 2015      by Veaceslav Munteanu, <veaceslav dot munteanu90 at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

### digiKam core object library #################################################################################################

set(DIGIKAMCORE_OBJECTS

            ${CMAKE_CURRENT_SOURCE_DIR}/utils/digikam_debug.cpp

            $<TARGET_OBJECTS:core_dimg_obj>
            $<TARGET_OBJECTS:core_dmetadata_obj>
            $<TARGET_OBJECTS:core_jpegutils_obj>
            $<TARGET_OBJECTS:core_threadimageio_obj>
            $<TARGET_OBJECTS:core_dthread_obj>
            $<TARGET_OBJECTS:core_libraw_obj>
            $<TARGET_OBJECTS:core_rawengine_obj>
            $<TARGET_OBJECTS:core_dpluginsinterface_obj>
            $<TARGET_OBJECTS:core_libheif_obj>
            $<TARGET_OBJECTS:core_libde265_obj>
)

add_library(digikamcore
            SHARED
            ${DIGIKAMCORE_OBJECTS}
)

set_target_properties(digikamcore PROPERTIES
                      VERSION ${DIGIKAM_VERSION_SHORT}
                      SOVERSION ${DIGIKAM_VERSION_SHORT}
)

target_compile_definitions(digikamcore
                           PRIVATE
                           digikamcore_EXPORTS
)

# All codes from this target are exported with digikam_core_export.h header and DIGIKAM_EXPORT macro.
generate_export_header(digikamcore
                       BASE_NAME digikam
                       EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/utils/digikam_core_export.h"
)

# NOTE: all this target dependencies must be private and not exported to prevent inherited dependencies on external plugins.

target_link_libraries(digikamcore

                      PRIVATE

                      Qt5::Core
                      Qt5::Gui
                      Qt5::Xml
                      Qt5::Concurrent

                      # Required by CImg which use pthread internally.

                      ${CMAKE_THREAD_LIBS_INIT}
                      ${EXPAT_LIBRARY}

                      ${LCMS2_LIBRARIES} # filters

                      ${TIFF_LIBRARIES}
                      PNG::PNG
                      ${JPEG_LIBRARIES}
                      exiv2lib

                      ${FFMPEG_LIBRARIES}

                      ${OPENMP_LDFLAGS}

                      opencv_core
                      opencv_objdetect
                      opencv_imgproc
                      opencv_imgcodecs
                      opencv_dnn
                      opencv_ml
                      opencv_flann
)

if(X11_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          Qt5::X11Extras
                          ${X11_LIBRARIES}
    )

endif()

if(Jasper_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${JASPER_LIBRARIES}
    )

endif()

# LibLqr-1 library rules for content-aware filter
if(Lqr-1_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${LQR-1_LIBRARIES}
    )

endif()

if(X265_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${X265_LIBRARIES}
    )

endif()

if(LensFun_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${LENSFUN_LIBRARIES}
    )

endif()

if(ImageMagick_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${ImageMagick_LIBRARIES}
    )

endif()

# for nrfilter
if(OpenCV_FOUND)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${OpenCV_LIBRARIES}
    )

endif()

if(APPLE)

    target_link_libraries(digikamcore
                          PRIVATE
                          /System/Library/Frameworks/AppKit.framework
    )

endif()

if(WIN32)

    target_link_libraries(digikamcore
                          PRIVATE
                          wsock32
                          ws2_32
    )

endif()

if(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)

    target_link_libraries(digikamcore
                          PRIVATE
                          ${KVM_LIBRARY}
    )

endif()
