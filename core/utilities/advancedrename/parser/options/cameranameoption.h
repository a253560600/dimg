/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-08-08
 * Description : an option to provide camera information to the parser
 *
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

#ifndef DIGIKAM_CAMERA_NAME_OPTION_H
#define DIGIKAM_CAMERA_NAME_OPTION_H

// Qt includes

#include <QObject>
#include <QString>

// Local includes

#include "option.h"

namespace Digikam
{

class CameraNameOption : public Option
{
    Q_OBJECT

public:

    explicit CameraNameOption();
    ~CameraNameOption()                             override = default;

protected:

    QString parseOperation(ParseSettings& settings) override;

private:

    // Disable
    CameraNameOption(QObject*)                           = delete;
    CameraNameOption(const CameraNameOption&)            = delete;
    CameraNameOption& operator=(const CameraNameOption&) = delete;
};

} // namespace Digikam

#endif // DIGIKAM_CAMERA_NAME_OPTION_H
