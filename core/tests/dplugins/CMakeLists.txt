#
# Copyright (c) 2010-2021, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# =======================================================

APPLY_COMMON_POLICIES()

include_directories(
    $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:Qt5::Gui,INTERFACE_INCLUDE_DIRECTORIES>
)

macro(DPLUGINS_BUILD_TOOL)

    set(_filename ${ARGV0})
    string(REPLACE "." ";" _temp ${_filename})
    list(GET _temp 0 _target)

    set(${_target}_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${_filename})

    add_executable(${_target} ${${_target}_SRCS})

    target_link_libraries(${_target}
                          digikamcore

                          ${COMMON_TEST_LINK}
    )

endmacro()

DPLUGINS_BUILD_TOOL(loadandrun_generic_gui.cpp)
DPLUGINS_BUILD_TOOL(confview_generic_gui.cpp)
