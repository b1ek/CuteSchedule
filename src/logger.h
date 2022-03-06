#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <QDir>
#include <unistd.h>

#define LOGGER_PATH "log/"
#define LOGGER_FILE_EXT ".log.txt"
#define LOGFILE(name) ((const char*) (LOGGER_PATH name LOGGER_FILE_EXT))

class logger {

public:
    logger();
    static void init();
    static void log(std::string message);
};

#endif // LOGGER_H
