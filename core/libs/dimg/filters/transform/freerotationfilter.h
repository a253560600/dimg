/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2005-07-18
 * Description : Free rotation threaded image filter.
 *
 * Copyright (C) 2004-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2009-2010 by Andi Clemens <andi dot clemens at gmail dot com>
 * Copyright (C) 2010      by Martin Klapetek <martin dot klapetek at gmail dot com>
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

#ifndef DIGIKAM_FREE_ROTATION_FILTER_H
#define DIGIKAM_FREE_ROTATION_FILTER_H

// Qt includes

#include <QSize>
#include <QColor>

// Local includes

#include "digikam_export.h"
#include "dimgthreadedfilter.h"

namespace Digikam
{

class DIGIKAM_EXPORT FreeRotationContainer
{
public:

    enum AutoCropTypes
    {
        NoAutoCrop = 0,
        WidestArea,
        LargestArea
    };

public:

    FreeRotationContainer()
      : antiAlias(true),
        autoCrop(NoAutoCrop),
        orgW(0),
        orgH(0),
        angle(0.0),
        backgroundColor(Qt::black)
    {
    };

    ~FreeRotationContainer()
    {
    };

public:

    bool   antiAlias;

    int    autoCrop;
    int    orgW;
    int    orgH;

    double angle;

    QSize  newSize;

    QColor backgroundColor;
};

// -----------------------------------------------------------------------------------------

class DIGIKAM_EXPORT FreeRotationFilter : public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit FreeRotationFilter(QObject* const parent = nullptr);
    explicit FreeRotationFilter(DImg* const orgImage, QObject* const parent = nullptr,
                                const FreeRotationContainer& settings=FreeRotationContainer());

    ~FreeRotationFilter() override;

    QSize getNewSize() const;

    static double calculateAngle(int x1, int y1, int x2, int y2);
    static double calculateAngle(const QPoint& p1, const QPoint& p2);

    static QString          FilterIdentifier()
    {
        return QLatin1String("digikam:FreeRotationFilter");
    }

    static QString          DisplayableName();

    static QList<int>       SupportedVersions()
    {
        return QList<int>() << 1;
    }

    static int              CurrentVersion()
    {
        return 1;
    }

    QString         filterIdentifier()                          const override
    {
        return FilterIdentifier();
    }

    FilterAction    filterAction()                                    override;
    void                    readParameters(const FilterAction& action)        override;

private:

    void        filterImage()                                                 override;
    inline int  setPosition (int Width, int X, int Y);
    inline bool isInside (int Width, int Height, int X, int Y);

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_FREE_ROTATION_FILTER_H
