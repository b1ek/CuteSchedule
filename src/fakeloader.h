#ifndef FAKELOADER_H
#define FAKELOADER_H
#ifndef NOLOAD
#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCryptographicHash>

#include <chrono>
#include <thread>
#include <math.h>

#include "errors.h"
#include "gui.h"
#include "cutelogger.h"
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
    void validate();
    void managerFinished(QNetworkReply *reply);

private:
    Ui::fakeloader *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QTimer *lt;
    bool versionCheckd;
    bool shouldBeClosed;
};
#endif // NOLOAD
#endif // FAKELOADER_H
