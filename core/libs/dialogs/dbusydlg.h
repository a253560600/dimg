/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-11-03
 * Description : a busy dialog for digiKam
 *
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

#ifndef DIGIKAM_DBUSY_DLG_H
#define DIGIKAM_DBUSY_DLG_H

// Qt includes

#include <QThread>
#include <QString>
#include <QProgressDialog>

// Local includes

#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_EXPORT DBusyThread : public QThread
{
    Q_OBJECT

public:

    explicit DBusyThread(QObject* const parent);
    ~DBusyThread() override;

Q_SIGNALS:

    void signalComplete();

protected:

    /// Reimplement this method with your code to run in a separate thread.
    void run() override {};
};

// ----------------------------------------------------------------------------------

class DIGIKAM_EXPORT DBusyDlg : public QProgressDialog
{
    Q_OBJECT

public:

    explicit DBusyDlg(const QString& txt, QWidget* const parent = nullptr);
    ~DBusyDlg() override;

    void setBusyThread(DBusyThread* const thread);

public Q_SLOTS:

    void slotComplete();

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_DBUSY_DLG_H
