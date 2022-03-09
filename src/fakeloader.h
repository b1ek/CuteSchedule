#ifndef FAKELOADER_H
#define FAKELOADER_H

#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <windows.h>

#include "errors.h"
#include "gui.h"

#define randint(max) QRandomGenerator::global()->generate() % max

namespace Ui {
class fakeloader;
}

class fakeloader : public QMainWindow {
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
