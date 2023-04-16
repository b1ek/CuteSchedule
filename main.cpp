
#ifndef _WIN32
#ifndef linux

#error "Can't recognize your platform. Please either set _WIN32 or 'linux' macro according to your system."

#endif
#endif

#ifdef _WIN32
#pragma message ( "Windows build is not supported, and should be quite unstable." )
#endif

#include <QApplication>
#include <QErrorMessage>

#include <iostream>

#include "src/config/config.h"
#include "src/mainwindow.h"
#include "src/util/userutil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Config config;

    if (!config.loadDefaultConfig()) {
        UserUtil::showError(
            QString("Cannot load config:\n") +
            "\n" +
            "Error code: 0x" + QString::number(config.getLastErrorCode()) + "\n"
        );
        return config.getLastErrorCode();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
