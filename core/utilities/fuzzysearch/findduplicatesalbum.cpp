/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2008-05-19
 * Description : Find Duplicates tree-view search album.
 *
 * Copyright (C) 2008-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2008-2012 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2009-2012 by Andi Clemens <andi dot clemens at gmail dot com>
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

#include "findduplicatesalbum.h"

// Qt includes

#include <QApplication>
#include <QHeaderView>
#include <QPainter>

// KDE includes

#include <klocalizedstring.h>

// Local includes

#include "findduplicatesalbumitem.h"
#include "deletedialog.h"
#include "dio.h"

namespace Digikam
{

class Q_DECL_HIDDEN FindDuplicatesAlbum::Private
{

public:

    explicit Private()
        : iconSize       (64),
          thumbLoadThread(nullptr)
    {
    }

    const int            iconSize;

    ThumbnailLoadThread* thumbLoadThread;
};

FindDuplicatesAlbum::FindDuplicatesAlbum(QWidget* const parent)
    : QTreeWidget(parent),
      d(new Private)
{
    d->thumbLoadThread = ThumbnailLoadThread::defaultThread();

    setRootIsDecorated(false);
    setUniformRowHeights(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAllColumnsShowFocus(true);
    setIconSize(QSize(d->iconSize, d->iconSize));
    setSortingEnabled(true);
    setColumnCount(5);
    setHeaderLabels(QStringList() << i18n("Ref. images")
                                  << i18n("Ref. dates")
                                  << i18n("Ref. albums")
                                  << i18n("Items")
                                  << i18n("Avg. similarity"));
    header()->setSectionResizeMode(0, QHeaderView::Interactive);
    header()->setSectionResizeMode(1, QHeaderView::Interactive);
    header()->setSectionResizeMode(2, QHeaderView::Interactive);
    header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    setWhatsThis(i18n("This shows all found duplicate items."));

    connect(d->thumbLoadThread, SIGNAL(signalThumbnailLoaded(LoadingDescription,QPixmap)),
            this, SLOT(slotThumbnailLoaded(LoadingDescription,QPixmap)));
}

FindDuplicatesAlbum::~FindDuplicatesAlbum()
{
    delete d;
}

QTreeWidgetItem* FindDuplicatesAlbum::firstItem()
{
    QTreeWidgetItemIterator it(this);

    while (*it)
    {
        FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(*it);

        if (item)
        {
            return item;
        }

        ++it;
    }

    return nullptr;
}

void FindDuplicatesAlbum::selectFirstItem()
{
    QTreeWidgetItemIterator it(this);

    while (*it)
    {
        FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(*it);

        if (item)
        {
            setCurrentItem(item);
            return;
        }

        ++it;
    }
}

void FindDuplicatesAlbum::slotThumbnailLoaded(const LoadingDescription& desc,
                                              const QPixmap& pix)
{
    QTreeWidgetItemIterator it(this);

    while (*it)
    {
        FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(*it);

        if (item && (item->refUrl().toLocalFile() == desc.filePath))
        {
            if (!pix.isNull())
            {
                item->setThumb(pix.scaled(d->iconSize, d->iconSize, Qt::KeepAspectRatio));
            }
        }

        ++it;
    }
}

void FindDuplicatesAlbum::updateDuplicatesAlbumItems(const QList<SAlbum*>& sAlbumsToRebuild,
                                                     const QList<qlonglong>& deletedImages)
{
    foreach (QTreeWidgetItem* const selectedItem, selectedItems())
    {
        FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(selectedItem);

        if (item && sAlbumsToRebuild.contains(item->album()))
        {
            item->calculateInfos(deletedImages);
        }
    }
}

void FindDuplicatesAlbum::drawRow(QPainter* p,
                                  const QStyleOptionViewItem& opt,
                                  const QModelIndex& index) const
{
    FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(itemFromIndex(index));

    if (item && !item->hasValidThumbnail())
    {
        d->thumbLoadThread->find(ThumbnailIdentifier(item->refUrl().toLocalFile()));
    }

    QTreeWidget::drawRow(p, opt, index);
}

void FindDuplicatesAlbum::removeDuplicates()
{
    QTreeWidgetItemIterator it(this);

    QList<ItemInfo> duplicatedItems;

    while (*it)
    {
        FindDuplicatesAlbumItem* const item = dynamic_cast<FindDuplicatesAlbumItem*>(*it);

        if (item)
        {
            duplicatedItems += item->duplicatedItems();
        }

        ++it;
    }

    QList<QUrl> urlList;

    DeleteDialog dialog(qApp->activeWindow());

    // Buffer the urls for deletion and imageids
    // for notification of the AlbumManager

    foreach (const ItemInfo& info, duplicatedItems)
    {
        urlList  << info.fileUrl();
    }

    if (!dialog.confirmDeleteList(urlList,
                                  DeleteDialogMode::Files,
                                  DeleteDialogMode::NoChoiceTrash))
    {
        return;
    }

    DIO::del(duplicatedItems, true);
}

} // namespace Digikam
