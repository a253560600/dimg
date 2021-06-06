#include <QProcessEnvironment>

namespace Digikam
{
    QProcessEnvironment adjustedEnvironmentForAppImage()
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        return env;
    }
}
