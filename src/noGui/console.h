#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <stdio.h>
int openConsole() {
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    return 0;
}
int closeConsole() {
    return PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
}

#ifdef __cplusplus
}
#endif

#endif // CONSOLE_H
