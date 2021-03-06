/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2012-02-05
 * Description : film color negative inverter filter
 *
 * Copyright (C) 2012 by Matthias Welwarsky <matthias at welwarsky dot de>
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

#ifndef DIGIKAM_FILM_FILTER_H
#define DIGIKAM_FILM_FILTER_H

// Qt includes

#include <QString>
#include <QSharedPointer>

// Local includes

#include "dimgthreadedfilter.h"
#include "levelsfilter.h"
#include "cbfilter.h"

namespace Digikam
{

class DIGIKAM_EXPORT FilmContainer
{
public:

    enum CNFilmProfile
    {
        CNNeutral = 0,
        CNKodakGold100,
        CNKodakGold200,
        CNKodakEktar100,
        CNKodakProfessionalPortra160NC,
        CNKodakProfessionalPortra160VC,
        CNKodakProfessionalPortra400NC,
        CNKodakProfessionalPortra400VC,
        CNKodakProfessionalPortra800Box,
        CNKodakProfessionalPortra800P1,
        CNKodakProfessionalPortra800P2,
        CNKodakProfessionalNewPortra160,
        CNKodakProfessionalNewPortra400,
        CNKodakFarbwelt100,
        CNKodakFarbwelt200,
        CNKodakFarbwelt400,
        CNKodakRoyalGold400,
        CNAgfaphotoVistaPlus200,
        CNAgfaphotoVistaPlus400,
        CNFujicolorPro160S,
        CNFujicolorPro160C,
        CNFujicolorNPL160,
        CNFujicolorPro400H,
        CNFujicolorPro800Z,
        CNFujicolorSuperiaReala,
        CNFujicolorSuperia100,
        CNFujicolorSuperia200,
        CNFujicolorSuperiaXtra400,
        CNFujicolorSuperiaXtra800,
        CNFujicolorTrueDefinition400,
        CNFujicolorSuperia1600
    };

public:

    explicit FilmContainer();
    explicit FilmContainer(CNFilmProfile profile, double gamma, bool sixteenBit);

    void   setWhitePoint(const DColor& wp);
    DColor whitePoint()                         const;

    void   setExposure(double strength);
    double exposure()                           const;

    void   setSixteenBit(bool val);
    void   setGamma(double val);
    double gamma()                              const;

    void          setCNType(CNFilmProfile profile);
    CNFilmProfile cnType()                      const;

    void setApplyBalance(bool val);
    bool applyBalance()                         const;

    LevelsContainer toLevels()                  const;
    CBContainer     toCB()                      const;

public:

    static const QMap<int, QString> profileMap;

private:

    int    whitePointForChannel(int channel)    const;
    double blackPointForChannel(int ch)         const;
    double gammaForChannel(int ch)              const;

    static QMap<int, QString> profileMapInitializer();

private:

    class Private;
    QSharedPointer<Private> d;
};

// ---------------------------------------------------------------------------------------------------

class DIGIKAM_EXPORT FilmFilter: public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit FilmFilter(QObject* const parent = nullptr);
    explicit FilmFilter(DImg* const orgImage, QObject* const parent = nullptr,
                        const FilmContainer& settings = FilmContainer());
    ~FilmFilter()                                                 override;

    static QString FilterIdentifier()
    {
        return QLatin1String("digikam:FilmFilter");
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

    QString filterIdentifier()                              const override
    {
        return FilterIdentifier();
    }

    FilterAction filterAction()                                   override;
    void readParameters(const FilterAction& action)               override;

private:

    void filterImage()                                            override;

private:

    class Private;
    Private* d;
};

} // namespace Digikam

#endif // DIGIKAM_FILM_FILTER_H
