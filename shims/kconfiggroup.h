#pragma once

#include <QVariant>
#include <QString>
#include <QStandardPaths>

class KConfigGroup
{
public:
    enum WriteConfigFlag {
        Persistent = 0x01,
        Global = 0x02,
        Localized = 0x04,
        Notify = 0x08 | Persistent,
        Normal = Persistent,
    };
    typedef QFlags<WriteConfigFlag> WriteConfigFlags;
    QStringList groupList() const;
    KConfigGroup group(const QString &group);
    bool hasGroup (const QString &group) const;
    void deleteGroup(WriteConfigFlags pFlags=Normal);
    template<typename T>
    T readEntry(const QString &key, const T &aDefault) const
    {
        //TODO
    }
    template<typename T >
    T readEntry(const char *key, const T &aDefault) const
    {
        //TODO
    }
    QVariant readEntry(const QString &key, const QVariant &aDefault) const;
    QVariant readEntry(const char *key, const QVariant &aDefault) const;
    QString readEntry(const QString &key, const QString &aDefault) const;
    QString readEntry(const char *key, const QString &aDefault) const;
    QString readEntry(const QString &key, const char *aDefault=nullptr) const;
    QString readEntry (const char *key, const char *aDefault=nullptr) const;
    QString readPathEntry(const QString &pKey, const QString &aDefault) const;
    QString readPathEntry(const char *key, const QString &aDefault) const;
    template<typename T >
    void writeEntry(const char *key, const T &value, WriteConfigFlags pFlags=Normal)
    {
        //TODO
    }
    template<typename T >
    void writeEntry(const QString &key, const T &value, WriteConfigFlags pFlags=Normal)
    {
        //TODO
    }
    void writeEntry(const QString &key, const QVariant &value, WriteConfigFlags pFlags=Normal);
    void writeEntry(const char *key, const QVariant &value, WriteConfigFlags pFlags=Normal);
    void writePathEntry(const QString &pKey, const QString &path, WriteConfigFlags pFlags=Normal);
    void writePathEntry(const char *Key, const QString &path, WriteConfigFlags pFlags=Normal);
    bool sync();
};

class KSharedConfig
{
public:
    enum OpenFlag {
        IncludeGlobals = 0x01, CascadeConfig = 0x02, SimpleConfig = 0x00, NoCascade = IncludeGlobals,
        NoGlobals = CascadeConfig, FullConfig = IncludeGlobals | CascadeConfig
    };
    typedef QFlags<OpenFlag> OpenFlags;
    typedef KSharedConfig* Ptr;
    static Ptr openConfig(const QString &fileName=QString(), OpenFlags mode=FullConfig, QStandardPaths::StandardLocation type=QStandardPaths::GenericConfigLocation);
    KConfigGroup group(const QString &group);
    KConfigGroup group(const char *group);
};
