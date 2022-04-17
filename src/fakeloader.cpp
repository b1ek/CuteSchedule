#ifndef NOLOAD
#include "fakeloader.h"
#include "ui_fakeloader.h"

void ssleep(long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

fakeloader::fakeloader(QWidget *parent) : fakeloader(Config(), parent) {}

void fakeloader::managerFinished(QNetworkReply *reply) {
#ifndef DEV_BUILD
    if (reply->error() || versionCheckd) {
        return;
    }

    QString answer = reply->readAll();
    QString ch = VERSION"+";
    ch += std::to_string((uint64_t) floor(manager::getSTime() / 3600)).c_str();
    QString hash = (QCryptographicHash::hash(ch.toLocal8Bit(), QCryptographicHash::Sha256)).toHex();
    if (answer != hash && !versionCheckd) {
        QMessageBox::warning(nullptr, "Warning", "The program is outdated. I recommend to download the newest version from the official site (cute.blek.codes).");
    }
    versionCheckd = true;
#endif // DEV_BUILD
}

void fakeloader::validate() {
    request.setUrl(QUrl("http://cute.blek.codes/outdated.php?v=" VERSION));
    manager->get(request);
    lt->setInterval(randint(60000));
}

fakeloader::fakeloader(Config __conf, QWidget *parent) :
    QMainWindow(nullptr),
    ui(new Ui::fakeloader) {
    versionCheckd = false;

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));
    lt = new QTimer();
    lt->setInterval(1);
    connect(lt, SIGNAL(timeout()), this, SLOT(validate()));
    lt->start();

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

#ifndef DEV_BUILD
    ssleep(250);
    CuteLogger::log("Loading config...");
    for (int i = 1; i >= 8; i++) {
        ssleep(15);
        std::stringstream s;
        s << "Loading config... [" << i << "/8 chunks passed]";
        CuteLogger::log(s.str().c_str());
    }
    CuteLogger::log("Config loaded.");
    ssleep(150);
    CuteLogger::log("Starting services...");
    ssleep(5);
    CuteLogger::log("Nothing to start.");
    CuteLogger::log("Cleaning up...");
    ssleep(250);
    CuteLogger::log("Done.");
    CuteLogger::log("Launching app...");
#endif // DEV_BUILD

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
    /*if (versionCheckd)*/ launchApp();
}
#endif // NOLOAD
