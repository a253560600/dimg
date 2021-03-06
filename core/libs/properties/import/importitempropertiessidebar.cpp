/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2006-02-08
 * Description : item properties side bar used by import tool.
 *
 * Copyright (C) 2006-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2013      by Michael G. Hansen <mike at mghansen dot de>
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

#include "importitempropertiessidebar.h"

// Qt includes

#include <QSplitter>
#include <QIcon>

// KDE includes

#include <klocalizedstring.h>
#include <kconfiggroup.h>

// Local includes

#include "digikam_config.h"
#include "dmetadata.h"
#include "camiteminfo.h"
#include "importitempropertiestab.h"
#include "itempropertiesmetadatatab.h"

#ifdef HAVE_MARBLE
#   include "itempropertiesgpstab.h"
#endif // HAVE_MARBLE

namespace Digikam
{

class Q_DECL_HIDDEN ImportItemPropertiesSideBarImport::Private
{
public:

    explicit Private()
      : dirtyMetadataTab    (false),
        dirtyCameraItemTab  (false),
        dirtyGpsTab         (false),
        metaData            (nullptr),

#ifdef HAVE_MARBLE

        gpsTab              (nullptr),

#endif // HAVE_MARBLE

        metadataTab         (nullptr),
        cameraItemTab       (nullptr)
    {
    }

    bool                       dirtyMetadataTab;
    bool                       dirtyCameraItemTab;
    bool                       dirtyGpsTab;

    DMetadata*                 metaData;

    CamItemInfo                itemInfo;

#ifdef HAVE_MARBLE

    ItemPropertiesGPSTab*      gpsTab;

#endif // HAVE_MARBLE

    ItemPropertiesMetadataTab* metadataTab;
    ImportItemPropertiesTab*   cameraItemTab;
};

ImportItemPropertiesSideBarImport::ImportItemPropertiesSideBarImport(QWidget* const parent,
                                                         SidebarSplitter* const splitter,
                                                         Qt::Edge side,
                                                         bool mimimizedDefault)
    : Sidebar(parent, splitter, side, mimimizedDefault),
      d      (new Private)
{
    d->cameraItemTab = new ImportItemPropertiesTab(parent);
    d->metadataTab   = new ItemPropertiesMetadataTab(parent);

    appendTab(d->cameraItemTab, QIcon::fromTheme(QLatin1String("configure")),             i18n("Properties"));
    appendTab(d->metadataTab,   QIcon::fromTheme(QLatin1String("format-text-code")),              i18n("Metadata")); // krazy:exclude=iconnames

#ifdef HAVE_MARBLE

    d->gpsTab        = new ItemPropertiesGPSTab(parent);
    appendTab(d->gpsTab,        QIcon::fromTheme(QLatin1String("globe")), i18n("Geolocation"));

#endif // HAVE_MARBLE

    // --- NOTE: use dynamic binding as slotChangedTab() is a virtual method which can be re-implemented in derived classes.

    connect(this, &ImportItemPropertiesSideBarImport::signalChangedTab,
            this, &ImportItemPropertiesSideBarImport::slotChangedTab);
}

ImportItemPropertiesSideBarImport::~ImportItemPropertiesSideBarImport()
{
    delete d;
}

void ImportItemPropertiesSideBarImport::applySettings()
{
    /// @todo Still needed?

    /// @todo Are load/saveState called by the creator?
}

QUrl ImportItemPropertiesSideBarImport::url() const
{
    return d->itemInfo.url();
}

void ImportItemPropertiesSideBarImport::itemChanged(const CamItemInfo& itemInfo, const DMetadata& meta)
{
    if (itemInfo.isNull())
    {
        return;
    }

    if (d->metaData)
    {
        delete d->metaData;
    }

    d->metaData           = new DMetadata(meta.data());
    d->itemInfo           = itemInfo;
    d->dirtyMetadataTab   = false;
    d->dirtyCameraItemTab = false;
    d->dirtyGpsTab        = false;

    slotChangedTab(getActiveTab());
}

void ImportItemPropertiesSideBarImport::slotNoCurrentItem()
{
    d->itemInfo           = CamItemInfo();

    if (d->metaData)
    {
        delete d->metaData;
        d->metaData = nullptr;
    }

    d->dirtyMetadataTab   = false;
    d->dirtyCameraItemTab = false;
    d->dirtyGpsTab        = false;

    d->cameraItemTab->setCurrentItem();
    d->metadataTab->setCurrentURL();

#ifdef HAVE_MARBLE

    d->gpsTab->setCurrentURL();

#endif // HAVE_MARBLE

}

void ImportItemPropertiesSideBarImport::slotChangedTab(QWidget* tab)
{
    if (d->itemInfo.isNull())
    {
        return;
    }

    setCursor(Qt::WaitCursor);

    if      ((tab == d->cameraItemTab) && !d->dirtyCameraItemTab)
    {
        d->cameraItemTab->setCurrentItem(d->itemInfo, d->metaData);

        d->dirtyCameraItemTab = true;
    }
    else if ((tab == d->metadataTab) && !d->dirtyMetadataTab)
    {
        d->metadataTab->setCurrentData(d->metaData, d->itemInfo.url());
        d->dirtyMetadataTab = true;
    }

#ifdef HAVE_MARBLE

    else if ((tab == d->gpsTab) && !d->dirtyGpsTab)
    {
        d->gpsTab->setMetadata(d->metaData, d->itemInfo.url());
        d->dirtyGpsTab = true;
    }

    d->gpsTab->setActive(tab == d->gpsTab);

#endif // HAVE_MARBLE

    unsetCursor();
}

void ImportItemPropertiesSideBarImport::doLoadState()
{
    /// @todo This code is taken from ItemPropertiesSideBar::doLoadState()
    ///       Ideally ImportItemPropertiesSideBarImport should be a subclass of
    ///       ItemPropertiesSideBar

    Sidebar::doLoadState();

    KConfigGroup group                  = getConfigGroup();

    KConfigGroup groupCameraItemTab     = KConfigGroup(&group, entryName(QLatin1String("Camera Item Properties Tab")));
    d->cameraItemTab->readSettings(groupCameraItemTab);

#ifdef HAVE_MARBLE

    KConfigGroup groupGPSTab            = KConfigGroup(&group, entryName(QLatin1String("GPS Properties Tab")));
    d->gpsTab->readSettings(groupGPSTab);

#endif // HAVE_MARBLE

    const KConfigGroup groupMetadataTab = KConfigGroup(&group, entryName(QLatin1String("Metadata Properties Tab")));
    d->metadataTab->readSettings(groupMetadataTab);
}

void ImportItemPropertiesSideBarImport::doSaveState()
{
    /// @todo This code is taken from ItemPropertiesSideBar::doSaveState()
    ///       Ideally ImportItemPropertiesSideBarImport should be a subclass of
    ///       ItemPropertiesSideBar

    Sidebar::doSaveState();

    KConfigGroup group              = getConfigGroup();

    KConfigGroup groupCameraItemTab = KConfigGroup(&group, entryName(QLatin1String("Camera Item Properties Tab")));
    d->cameraItemTab->writeSettings(groupCameraItemTab);

#ifdef HAVE_MARBLE

    KConfigGroup groupGPSTab        = KConfigGroup(&group, entryName(QLatin1String("GPS Properties Tab")));
    d->gpsTab->writeSettings(groupGPSTab);

#endif // HAVE_MARBLE

    KConfigGroup groupMetadataTab   = KConfigGroup(&group, entryName(QLatin1String("Metadata Properties Tab")));
    d->metadataTab->writeSettings(groupMetadataTab);
}

} // namespace Digikam
