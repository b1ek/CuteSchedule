#include "gui.h"
#include "./ui_gui.h"
#define str std::string

str replace(str base, str sub, str repl) {
    return base.replace(base.find(sub), sub.length(), repl);
}

str getCD() {
    char name[MAX_PATH];
    GetModuleFileNameA(nullptr, name, MAX_PATH);
    return name;
}

QString gui::getConfParam(str query) {
    auto a = conf.get(query);
    return a.c_str();
}


gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    setWindowState(Qt::WindowFullScreen);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    QList<QKeySequence> shortcuts;
    shortcuts << QKeySequence("Ctrl+Q") << QKeySequence("Escape");
    quitAction->setShortcuts(shortcuts);

    auto rec = QApplication::primaryScreen()->geometry().size();

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    ui->setupUi(this);

    connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(buttonLeft_pressed()));
    connect(ui->buttonRight, SIGNAL(clicked()), this, SLOT(buttonRight_press()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(warnNexit()));

    ui->centralwidget->setMinimumSize(rec);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    timer->start(1000);

    this->selector = new gradeSelect(ui->menu);
    this->gview = new gradeView(ui->menu);
    this->tview = new teacherView(ui->menu);
    this->authr = new about(ui->menu);
    selector->hide();
    gview->hide();
    tview->hide();
    authr->hide();
    connect(ui->about, SIGNAL(clicked()), this, SLOT(op_authr()));
    connect(this->selector, &gradeSelect::send_selected, this, &gui::receive_selected_grade);

    if (QFile::exists(getConfParam("posters/1"))) {
        ui->poster1->setStyleSheet(QString("background: url(").append(getConfParam("posters/1")).append(");\n"));
        ui->p1warning->setStyleSheet("background: none;");
    } else {
        ui->p1warning->setStyleSheet("background: url(:/noposter)");
    } if (QFile::exists(getConfParam("posters/2"))) {
        ui->poster2->setStyleSheet(QString("background: url(").append(getConfParam("posters/2")).append(");"));
        ui->p2warning->setStyleSheet("background: none;");
    } else {
        ui->p2warning->setStyleSheet("background: url(:/noposter)");
    }

    if (conf.get("config/noposters") == "true") {
        ui->poster1->hide();
        ui->poster2->hide();
    }

    if (manager::isNumber(conf.get("config/activeDelay").c_str())) {
        activeDelay = atoi(conf.get("config/activeDelay").c_str());
    } else {activeDelay = 60000;}
    autoBackAllowed = true;
    if (conf.get("config/noAutoBack") != "(null)") {
        autoBackAllowed = false;
    }

    show();
    setWindowFlags(Qt::WindowStaysOnTopHint);
    Sleep(1);
    setWindowFlags(windowFlags() ^ Qt::WindowStaysOnTopHint);

    looper = new QTimer();
    looper->start(1);
    connect(looper, SIGNAL(timeout()), this, SLOT(loop()));
}

void gui::op_authr() {
    back();
    ui->mainMenu->hide();
    this->authr->show();
}

void gui::loop() {
    if (manager::getMSTime() - lastActive >= activeDelay && autoBackAllowed) {
        back();
    }
}

inline long gui::minutes(int c) {
    return c * 60;
}

void gui::warnNexit() {
    std::ofstream out("lastExit.txt");
    out << "В последний раз выход был выполнен: " << manager::getDate("%mго месяца %d дня %Y года %H:%M:%S\n");
    out.close();
    manager::quit(7);

}

gui::gui(Config c) : gui(nullptr) {
    this->conf = c;
}

void gui::posterightclick() {
    lastActive = manager::getMSTime();
    //QMessageBox::information(this, "info", "you clicked a poster!");
}

void gui::posterleftclick() {
    lastActive = manager::getMSTime();

}
void gui::check() {
#ifdef LICE_P
    unsigned long t =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::seconds(1);
    unsigned long end = 1647321600+3600;
    if (t > end) {
        qApp->exit(6);
    }
#endif
}

void gui::back() {
    lastActive = manager::getMSTime();
    this->selector->hide();
    this->gview->hide();
    this->tview->hide();
    this->authr->hide();

    ui->mainMenu->show();
}

void gui::buttonRight_press() {
    lastActive = manager::getMSTime();
    back();
    ui->mainMenu->hide();

    tview->show();
}

void gui::buttonLeft_pressed() {
    lastActive = manager::getMSTime();
    back();
    ui->mainMenu->hide();

    selector->show();
}

gui::~gui() {
    delete ui;
}

void gui::receive_selected_grade(QString id) {
    lastActive = manager::getMSTime();
    this->selector->hide();

    this->gview->setID(id);
    this->gview->show();
}


void gui::setTitle(QString value) {
    lastActive = manager::getMSTime();
    ui->uiTitle->setText(value);
}
