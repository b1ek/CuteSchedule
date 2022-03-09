#ifndef CONFIG_H
#define CONFIG_H

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string.h>
#include <QMessageBox>

#include "scheduleObjects/teacher.h"

class Config
{
    YAML::Node file;
public:
    Config();
    char* getSourceStr();
    void reload();
    std::string get(std::string what);
    YAML::Node getNode(std::string ofWhat, bool& exists);
    bool exists(std::string what);
    std::map<std::string, qbs::teacher> loadTeachers();

};

#endif // CONFIG_H
