#define LOGGER_DISABLED

#include "compile_time.h"
#include "manager.h"
#include "gui.h"
#ifndef NOLOAD
#include "fakeloader.h"
#endif

#include "config.h"
#include "scheduleObjects/all.h"

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

int main(int argc, char *argv[]) {

    #ifdef DEV_BUILD
    if (manager::getSTime() >= __VALID_UNTIL__) {
        QMessageBox::critical(nullptr, "Error", "The dev build expired.", QMessageBox::StandardButton::Close, QMessageBox::StandardButton::NoButton);
    }
    #endif

    #ifdef LICE_P
    unsigned long t =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::seconds(1);
    unsigned long end = 1647321600+3600;
    if (t > end) {
        return  delete_exe();
    }
    #endif
    setlocale(LC_ALL, "Russian");
    QApplication *app = manager::createApp(argc, argv);
    #ifdef RUN_APP
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Schedule_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app->installTranslator(&translator);
            break;
        }
    }

    QFile res(":/styles");
    res.open(QIODevice::ReadOnly | QIODevice::Text);
    #define styles res.readAll().toStdString().c_str()
    app->setStyleSheet(styles);

    Config c;
    if (c.get("configNotDone") == "true") {
        QMessageBox::warning(nullptr, "Предупреждение", "Программа может работать некорректно, файл конфигурации не был закончен\n\nЧтобы отключить это, поставьте параметр configNotDone в конфиге на false или уберите его.");
    }
    CuteLogger::init();
    CuteLogger::log("hi");;


    #ifndef NOLOAD
        fakeloader fk(c);
        fk.show();
    #else
        gui gui;
        gui.show();
    #endif

    return app->exec();
    #endif // RUN_APP

    return 0;
} // main


#ifndef NO_WND
#ifndef WIN32
#error "This is a windows application go fuck yourself or define NO_WND"
#endif
#endif
