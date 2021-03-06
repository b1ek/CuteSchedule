#ifndef CONFIG_H
#define CONFIG_H

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string.h>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sys/stat.h>
#include <QFile>
#include <regex>

#include "errors.h"
#include "scheduleObjects/all.h"

class Config {
    YAML::Node file;
public:
    Config();
    char* getSourceStr();
    void reload();
    std::string get(std::string what);
    YAML::Node getNode(std::string ofWhat, bool& exists);
    bool exists(std::string what);
private:
    static bool isconf;
    static Config loaded;

};

#endif // CONFIG_H
