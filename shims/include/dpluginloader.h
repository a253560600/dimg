/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Copyright (C) 2014-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#pragma once

#include <vector>

namespace Digikam
{
    class DPlugin;
    class DPluginLoader
    {
    public:
        static DPluginLoader* instance()
        {
            static DPluginLoader loader;
            return &loader;
        }
        static std::vector<DPlugin*> allPlugins()
        {
            return plugins;
        }
        static void addPlugin(DPlugin* plugin)
        {
            plugins.push_back(plugin);
        }
    private:
        DPluginLoader() {}
        static std::vector<DPlugin*> plugins;
    };
}
