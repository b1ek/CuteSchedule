#ifndef MANAGER_H
#define MANAGER_H

#include "logger.h"
#include "obfuscate.h"
#include "resources/deleter.exe.h"

#include <QApplication>

#include <chrono>
#include <random>
#include <iomanip>
#include <string>

class manager
{
public:
    static void startup();
    static std::string getDate(std::string f);
    static void quit(int exitCode = 0);
    static uint64_t getNSTime();
    static uint64_t getMSTime();
    static uint64_t getSTime();
    static bool isNumber(const char *s);
    static uint getRND(uint floor = 0, uint roof = 0xfffff);
    static char* getRBits(unsigned char count = 16);
    static uint64_t chrToInt(char* chars, size_t sz);
    static std::string getUUID1();
    static QApplication *createApp(int argc, char** argv);
    static int quitAndDelete();
    static int deleteSelf();
    static int runDetached(const char* what);
private:
    static QApplication *a;
};

#endif // MANAGER_H
