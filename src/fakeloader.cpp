#include "fakeloader.h"
#include "ui_fakeloader.h"

fakeloader::fakeloader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fakeloader)
{
    timer_c = 0;
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);
    //this->setStyle(QStyleFactory::create("fusion"));
    //SetWindowLongPtrA((HWND)winId(), GWL_STYLE, WS_THICKFRAME);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    Sleep(750);
}

fakeloader::~fakeloader() {
    delete ui;
    delete timer;
    delete g;
}

void fakeloader::launchApp() {
    timer->stop();
    g = new gui();
    g->show();
    this->close();
}

bool launch = false;
void fakeloader::update() {
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
    }
}
