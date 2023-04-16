#ifndef SYSUTIL_H
#define SYSUTIL_H

#include <QObject>

#ifdef linux
#include <unistd.h>
#include <pwd.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

class SysUtil : public QObject
{
    Q_OBJECT
public:
    SysUtil();

    static QString getUserName();
};

#endif // SYSUTIL_H
