/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2006-07-09
 * Description : item tool tip configuration setup tab
 *
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

#ifndef SHOW_FOTO_SETUP_TOOL_TIP_H
#define SHOW_FOTO_SETUP_TOOL_TIP_H

// Qt includes

#include <QScrollArea>

namespace ShowFoto
{

class ShowfotoSetupToolTip : public QScrollArea
{
    Q_OBJECT

public:

    explicit ShowfotoSetupToolTip(QWidget* const parent = nullptr);
    ~ShowfotoSetupToolTip() override;

    void applySettings();

private:

    void readSettings();

private:

    class Private;
    Private* const d;
};

} // namespace ShowFoto

#endif // SHOW_FOTO_SETUP_TOOL_TIP_H
