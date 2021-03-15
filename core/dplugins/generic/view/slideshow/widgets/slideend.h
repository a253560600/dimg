/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2014-09-18
 * Description : slideshow end view
 *
 * Copyright (C) 2014-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2019-2020 by Minh Nghia Duong <minhnghiaduong997 at gmail dot com>
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

#ifndef DIGIKAM_SLIDE_END_PLUGIN_H
#define DIGIKAM_SLIDE_END_PLUGIN_H

// Qt includes

#include <QWidget>

// Local includes

#include "digikam_export.h"

namespace DigikamGenericSlideShowPlugin
{

class SlideEnd : public QWidget
{
    Q_OBJECT

public:

    explicit SlideEnd(QWidget* const parent = nullptr);
    ~SlideEnd() override;
};

} // namespace DigikamGenericSlideShowPlugin

#endif // DIGIKAM_SLIDE_END_PLUGIN_H
