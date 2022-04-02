#ifndef NOLOAD
#include "fakeloader.h"
#include "ui_fakeloader.h"

void ssleep(long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

fakeloader::fakeloader(QWidget *parent) : fakeloader(Config(), parent) {}

void fakeloader::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
}

fakeloader::fakeloader(Config __conf, QWidget *parent) :
    QMainWindow(nullptr),
    ui(new Ui::fakeloader) {

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));
    request.setUrl(QUrl("http://cute.blek.codes/outdated.php?v=1.3.4"));
    manager->get(request);

    this->conf = __conf;
    timer_c = 0;
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(randint(10000));
    //this->setStyle(QStyleFactory::create("fusion"));
    //SetWindowLongPtrA((HWND)winId(), GWL_STYLE, WS_THICKFRAME);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    ssleep(1);
    ui->setupUi(this);
}

fakeloader::~fakeloader() {
    delete ui;
    delete timer;
    delete g;
    delete manager;
}

void fakeloader::launchApp() {
    timer->stop();
    this->close();

    ssleep(250);
    logger::log("Loading config...");
    for (int i = 1; i >= 8; i++) {
        ssleep(15);
        std::stringstream s;
        s << "Loading config... [" << i << "/8 chunks passed]";
        logger::log(s.str());
    }
    logger::log("Config loaded.");
    ssleep(150);
    logger::log("Starting services...");
    ssleep(5);
    logger::log("Nothing to start.");
    logger::log("Cleaning up...");
    ssleep(250);
    logger::log("Done.");
    logger::log("Launching app...");

    g = new gui(conf);
    g->show();
}

bool launch = false;
void fakeloader::update() {/*
    if (timer_c <= 20) {
        timer->setInterval(randint(150));
        ui->progressBar->setValue(timer_c);
        timer_c+= randint(5);
    } if (timer_c <= 40) {
        timer->setInterval(randint(200));
        ui->progressBar->setValue(timer_c);
        timer_c+= randint(4);
    } if (timer_c <= 60) {
        timer->setInterval(randint(250));
        ui->progressBar->setValue(timer_c);
        timer_c+= randint(3);
    } if (timer_c <= 70) {
        timer->setInterval(randint(300));
        ui->progressBar->setValue(timer_c);
        timer_c+= randint(2);
    } if (timer_c <= 80) {
        timer->setInterval(randint(300));
        ui->progressBar->setValue(timer_c);
        timer_c+= randint(8);
    } else {
        timer->setInterval(1);
        ui->progressBar->setValue(timer_c);
        timer_c++;
    }
    if (timer_c >= 90) {
        ui->progressBar->setValue(100);
        launch = true;
        timer->setInterval(randint(1000));
    }
    if (launch) {
        fakeloader::launchApp();
    }*/
    launchApp();
}
#endif // NOLOAD
