#
# Copyright (c) 2010-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
# Copyright (c) 2015      by Veaceslav Munteanu, <veaceslav dot munteanu90 at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

APPLY_COMMON_POLICIES()

# -----------------------------------------------------------------------------------
# Headers to configure

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/utils/digikam_version.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/utils/digikam_version.h)

# -----------------------------------------------------------------------------------
# Common includes rules

include_directories($<TARGET_PROPERTY:Qt5::Gui,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Xml,INTERFACE_INCLUDE_DIRECTORIES>
                    $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>)

# -----------------------------------------------------------------------------------
# Targets to build

include(DigikamCoreTarget.cmake)
