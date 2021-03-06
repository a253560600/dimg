/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2000-06-08
 * Description : Core database <-> thumbnail database interface
 *
 * Copyright (C) 2009      by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "coredbthumbinfoprovider.h"

// Qt includes

#include <QUrl>

// Local includes

#include "coredb.h"
#include "collectionmanager.h"
#include "collectionlocation.h"
#include "coredbaccess.h"
#include "iteminfo.h"
#include "thumbnailcreator.h"

namespace Digikam
{

ThumbnailInfo ThumbsDbInfoProvider::thumbnailInfo(const ThumbnailIdentifier& identifier)
{
    // If code here proves to be a bottleneck we can add custom queries to albumdb to retrieve info all-in-one

    ItemInfo imageinfo;

    if (identifier.id)
    {
        imageinfo = ItemInfo(identifier.id);
    }
    else
    {
        imageinfo = ItemInfo::fromLocalFile(identifier.filePath);
    }

    if (imageinfo.isNull())
    {
        return ThumbnailCreator::fileThumbnailInfo(identifier.filePath);
    }

    return imageinfo.thumbnailInfo();
}

// ---------------------------------------------------------------------------------

int DatabaseLoadSaveFileInfoProvider::orientationHint(const QString& path)
{
    ItemInfo info = ItemInfo::fromLocalFile(path);

    return info.orientation();
}

QSize DatabaseLoadSaveFileInfoProvider::dimensionsHint(const QString& path)
{
    ItemInfo info = ItemInfo::fromLocalFile(path);

    return info.dimensions();
}

} // namespace Digikam
