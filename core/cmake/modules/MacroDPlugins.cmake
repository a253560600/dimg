# Some useful macros for printing status information
#
# Copyright (c) 2010-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

APPLY_COMMON_POLICIES()

include(CMakeParseArguments)

# -------------------------------------------------------------------------

# This macro implement the rules to compile and link a DImg DPlugin with extra arguments.
#
# Usage: DIGIKAM_ADD_DIMG_PLUGIN(NAME    _plugin_name_
#                                SOURCE  _plugin_sources_
#                                DEPENDS _plugin_dependencies_)
#
# With: _plugin_name_ the literal name of the plugin (mandatory).
#       _plugin_sources_ the list of source codes to compile (mandatory).
#       _plugin_dependencies_ the list of dependencies to link (optional).
#
# Note: by default a DImg plugin is linked with digikamcore shared library.
#
# This macro will generate a plugin library with this pattern as file name:
# DImg_${_pluginname_}_Plugin
#
macro(DIGIKAM_ADD_DIMG_PLUGIN)

    set(_OPTIONS_ARGS)
    set(_ONE_VALUE_ARGS)
    set(_MULTI_VALUE_ARGS NAME SOURCES DEPENDS)

    cmake_parse_arguments(_parse_results "${_OPTIONS_ARGS}"
                                         "${_ONE_VALUE_ARGS}"
                                         "${_MULTI_VALUE_ARGS}"
                                         ${ARGN}
    )

    # Mandatory
    if(NOT _parse_results_NAME)
        message(FATAL_ERROR "DImg plugin name is required.")
    endif()

    if(NOT _parse_results_SOURCES)
        message(FATAL_ERROR "DImg plugin sources is required.")
    endif()

    if(APPLE)
        set(_extra_deps /System/Library/Frameworks/AppKit.framework)
    endif()

    add_library(DImg_${_parse_results_NAME}_Plugin
                MODULE ${_parse_results_SOURCES})

    target_link_libraries(DImg_${_parse_results_NAME}_Plugin

                          PRIVATE

                          digikamcore

                          Qt5::Core
                          Qt5::Gui
                          Qt5::Xml

                          ${_parse_results_DEPENDS}
                          ${_extra_deps}
    )

    install(TARGETS DImg_${_parse_results_NAME}_Plugin
            DESTINATION ${PLUGIN_INSTALL_DIR}/digikam/dimg
    )

    if(APPLE)
        install(FILES "$<TARGET_FILE:DImg_${_parse_results_NAME}_Plugin>.dSYM"
                DESTINATION ${PLUGIN_INSTALL_DIR}/digikam/dimg
                CONFIGURATIONS Debug RelWithDebInfo
        )
    endif()

endmacro()
