/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2004-12-06
 * Description : digiKam image editor Ratio Crop tool
 *
 * Copyright (C) 2007      by Jaromir Malenko <malenko at email dot cz>
 * Copyright (C) 2008      by Roberto Castagnola <roberto dot castagnola at gmail dot com>
 * Copyright (C) 2004-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_EDITOR_RATIO_CROP_TOOL_H
#define DIGIKAM_EDITOR_RATIO_CROP_TOOL_H

// Qt includes

#include <QRect>

// Local includes

#include "editortool.h"

using namespace Digikam;

namespace DigikamEditorRatioCropToolPlugin
{

class RatioCropTool : public EditorTool
{
    Q_OBJECT

public:

    explicit RatioCropTool(QObject* const parent);
    ~RatioCropTool()                            override;

private:

    void  readSettings()                        override;
    void  writeSettings()                       override;

    void  finalRendering()                      override;
    void  updateCropInfo();
    void  applyRatioChanges(int a);
    void  blockWidgetSignals(bool b);
    void  setRatioCBText(int orientation);
    void  setInputRange(const QRect& rect);
    void  setBackgroundColor(const QColor& bg)  override;
    QRect getNormalizedRegion() const;

private Q_SLOTS:

    void slotMaxAspectRatio();
    void slotResetSettings()                    override;

    void slotCenterWidth();
    void slotCenterHeight();
    void slotXChanged(int x);
    void slotYChanged(int y);
    void slotWidthChanged(int w);
    void slotHeightChanged(int h);
    void slotCustomRatioChanged();
    void slotCustomNRatioChanged(int a);
    void slotCustomDRatioChanged(int a);
    void slotPreciseCropChanged(bool a);
    void slotOrientChanged(int o);
    void slotAutoOrientChanged(bool a);
    void slotRatioChanged(int a);
    void slotSelectionChanged(const QRect&);
    void slotSelectionOrientationChanged(int);
    void slotGuideTypeChanged(int t);
    void slotGoldenGuideTypeChanged();

private:

    class Private;
    Private* const d;
};

} // namespace DigikamEditorRatioCropToolPlugin

#endif // DIGIKAM_EDITOR_RATIO_CROP_TOOL_H
