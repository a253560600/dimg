/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-04-16
 * Description : Qt Model for Albums - drag and drop handling
 *
 * Copyright (C) 2009-2011 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2006-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_ALBUM_DRAG_DROP_H
#define DIGIKAM_ALBUM_DRAG_DROP_H

// Local includes

#include "albummodeldragdrophandler.h"
#include "albummodel.h"

namespace Digikam
{

class AlbumDragDropHandler : public AlbumModelDragDropHandler
{
    Q_OBJECT

public:

    explicit AlbumDragDropHandler(AlbumModel* const model);

    AlbumModel* model() const;

    bool dropEvent(QAbstractItemView* view,
                   const QDropEvent* e,
                   const QModelIndex& droppedOn)         override;

    Qt::DropAction accepts(const QDropEvent* e,
                           const QModelIndex& dropIndex) override;

    QStringList mimeTypes() const override;
    QMimeData* createMimeData(const QList<Album*>&)      override;
};

} // namespace Digikam

#endif // DIGIKAM_ALBUM_DRAG_DROP_H
