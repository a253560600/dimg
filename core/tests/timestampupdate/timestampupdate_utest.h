/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2015
 * Description : a test for timestamp trigger for re-reading metadata from image
 *
 * Copyright (C) 2015 by Kristian Karl <kristian dot hermann dot karl at gmail dot com>
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

#ifndef DIGIKAM_TIME_STAMP_UPDATE_UTEST_H
#define DIGIKAM_TIME_STAMP_UPDATE_UTEST_H

// Qt includes

#include <QTest>

class TimeStampUpdateTest : public QObject
{
    Q_OBJECT

public:

    explicit TimeStampUpdateTest(QObject* const parent = nullptr)
        : QObject(parent)
    {
    }

private Q_SLOTS:

    void initTestCase();
    void cleanupTestCase();
    void cleanup();
    void testRescanImageIfModifiedSet2True();
    void testRescanImageIfModifiedSet2False();

private:

    QString tempFileName(const QString& purpose) const;
    QString tempFilePath(const QString& purpose) const;

private:

    QString          dbFile;
    QList<qlonglong> ids;
};

#endif // DIGIKAM_TIME_STAMP_UPDATE_UTEST_H
