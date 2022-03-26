#ifndef MANAGER_H
#define MANAGER_H
#include "logger.h"

#include <QApplication>

#include <chrono>
#include <random>
#include <iomanip>

class manager
{
public:
    static void startup();
    static void quit(int exitCode);
    static uint64_t getNSTime();
    static uint getRND(uint floor = 0, uint roof = 0xfffff);
    static char* getRBits(unsigned char count = 16);
    static uint64_t chrToInt(char* chars, size_t sz);
    static std::string getUUID1();
    static QApplication *createApp(int argc, char** argv);
private:
    static QApplication *a;
};

#endif // MANAGER_H
