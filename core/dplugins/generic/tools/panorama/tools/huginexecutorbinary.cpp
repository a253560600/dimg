/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2015-11-02
 * Description : Autodetect hugin_executor binary program and version
 *
 * Copyright (C) 2015-2016 by Benjamin Girault <benjamin dot girault at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "huginexecutorbinary.h"

namespace DigikamGenericPanoramaPlugin
{

HuginExecutorBinary::HuginExecutorBinary(QObject* const)
    : DBinaryIface(QLatin1String("hugin_executor"),
                   QLatin1String("Hugin"),
                   QLatin1String("http://hugin.sourceforge.net/download/"),         // krazy:exclude=insecurenet
                   QLatin1String("Panorama"),
                   QStringList(QLatin1String("-h"))
                  )
{
    setup();
}

HuginExecutorBinary::~HuginExecutorBinary()
{
}

} // namespace DigikamGenericPanoramaPlugin
