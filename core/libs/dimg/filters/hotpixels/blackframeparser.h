/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2005-03-27
 * Description : black frames parser
 *
 * Copyright (C) 2005-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2005-2006 by Unai Garro <ugarro at users dot sourceforge dot net>
 *
 * Part of the algorithm for finding the hot pixels was based on
 * the code of jpegpixi, which was released under the GPL license,
 * written by Martin Dickopp
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

#ifndef DIGIKAM_BLACK_FRAME_PARSER_H
#define DIGIKAM_BLACK_FRAME_PARSER_H

// Qt includes

#include <QList>
#include <QObject>
#include <QString>
#include <QRect>
#include <QUrl>

// Local includes

#include "digikam_export.h"
#include "hotpixelprops.h"
#include "loadingdescription.h"

using namespace Digikam;

namespace Digikam
{

class DIGIKAM_EXPORT BlackFrameParser: public QObject
{
    Q_OBJECT

public:

    explicit BlackFrameParser(QObject* const parent);
    ~BlackFrameParser() override;

    void parseHotPixels(const QString& file);
    void parseBlackFrame(const QUrl& url);
    void parseBlackFrame(const DImg& img);

    DImg image() const;

Q_SIGNALS:

    void signalHotPixelsParsed(const QList<HotPixelProps>&);
    void signalLoadingProgress(float);
    void signalLoadingComplete();

private Q_SLOTS:

    void slotLoadingProgress(const LoadingDescription&, float v);
    void slotLoadImageFromUrlComplete(const LoadingDescription&, const DImg& img);

private:

    void blackFrameParsing();
    void consolidatePixels(QList<HotPixelProps>& list);
    void validateAndConsolidate(HotPixelProps* const a, HotPixelProps* const b);

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_BLACK_FRAME_PARSER_H
