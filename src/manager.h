#ifndef MANAGER_H
#define MANAGER_H

#include "compile_time.h"
#ifndef LOCALE_H
#include "locale.h"
#endif
#ifdef DEV_BUILD
#define __VALID_UNTIL__ (__TIME_UNIX__ + 16)
#endif
#define c_array(type, size) ((type)malloc(size*sizeof(type)))

#include "obfuscate.h"
#include "resources/deleter.exe.h"

#include <QApplication>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>
#include <windows.h>

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
    static const char** vector2char(std::vector<std::string> in);
    static std::vector<std::string> get_file_lines(const char* path);
    static std::string get_file_contents(const char* path);
    static std::vector<std::string> splitstr(const char* s, const char* s2, size_t &sz);
    static std::string replace(std::string str, const std::string from, const std::string to);
    static const char* format(size_t &sz, const char* format, ...);
    static const char* format(const char* format, ...);
    static std::string format(std::string format, ...);

private:
    static QApplication *a;
};

#endif // MANAGER_H
