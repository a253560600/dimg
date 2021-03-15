/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-11-21
 * Description : Wavelets Noise Reduction batch tool.
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

#ifndef DIGIKAM_BQM_NOISE_REDUCTION_H
#define DIGIKAM_BQM_NOISE_REDUCTION_H

// Local includes

#include "batchtool.h"
#include "nrsettings.h"

using namespace Digikam;

namespace DigikamBqmNoiseReductionPlugin
{

class NoiseReduction : public BatchTool
{
    Q_OBJECT

public:

    explicit NoiseReduction(QObject* const parent = nullptr);
    ~NoiseReduction()                   override;

    BatchToolSettings defaultSettings() override;

    BatchTool* clone(QObject* const parent=nullptr) const override { return new NoiseReduction(parent); };

    void registerSettingsWidget()       override;

private:

    bool toolOperations()               override;

private Q_SLOTS:

    void slotAssignSettings2Widget()    override;
    void slotSettingsChanged()          override;

private:

    NRSettings* m_settingsView;
};

} // namespace DigikamBqmNoiseReductionPlugin

#endif // DIGIKAM_BQM_NOISE_REDUCTION_H
