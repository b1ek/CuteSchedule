#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QDir>
#include <yaml-cpp/yaml.h>

#include "../util/sysutil.h"

#define CONF_ERR_NO_DIR 1

class Config
{
private:
    QString plainConfig;
    YAML::Node config;
    int errorCode;
public:
    Config();
    int getLastErrorCode();

    // Files
    bool loadDefaultConfig();
    static QString getDefaultConfigDir();

    // Config
    QString getConfigProperty(QString path);
};

#endif // CONFIG_H
