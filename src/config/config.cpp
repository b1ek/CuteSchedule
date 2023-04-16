#include "config.h"

Config::Config()
{

}

bool Config::loadDefaultConfig()
{
    QString confDir = Config::getDefaultConfigDir();
    QDir configs(confDir);

    if (!configs.exists())
    {
        this->errorCode = CONF_ERR_NO_DIR;
        return false;
    }

    return true;
}

QString Config::getDefaultConfigDir()
{
#ifdef _WIN32
    return QString("C:\\Users\\") + SysUtil::getUserName() + "\\AppData\\Local\\CuteSchedule";
#endif

#ifdef linux
    return QString("/home/") + SysUtil::getUserName() + "/.config/CuteSchedule";
#endif

    return "";
}

QString Config::getConfigProperty(QString path)
{
    return "";
}

int Config::getLastErrorCode()
{
    return this->errorCode;
}
