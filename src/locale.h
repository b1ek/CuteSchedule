#ifndef LOCALE_H
#define LOCALE_H

#include <iostream> 
#include <string>
#include <stdlib.h>

#include <QString>
#include <QList>
#include <QFile>

#include "manager.h"

class locale
{
    static QStringList trs;
public:
    static void init();
    static std::string get(int id);
    static QString Qget(qint32 id);

};

#endif // LOCALE_H
