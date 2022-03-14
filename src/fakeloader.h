#ifndef FAKELOADER_H
#define FAKELOADER_H

#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <QThread>

#include "errors.h"
#include "gui.h"
#include "logger.h"

#define randint(max) QRandomGenerator::global()->generate() % max
class Sleeper {
public:
    static void msleep(long ms) {QThread::msleep(ms);}
};

#define Sleep(ms) Sleeper::msleep(ms)

namespace Ui {
class fakeloader;
}

class fakeloader  : public QMainWindow {
    Q_OBJECT
    QTimer * timer;
    gui *g;
    int timer_c;

public:
    explicit fakeloader(QWidget *parent = nullptr);
    ~fakeloader();
    void launchApp();

private slots:
    void update();

private:
    Ui::fakeloader *ui;
};

#endif // FAKELOADER_H
