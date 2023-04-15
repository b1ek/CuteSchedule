
#ifndef _WIN32
#ifndef linux

#error "Can't recognize your platform. Please either set _WIN32 or 'linux' macro according to your system."

#endif
#endif

#include <QApplication>

#include "./src/config/config.h"
#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
    Config config;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
