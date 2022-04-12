#ifndef CUTELOGGER_H
#define CUTELOGGER_H

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QString>

#include <iosfwd>
#include <string>

class CuteLogger
{
public:
    enum Code {Info, Warn, Error, Critical};
    static void init();
    static void uninit();
    static void reload();
    static void info(QString msg);
    static void warn(QString msg);
    static void eror(QString msg);
    static void crit(QString msg);
    static void log(QString msg, Code c = Info);

private:
    static void write(QString msg);
    static QFile *open();
    static QFile *out;
    static QDateTime date;
    static bool initalized;

};

#endif // CUTELOGGER_H
