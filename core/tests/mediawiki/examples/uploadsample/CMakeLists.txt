#
# Copyright (c) 2010-2021, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

APPLY_COMMON_POLICIES()

set(uploadsample_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
)

qt5_wrap_ui(uploadsample_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

add_executable(uploadsample_gui
               ${uploadsample_SRCS}
)

target_link_libraries(uploadsample_gui

                      PRIVATE

                      digikamcore
                      mediawikibackend

                      ${COMMON_TEST_LINK}
)

