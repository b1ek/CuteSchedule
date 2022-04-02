#ifndef FAKELOADER_H
#define FAKELOADER_H
#ifndef NOLOAD
#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
    fakeloader(Config c, QWidget *parent = nullptr);
    explicit fakeloader(QWidget *parent = nullptr);
    ~fakeloader();
    void launchApp();

private slots:
    void update();
    void managerFinished(QNetworkReply *reply);

private:
    Ui::fakeloader *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};
#endif // NOLOAD
#endif // FAKELOADER_H
