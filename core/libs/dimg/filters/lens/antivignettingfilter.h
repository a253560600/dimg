/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2005-05-25
 * Description : Antivignetting threaded image filter.
 *
 * Copyright (C) 2005-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_ANTI_VIGNETTING_FILTER_H
#define DIGIKAM_ANTI_VIGNETTING_FILTER_H

// Local includes

#include "dimgthreadedfilter.h"
#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_EXPORT AntiVignettingContainer
{

public:

    explicit AntiVignettingContainer()
      : addvignetting(true),
        density      (2.0),
        power        (1.0),
        innerradius  (1.0),
        outerradius  (1.0),
        xshift       (0.0),
        yshift       (0.0)
    {
    };

    ~AntiVignettingContainer()
    {
    };

public:

    bool   addvignetting;

    double density;
    double power;
    double innerradius;
    double outerradius;
    double xshift;
    double yshift;
};

// -----------------------------------------------------------------------------------------------

class DIGIKAM_EXPORT AntiVignettingFilter : public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit AntiVignettingFilter(QObject* const parent = nullptr);
    explicit AntiVignettingFilter(DImg* const orgImage, QObject* const parent = nullptr,
                                  const AntiVignettingContainer& settings = AntiVignettingContainer());

    ~AntiVignettingFilter()                                override;

    static QString FilterIdentifier()
    {
        return QLatin1String("digikam:AntiVignettingFilter");
    }

    static QString DisplayableName();

    static QList<int> SupportedVersions()
    {
        return QList<int>() << 1;
    }

    static int CurrentVersion()
    {
        return 1;
    }

    void readParameters(const FilterAction& action)        override;

    QString filterIdentifier()                       const override
    {
        return FilterIdentifier();
    }

    FilterAction filterAction()                            override;

private:

    void           filterImage()                           override;

    double         hypothenuse(double x, double y);
    uchar          clamp8bits(double x);
    unsigned short clamp16bits(double x);
    double         attenuation(double r1, double r2, double distcenter);
    double         real_attenuation(double r1, double r2, double distcenter);

private:

    AntiVignettingContainer m_settings;
};

} // namespace Digikam

#endif // DIGIKAM_ANTI_VIGNETTING_FILTER_H
