/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2005-11-24
 * Description : Color management setup tab.
 *
 * Copyright (C) 2005-2007 by F.J. Cruz <fj dot cruz at supercable dot es>
 * Copyright (C) 2005-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2009-2012 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#ifndef DIGIKAM_SETUP_ICC_H
#define DIGIKAM_SETUP_ICC_H

// Qt includes

#include <QScrollArea>
#include <QMap>
#include <QDir>
#include <QUrl>

// Local includes

#include "digikam_export.h"

class QDialogButtonBox;

namespace Digikam
{

class IccProfile;

class DIGIKAM_EXPORT SetupICC : public QScrollArea
{
    Q_OBJECT

public:

    explicit SetupICC(QDialogButtonBox* const dlgBtnBox, QWidget* const parent = nullptr);
    ~SetupICC() override;

    void applySettings();

    static bool iccRepositoryIsValid();

private:

    void readSettings(bool restore = false);
    void fillCombos(bool report);
    void setWidgetsEnabled(bool enabled);
    void profileInfo(const IccProfile&);

private Q_SLOTS:

    void slotToggledEnabled();
    void slotUrlChanged();
    void slotUrlTextChanged();
    void slotClickedIn();
    void slotClickedWork();
    void slotClickedMonitor();
    void slotClickedProof();
    void slotShowDefaultSearchPaths();
    void slotMissingToggled(bool);

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_SETUP_ICC_H
