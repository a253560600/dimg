/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2008-02-17
 * Description : a command line tool to convert RAW file to DNG
 *
 * Copyright (C) 2008-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

// Qt includes

#include <QCoreApplication>

// Local includes

#include "dngwriter.h"
#include "digikam_debug.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    if (argc != 2)
    {
        qCDebug(DIGIKAM_TESTS_LOG) << "raw2dng - RAW Camera Image to DNG Converter";
        qCDebug(DIGIKAM_TESTS_LOG) << "Usage: <rawfile>";

        return -1;
    }

    Digikam::DNGWriter dngProcessor;
    dngProcessor.setInputFile(QString::fromUtf8(argv[1]));
    int ret = dngProcessor.convert();

    return ret;
}
