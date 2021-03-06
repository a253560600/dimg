/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-02-11
 * Description : a tool to show image using an OpenGL interface.
 *
 * Copyright (C) 2007-2008 by Markus Leuthold <kusi at forum dot titlis dot org>
 * Copyright (C) 2008-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_GLVIEWER_PLUGIN_GLVIEWER_TEXTURE_H
#define DIGIKAM_GLVIEWER_PLUGIN_GLVIEWER_TEXTURE_H

// Qt includes

#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QImage>
#include <QString>

// Local includes

#include "dinfointerface.h"

using namespace Digikam;

namespace DigikamGenericGLViewerPlugin
{

class GLViewerTexture : public QOpenGLTexture
{

public:

    explicit GLViewerTexture(DInfoInterface* const iface);
    ~GLViewerTexture();

    bool load(const QString& fn, const QSize& size);
    bool load(const QImage& im);
    bool loadFullSize();

    GLfloat vertex_bottom() const;
    GLfloat vertex_top()    const;
    GLfloat vertex_left()   const;
    GLfloat vertex_right()  const;

    void setViewport(int w, int h);
    void zoom(float delta, const QPoint& mousepos);
    void reset(bool resetFullImage = false);
    void move(const QPoint& diff);
    bool setNewSize(QSize size);
    void rotate();
    void zoomToOriginal();

private:

    bool loadInternal();
    void calcVertex();

private:

    // Disable
    GLViewerTexture(const GLViewerTexture&) = delete;

private:

    class Private;
    Private* const d;
};

} // namespace DigikamGenericGLViewerPlugin

#endif // DIGIKAM_GLVIEWER_PLUGIN_GLVIEWER_TEXTURE_H
