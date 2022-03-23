#ifndef LOGGER_H
#define LOGGER_H

#include "errors.h"
#include "config.h"

#include <string>
#include <iostream>
#include <QDir>
#include <unistd.h>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>

#include <ctime>
#include <iomanip>

#define LOGGER_PATH "log/"
#define LOGGER_FILE_EXT ".log.txt"
#define LOGFILE(name) ((const char*) (LOGGER_PATH name LOGGER_FILE_EXT))

#define L_INF 0 // information
#define L_WRN 1 // warning
#define L_ERR 2 // error
#define L_CRT 3 // critical error

#define L_DIR_DATE_F  "%d %b %Y"
#define L_FILE_DATE_F "[%d.%b.%Y %I-00 %p]"
#define L_LOG_DATE_F  "[%H:%M.%S]"

class logger {
public:
    static void md(const char* path);
    static void init();
    static void getTime(const char* f);
private:
};

#endif // LOGGER_H
