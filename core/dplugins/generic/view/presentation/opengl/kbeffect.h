/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-11-14
 * Description : a presentation tool.
 *
 * Copyright (C) 2007-2008 by Valerio Fuoglio <valerio dot fuoglio at gmail dot com>
 * Copyright (C) 2012-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * Parts of this code are based on smoothslidesaver by Carsten Weinhold
 * <carsten dot weinhold at gmx dot de>
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

#ifndef DIGIKAM_KB_EFFECT_H
#define DIGIKAM_KB_EFFECT_H

// Qt includes

#include <QObject>

namespace DigikamGenericPresentationPlugin
{

class KBImage;
class PresentationKB;

class KBEffect
{

public:

    typedef enum
    {
        Fade,
        Blend
    } Type;

public:

    explicit KBEffect(PresentationKB* const parent, bool m_needFadeIn = true);
    virtual ~KBEffect()                  = default;

    virtual bool fadeIn()       const
    {
        return m_needFadeIn;
    };

    virtual void advanceTime(float step) = 0;
    virtual Type type()                  = 0;
    virtual bool done()                  = 0;

    static Type chooseKBEffect(Type oldType);

protected:

    void     setupNewImage(int img);
    void     swapImages();
    KBImage* image(int img)     const;

protected:

    static int      m_numKBEffectRepeated;
    bool            m_needFadeIn;
    KBImage*        m_img[2];

private:

    PresentationKB* m_slideWidget;

private:

    Q_DISABLE_COPY(KBEffect)
};

// -------------------------------------------------------------------------

class FadeKBEffect: public KBEffect
{

public:

    explicit FadeKBEffect(PresentationKB* const parent, bool m_needFadeIn = true);
    ~FadeKBEffect()              override;

    Type type()                  override
    {
        return Fade;
    };

    void advanceTime(float step) override;
    bool done()                  override;

private:

    Q_DISABLE_COPY(FadeKBEffect)
};

// -------------------------------------------------------------------------

class BlendKBEffect: public KBEffect
{

public:

    explicit BlendKBEffect(PresentationKB* const parent, bool m_needFadeIn = true);
    ~BlendKBEffect()             override;

    Type type()                  override
    {
        return Blend;
    };

    void advanceTime(float step) override;
    bool done()                  override;

private:

    Q_DISABLE_COPY(BlendKBEffect)
};

} // namespace DigikamGenericPresentationPlugin

#endif // DIGIKAM°KB_EFFECT_H
