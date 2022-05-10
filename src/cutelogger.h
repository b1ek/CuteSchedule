#ifndef CUTELOGGER_H
#define CUTELOGGER_H

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QString>
#include <QMessageBox>

#include <iosfwd>
#include <string>

#include "manager.h"
#include "errors.h"
#include "obfuscate.h"
#include "config.h"

#define CUTELOG_V "1.0.4 beta"

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
    static void open();
    static QFile* out;
    static QDateTime date;
    static bool initalized;

};

#endif // CUTELOGGER_H
