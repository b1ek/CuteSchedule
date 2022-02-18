#pragma comment(lib, "yaml-cpp.lib")

#include "gui.h"

#include <yaml-cpp/yaml.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Schedule_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    YAML::Emitter out;
    out << "Hello, World!";
    std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"

    QFile res(":/styles");
    res.open(QIODevice::ReadOnly | QIODevice::Text);
    #define styles res.readAll().toStdString().c_str()
    app.setStyleSheet(styles);

    gui w;
    w.show();
    return app.exec();
}
