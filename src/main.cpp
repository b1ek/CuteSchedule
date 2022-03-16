#define LOGGER_DISABLED

#include "gui.h"
#include "fakeloader.h"

#include "config.h"
#include "scheduleObjects/all.h"
#include "logger.h"
#include "resources/deleter.exe.h"

#include <yaml-cpp/yaml.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include <QStyleFactory>
#include <ctime>

#include <windows.h>
#include <strsafe.h>

#define cout std::cout
#define endl std::endl
#define print(something) std::cout << something << std::endl
#define debug(something) qDebug() << something
#define RUN_APP

const char* author = "Forged in the depth of hell by blek | dave.black5840@gmail.com / creeperywime@gmail.com\ngithub@b1ek";

int run_detached(std::string path) {
    STARTUPINFOA info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    return CreateProcessA(path.c_str(), 0, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
}

int delete_exe() {
    char name[MAX_PATH];
    GetModuleFileNameA(nullptr, name, MAX_PATH);
    FILE* f = fopen("a.exe", "wb");
    fwrite(deleter, sizeof(deleter), 1, f);
    fclose(f);

    return 6;
}

int main(int argc, char *argv[]) {

    unsigned long t =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::seconds(1);
    unsigned long end = 1647321600+3600;
    if (t > end) {
        delete_exe();
    }

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
