#
# Copyright (c) 2015-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

APPLY_COMMON_POLICIES()

include(MacroDPlugins)

include_directories($<TARGET_PROPERTY:Qt5::Gui,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Widgets,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>

                    $<TARGET_PROPERTY:KF5::ConfigCore,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:KF5::I18n,INTERFACE_INCLUDE_DIRECTORIES>
)

set(dimgpgfplugin_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgpgfplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgpgfloader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgpgfloader_load.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dimgpgfloader_save.cpp
)

DIGIKAM_ADD_DIMG_PLUGIN(NAME    PGF
                        SOURCES ${dimgpgfplugin_SRCS}
)
