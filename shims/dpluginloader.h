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
    std::vector<DPlugin*> allPlugins();

private:
    DPluginLoader() {}
};

}
