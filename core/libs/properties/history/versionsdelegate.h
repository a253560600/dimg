/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-07-15
 * Description : Item delegate for image versions list view
 *
 * Copyright (C) 2010-2011 by Martin Klapetek <martin dot klapetek at gmail dot com>
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

#ifndef DIGIKAM_VERSIONS_DELEGATE_H
#define DIGIKAM_VERSIONS_DELEGATE_H

// Qt includes

#include <QStyledItemDelegate>

// Local includes

#include "digikam_export.h"
#include "itemdelegateoverlay.h"

namespace Digikam
{

class VersionsDelegate : public QStyledItemDelegate,
                         public ItemDelegateOverlayContainer
{
    Q_OBJECT
    Q_PROPERTY(int animationState READ animationState
                                  WRITE setAnimationState
                                  NOTIFY animationStateChanged)

public:

    explicit VersionsDelegate(QObject* const parent);
    ~VersionsDelegate()                                                                               override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index)                const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void beginPainting();
    void finishPainting();

    int animationState()                                                                        const;
    void setAnimationState(int animationState);

    void setThumbnailSize(int size)                                                             const;
    int  thumbnailSize()                                                                        const;

Q_SIGNALS:

    void animationStateChanged();
    void visualChange(); // for ItemDelegateOverlayContainer

    /// NOTE: for ItemDelegateOverlayContainer, unimplemented:
    void requestNotification(const QModelIndex& index, const QString& message);
    void hideNotification();

protected Q_SLOTS:

    void overlayDestroyed(QObject* o)                                                                 override
    {
        ItemDelegateOverlayContainer::overlayDestroyed(o);
    }

protected:

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)                const override;

    /// Returns the delegate, typically, the derived class
    QAbstractItemDelegate* asDelegate() override
    {
        return this;
    }

private:

    VersionsDelegate(); // Disable default constructor.

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_VERSIONS_DELEGATE_H
