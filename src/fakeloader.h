#ifndef FAKELOADER_H
#define FAKELOADER_H
#ifndef NOLOAD
#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyleFactory>

#include <chrono>
#include <thread>

#include "errors.h"
#include "gui.h"
#include "logger.h"
#include "config.h"

#define randint(max) QRandomGenerator::global()->generate() % max

namespace Ui {
class fakeloader;
}

class fakeloader  : public QMainWindow {
    Q_OBJECT
    QTimer * timer;
    gui *g;
    int timer_c;
    Config conf;

public:
    explicit fakeloader(QWidget *parent = nullptr);
    fakeloader(Config c);
    ~fakeloader();
    void launchApp();

private slots:
    void update();

private:
    Ui::fakeloader *ui;
};
#endif // NOLOAD
#endif // FAKELOADER_H
