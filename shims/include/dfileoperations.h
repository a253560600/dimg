/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Copyright (C) 2014-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#pragma once

#ifndef Q_CC_MSVC
#   include <utime.h>
#else
#   include <sys/utime.h>
#endif
#include <QString>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <qplatformdefs.h>

namespace Digikam
{
    class DFileOperations
    {
    public:
        static bool copyModificationTime(const QString& srcFile, const QString& dstFile)
        {
#ifdef Q_OS_WIN64
            struct __utimbuf64 ut;
            struct __stat64    st;
            int ret = _wstat64((const wchar_t*)srcFile.utf16(), &st);
#elif defined Q_OS_WIN
            struct _utimbuf    ut;
            struct _stat       st;
            int ret = _wstat((const wchar_t*)srcFile.utf16(), &st);
#else
            struct utimbuf     ut;
            QT_STATBUF         st;
            int ret = QT_STAT(srcFile.toUtf8().constData(), &st);
#endif

            if (ret == 0)
            {
                ut.modtime = st.st_mtime;
                ut.actime  = st.st_atime;
#ifdef Q_OS_WIN64
                ret        = _wutime64((const wchar_t*)dstFile.utf16(), &ut);
#elif defined Q_OS_WIN
                ret        = _wutime((const wchar_t*)dstFile.utf16(), &ut);
#else
                ret        = ::utime(dstFile.toUtf8().constData(), &ut);
#endif
            }

            if (ret != 0)
            {
                qWarning() << "Failed to restore modification time for file" << dstFile;
                return false;
            }

            return true;
        }
        static bool setModificationTime(const QString& srcFile,
                                                  const QDateTime& dateTime)
        {

        #ifdef Q_OS_WIN64

            struct __utimbuf64 ut;
            struct __stat64    st;
            int ret = _wstat64((const wchar_t*)srcFile.utf16(), &st);

        #elif defined Q_OS_WIN

            struct _utimbuf    ut;
            struct _stat       st;
            int ret = _wstat((const wchar_t*)srcFile.utf16(), &st);

        #else

            struct utimbuf     ut;
            QT_STATBUF         st;
            int ret = QT_STAT(srcFile.toUtf8().constData(), &st);

        #endif

            if (ret == 0)
            {
                ut.modtime = dateTime.toSecsSinceEpoch();
                ut.actime  = st.st_atime;

        #ifdef Q_OS_WIN64

                ret        = _wutime64((const wchar_t*)srcFile.utf16(), &ut);

        #elif defined Q_OS_WIN

                ret        = _wutime((const wchar_t*)srcFile.utf16(), &ut);

        #else

                ret        = ::utime(srcFile.toUtf8().constData(), &ut);

        #endif

            }

            if (ret != 0)
            {
                qWarning() << "Failed to set modification time for file" << srcFile;
                return false;
            }

            return true;
        }
    };
}
