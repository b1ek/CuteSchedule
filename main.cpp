
#ifndef _WIN32
#ifndef linux

#error "Can't recognize your platform. Please either set _WIN32 or 'linux' macro according to your system."

#endif
#endif

#ifdef _WIN32
#pragma message ( "Windows build is not supported, and should be quite unstable." )
#endif

#include <QApplication>

#include <iostream>

#include "src/config/config.h"
#include "src/sysutil.h"
#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
    Config config;

    std::cout << config.loadDefaultConfig() << '\n';
    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
