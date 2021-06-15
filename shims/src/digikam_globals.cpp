#include <QProcessEnvironment>

namespace Digikam
{
    QProcessEnvironment adjustedEnvironmentForAppImage()
    {
        return QProcessEnvironment::systemEnvironment();
    }
}
