#ifndef NOLOAD
#include "fakeloader.h"
#include "ui_fakeloader.h"

void ssleep(long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

fakeloader::fakeloader(QWidget *parent) : fakeloader(Config(), parent) {}

fakeloader::fakeloader(Config __conf, QWidget *parent) :
    QMainWindow(nullptr),
    ui(new Ui::fakeloader) {
    versionCheckd = false;

    c = Config();

    QAction *quitAction = new QAction();
    QList<QKeySequence> shortcuts = { QKeySequence("Ctrl+Q"), QKeySequence("Ctrl+Shift+Q") };
    quitAction->setShortcuts(shortcuts);

    QObject::connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);
    quitAction->setEnabled(true);

    this->conf = __conf;
    timer_c = 0;
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(manager::getRND(1000, 2000));
    guiOpened = false;
    //this->setStyle(QStyleFactory::create("fusion"));
    //SetWindowLongPtrA((HWND)winId(), GWL_STYLE, WS_THICKFRAME);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
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

int step = 0;

void fakeloader::update() {
    if (NOT(guiOpened)) {
        g = new gui();
        g->show();
        close();
        guiOpened = true;
    }

}
#endif // NOLOAD
