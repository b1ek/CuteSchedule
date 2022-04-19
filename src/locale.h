#ifndef LOCALE_H
#define LOCALE_H

#include <iostream> 
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

#include <QString>
#include <QList>
#include <QFile>

#ifndef MANGER_H
#include "manager.h"
#endif

class locale
{
    static std::vector<std::string> trs;
public:
    static void init();
    static void uninit();
    static const char* get(size_t id);

};

#endif // LOCALE_H
