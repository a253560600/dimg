#pragma once

#include <QString>

namespace Digikam
{

class DFileOperations
{
public:
    static bool copyModificationTime(const QString& srcFile, const QString& dstFile);
};

}
