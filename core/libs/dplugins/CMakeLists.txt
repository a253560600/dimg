#
# Copyright (c) 2010-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

APPLY_COMMON_POLICIES()

include_directories($<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Gui,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Xml,INTERFACE_INCLUDE_DIRECTORIES>
)

set(libdpluginsinterface_SRCS

    ${CMAKE_CURRENT_SOURCE_DIR}/core/dplugin.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/core/dplugingeneric.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/core/dplugineditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/dpluginrawimport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/dplugindimg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/dpluginauthor.cpp
)

#if(ENABLE_QWEBENGINE)
#    set(libdpluginsinterface_SRCS
#        ${libdpluginsinterface_SRCS}
#        ${CMAKE_CURRENT_SOURCE_DIR}/webservices/webwidget_qwebengine.cpp
#       )
#else()
#    set(libdpluginsinterface_SRCS
#        ${libdpluginsinterface_SRCS}
#        ${CMAKE_CURRENT_SOURCE_DIR}/webservices/webwidget.cpp
#       )
#endif()

# Used by digikamcore
add_library(core_dpluginsinterface_obj OBJECT ${libdpluginsinterface_SRCS})

target_compile_definitions(core_dpluginsinterface_obj
                           PRIVATE
                           digikamcore_EXPORTS
)

# Parse O2 library code and rules at end, and compilation rules remove important Qt definitions.

if(WIN32)
    # NOTE: this O2 export symbols rule must be on top level.
    add_definitions(-DO2_DLL_EXPORT)
endif()
