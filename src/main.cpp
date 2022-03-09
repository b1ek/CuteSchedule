#define LOGGER_DISABLED

#include "gui.h"
#include "config.h"
#include "scheduleObjects/grade.h"
#include "scheduleObjects/teacher.h"
#include "logger.h"

#include <windows.h>
#include <yaml-cpp/yaml.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#define p std::cout
#define n std::endl
#define print(something) std::cout << something << std::endl
#define debug(something) qDebug() << something
//#define RUN_APP

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);
    QApplication app(argc, argv);
    #ifdef RUN_APP
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Schedule_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QFile res(":/styles");
    res.open(QIODevice::ReadOnly | QIODevice::Text);
    #define styles res.readAll().toStdString().c_str()
    app.setStyleSheet(styles);

    Config c;
    logger::regConfig(c);
    logger::init();

    gui w;
    w.show();
    return app.exec();
    #endif

    /*Config *conf = new Config();
    bool exists = true;
    auto node = conf->getNode("", exists)["classes"].as<std::map<std::string, std::map<std::string, std::vector<std::string>>>>();
    for (auto i = node.begin(); i != node.end(); ++i) {
        debug(i->first.c_str());
        debug(i->second.begin()->first.c_str());
        for (auto ii = i->second.begin(); ii != i->second.end(); ++ii) {
            for(auto _i = ii->second.begin(); _i != ii->second.end(); ++_i) {
                debug(_i->c_str());
            }
        }
    }*/
    Config c;

    return 0;
}
