/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-11-10
 * Description : IPTC envelope settings page.
 *
 * Copyright (C) 2007-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_IPTC_ENVELOPE_H
#define DIGIKAM_IPTC_ENVELOPE_H

// Qt includes

#include <QWidget>
#include <QByteArray>

namespace DigikamGenericMetadataEditPlugin
{

class IPTCEnvelope : public QWidget
{
    Q_OBJECT

public:

    explicit IPTCEnvelope(QWidget* const parent);
    ~IPTCEnvelope() override;

    void applyMetadata(QByteArray& iptcData);
    void readMetadata(QByteArray& iptcData);

Q_SIGNALS:

    void signalModified();

private Q_SLOTS:

    void slotDestinationLeftCharacters();
    void slotSetTodaySent();
    void slotLineEditModified();

private:

    class Private;
    Private* const d;
};

} // namespace DigikamGenericMetadataEditPlugin

#endif // DIGIKAM_IPTC_ENVELOPE_H
