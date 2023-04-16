#include "sysutil.h"

SysUtil::SysUtil()
{

}

QString SysUtil::getUserName()
{
#ifdef linux
    uid_t uid;
    struct passwd* pawd;
    uid = getuid();
    pawd = getpwuid(uid);

    return pawd->pw_name;
#endif

#ifdef _WIN32
#define MAX 100
    char szBuffer[MAX];
    DWORD len = MAX;
    if (GetUserName(szBuffer, &len))
        return szBuffer;
#undef MAX
#endif

    return "";
}
