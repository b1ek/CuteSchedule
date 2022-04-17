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

    if (reply->rawHeader(QString("Authority").toLocal8Bit()) != QString("true").toLocal8Bit()) {
        return;
    }
    QString answer = reply->readAll();
    QString ch = VERSION"+";
    ch += std::to_string((uint64_t) floor(manager::getSTime() / 3600)).c_str();
    QString hash = (QCryptographicHash::hash(ch.toLocal8Bit(), QCryptographicHash::Sha256)).toHex();
    if (answer != hash && !versionCheckd) {
        QMessageBox::warning(nullptr, locale::get(31), locale::get(32));
    }
    versionCheckd = true;
#endif // DEV_BUILD
}

void fakeloader::validate() {
    if (!versionCheckd) {
        request.setUrl(QUrl("http://cute.blek.codes/outdated.php"));
        manager->get(request);
        lt->setInterval(randint(60000));
    }
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
#ifndef DEV_BUILD
    ui->label->setText("Version " VERSION);
#else
    ui->label->setText("Version " VERSION " DEV BUILD");
#endif
}

fakeloader::~fakeloader() {
    delete ui;
    delete timer;
    delete g;
    delete manager;
}

bool openedGui = false;
void fakeloader::launchApp() {
    shouldBeClosed = true;
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

    if (!openedGui) {
        g = new gui(conf);
        g->show();
        openedGui = true;
    }
}

bool launch = false;
void fakeloader::update() {
    timer->setInterval(15);

    if (shouldBeClosed) {
        this->close();
        timer->stop();
    } else {
        launchApp();
    }
}
#endif // NOLOAD
