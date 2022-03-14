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

namespace logger {

    static std::ofstream out;
    static const std::string defFolder = "src";
    static bool initalized = false;

    static void md(const char* path) {
        if (QDir(path).exists()) return;
        QDir().mkdir(path);
    }

    static std::string getDate(std::string format) {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream s("");
        s << std::put_time(&tm, format.c_str());
        return s.str();
    }

    static void init() {
        auto dir = defFolder + "/" + getDate(L_DIR_DATE_F);
        md(dir.c_str());
        out = std::ofstream(dir + "/" + getDate(L_FILE_DATE_F) + ".txt.log");

        initalized = true;
    }

    static void write(std::string msg) {
        out << msg;
    }

    static void log(std::string msg, int level = L_INF) {
        switch (level) {
            case L_INF:
                logger::write(getDate(L_LOG_DATE_F) + "-[INFO]: " + msg);
                break;
            case L_WRN:
                logger::write(getDate(L_LOG_DATE_F) + "-[WARN]: " + msg);
                break;
            case L_ERR:
                logger::write(getDate(L_LOG_DATE_F) + "-[EROR]: " + msg);
                break;
            case L_CRT:
                logger::write(getDate(L_LOG_DATE_F) + "-[CERR]: " + msg);
                break;
        }
    }

    static void uninit() {
        if (initalized) return;
        out.close();
        initalized = false;
    }
}

#endif // LOGGER_H
