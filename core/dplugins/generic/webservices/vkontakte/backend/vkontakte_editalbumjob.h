/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2011-02-19
 * Description : a tool to export images to VKontakte web service
 *
 * Copyright (C) 2011-2015 by Alexander Potashev <aspotashev at gmail dot com>
 * Copyright (C) 2011-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_VKONTAKTE_EDITALBUMJOB_H
#define DIGIKAM_VKONTAKTE_EDITALBUMJOB_H

// Local includes

#include "vkontakte_jobs.h"
#include "vkontakte_albuminfo.h"

namespace Vkontakte
{

class EditAlbumJob : public VkontakteJob
{
    Q_OBJECT

public:

    EditAlbumJob(const QString& accessToken,
                 int aid,
                 const QString& title,
                 const QString& description = QString(),
                 int privacy = AlbumInfo::PRIVACY_UNKNOWN,
                 int comment_privacy = AlbumInfo::PRIVACY_UNKNOWN);

protected:

    void handleData(const QJsonValue& data) override;

private:

    // Disable
    EditAlbumJob(QObject*) = delete;
};

} // namespace Vkontakte

#endif // DIGIKAM_VKONTAKTE_EDITALBUMJOB_H
