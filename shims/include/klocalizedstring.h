#pragma once

#include <QString>

#define I18N_NOOP(x) (x)

inline QString i18n(const char *text)
{
    return QString::fromUtf8(text);
}

template<typename A1>
QString i18n(const char *text, const A1& a1)
{
    return QString::fromUtf8(text).arg(a1);
}

template<typename A1, typename A2>
QString i18n(const char*, const char *text, const A1& a1, const A2& a2)
{
    return QString::fromUtf8(text).arg(a1).arg(a2);
}

inline QString i18nc(const char*, const char *text)
{
    return QString::fromUtf8(text);
}

template<typename A1>
QString i18nc(const char*, const char *text, const A1& a1)
{
    return QString::fromUtf8(text).arg(a1);
}

template<typename A1, typename A2>
QString i18nc(const char*, const char *text, const A1& a1, const A2& a2)
{
    return QString::fromUtf8(text).arg(a1).arg(a2);
}
