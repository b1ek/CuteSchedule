#ifndef LICENSER_H
#define LICENSER_H

#include <string>
#include "obfuscate.h"

class licenser
{
    long guid;
    bool valid;
public:
    static long get_license_guid();
    static void reload();
    static void init();
    static bool isValid();
    static std::string getLicense();
};

#endif // LICENSER_H
