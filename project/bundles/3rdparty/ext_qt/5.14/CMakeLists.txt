# Script to build Qt for digiKam bundle.
#
# Copyright (c) 2015-2021 by Gilles Caulier  <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(EXTPREFIX_qt "${EXTPREFIX}")

IF(NOT ENABLE_QTWEBENGINE)
    SET(DROP_QTWEBENGINE_DEPS
        -skip qtwebengine                 # No need Chromium browser support (QtWebkit instead)
        -skip qtwebchannel                # QtWebChannel support ==> QWebEngine dependency
        -skip qtquickcontrols             # QtQuick support      ==> QWebEngine dependency
        )
ENDIF()

ExternalProject_Add(ext_qt
    DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
    URL https://download.qt.io/archive/qt/5.14/5.14.2/single/qt-everywhere-src-5.14.2.tar.xz
    URL_MD5 b3d2b6d00e6ca8a8ede6d1c9bdc74daf

    PATCH_COMMAND ${PATCH_COMMAND} -p1 -i ${CMAKE_CURRENT_SOURCE_DIR}/qt-appimage-support.patch
               && ${PATCH_COMMAND} -p1 -i ${CMAKE_CURRENT_SOURCE_DIR}/qt-fix-jp2handler.patch

#    PATCH_COMMAND ${PATCH_COMMAND} -p1 -i ${CMAKE_CURRENT_SOURCE_DIR}/qt-icu-hack.patch &&
#                  ${PATCH_COMMAND} -p1 -i ${CMAKE_CURRENT_SOURCE_DIR}/qt-appimage-support.patch

    CONFIGURE_COMMAND <SOURCE_DIR>/configure
                  ICU_LIBS="-I${EXTPREFIX}/local/ -L${EXTPREFIX}/local/lib -licui18n -licuuc -licudata"
                  -prefix ${EXTPREFIX_qt}
                  -verbose
                  -release
                  -opensource
                  -confirm-license
                  -sql-sqlite                       # Compile Sqlite SQL plugin
                  -sql-mysql                        # Compile Mysql SQL plugin
                  -iconv                            # International string conversion
                  -fontconfig
                  -system-freetype                  # Use system font rendering lib https://doc.qt.io/qt-5/qtgui-attribution-freetype.html
                  -openssl-linked                   # hard link ssl libraries
                  -nomake tests                     # Do not build test codes
                  -nomake examples                  # Do not build basis example codes
                  -no-compile-examples              # Do not build extra example codes
                  -no-icu                           # ICU do not work at run-time (FIXME later)
                  -no-qml-debug
                  -no-mtdev
                  -no-journald
                  -no-syslog
                  -no-tslib
                  -no-directfb
                  -no-linuxfb
                  -no-libproxy
                  -no-pch
                  -qt-zlib
                  -qt-pcre
                  -qt-harfbuzz
                  -qt-xcb
                  -skip qt3d                        # 3D core
                  -skip qtactiveqt                  # No need ActiveX support
                  -skip qtandroidextras             # For embeded devices only
                  -skip qtcharts                    # No need data models charts support
                  -skip qtconnectivity              # For embeded devices only
                  -skip qtdatavis3d                 # no need 3D data visualizations support
                  -skip qtdoc                       # No need documentation
                  -skip qtgamepad                   # No need gamepad hardware support.
                  -skip qtgraphicaleffects          # No need Advanced graphical effects in GUI
                  -skip qtlocation                  # No need geolocation
                  -skip qtlottie                    # No need Adobe QtQuick After Effect animations integration
                  -skip qtmacextras                 # For MacOS devices only
                  -skip qtmultimedia                # No need multimedia support (replaced by QtAV+ffmpeg)
                  -skip qtnetworkauth               # No need network authentification support.
                  -skip qtpurchasing                # No need in-app purchase of products support
                  -skip qtquickcontrols2            # QtQuick support for QML
                  -skip qtremoteobjects             # No need sharing QObject properties between processes support
                  -skip qtscript                    # No need scripting (deprecated)
                  -skip qtscxml                     # No need SCXML state machines support
                  -skip qtsensors                   # For embeded devices only
                  -skip qtserialbus                 # No need serial bus support
                  -skip qtserialport                # No need serial port support
                  -skip qtspeech                    # No need speech synthesis support
                  -skip qtvirtualkeyboard           # No need virtual keyboard support
                  -skip qtwebglplugin               # No need browser OpenGL extention support
                  -skip qtwebsockets                # No need websocket support
                  -skip qtwebview                   # QML extension for QWebEngine
                  -skip qtwinextras                 # For Windows devices only
                  ${DROP_QTWEBENGINE_DEPS}

    # Exemple of code to install only one Qt module for hacking purpose (aka qtbase here)
    #BUILD_COMMAND cd <SOURCE_DIR> && $(MAKE) module-qtbase
    #INSTALL_COMMAND cd <SOURCE_DIR> && $(MAKE) module-qtbase-install_subtargets

    UPDATE_COMMAND ""
    BUILD_IN_SOURCE 1
    ALWAYS 0
)
