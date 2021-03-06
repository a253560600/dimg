#
# Copyright (c) 2015-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

APPLY_COMMON_POLICIES()

include(MacroDPlugins)

include_directories($<TARGET_PROPERTY:Qt5::Gui,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>
)

set(dimgjpeg2000plugin_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgjpeg2000plugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgjpeg2000loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgjpeg2000loader_load.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgjpeg2000loader_save.cpp
)

DIGIKAM_ADD_DIMG_PLUGIN(NAME    JPEG2000
                        SOURCES ${dimgjpeg2000plugin_SRCS}
                        DEPENDS ${JASPER_LIBRARIES}
)
