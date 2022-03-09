#ifndef LOGGER_DISABLED
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <QDir>
#include <unistd.h>
#include <fstream>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <algorithm>

#include <ctime>
#include <iomanip>

#include "config.h"
#include "errors.h"

#define LOGGER_PATH "log/"
#define LOGGER_FILE_EXT ".log.txt"
#define LOGFILE(name) ((const char*) (LOGGER_PATH name LOGGER_FILE_EXT))

#define L_INF 0 // information
#define L_WRN 1 // warning
#define L_ERR 2 // error
#define L_CRT 3 // critical error

#define L_SINGLESTREAM 0b1000
#define L_NOCONFERROR 0b0100

class logger {
private:
    static Config conf;
    static bool confRegistered;
    static unsigned char config;
    static std::ofstream out;
    static bool stream_opened;
    static std::ofstream open_stream();
    static void write(std::string message);
public:
    logger();
    static void regConfig(Config c);
    static void init();
    static void log(std::string message, char code = L_INF);
    static void configure(unsigned char _config, bool overrideExistant = true);
};

#endif // LOGGER_H
#endif // LOGGER_DISABLED
