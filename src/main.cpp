#define LOGGER_DISABLED

#include "gui.h"
#include "fakeloader.h"

#include "config.h"
#include "scheduleObjects/all.h"
#include "logger.h"

#include <yaml-cpp/yaml.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include <QStyleFactory>

#define p std::cout
#define n std::endl
#define print(something) std::cout << something << std::endl
#define debug(something) qDebug() << something
#define RUN_APP

const char* author = "Forged in the depth of hell by blek | dave.black5840@gmail.com / creeperywime@gmail.com\ngithub@b1ek";

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");
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
    logger::init();
    logger::log("hii");;


#ifndef NOLOAD
    fakeloader fk;
    fk.show();
#else
    gui gui;
    gui.show();
#endif

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

    return 0;
}
