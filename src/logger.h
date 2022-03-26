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
#include <windows.h>

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
    static void md(std::string path);
    static void init();
    static void uninit();
    static void write(std::string msg);
    static void log(std::string msg, int level = L_INF);
    static std::string getDate(std::string f);
private:
    static std::ofstream out;
    static bool initalized;
};

#endif // LOGGER_H
