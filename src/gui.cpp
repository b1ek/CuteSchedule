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

    QAction *quitAction = new QAction();
    QList<QKeySequence> shortcuts = { QKeySequence("Ctrl+Q"), QKeySequence("Ctrl+Shift+Q") };
    quitAction->setShortcuts(shortcuts);

    QObject::connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);
    quitAction->setEnabled(true);

    auto rec = QApplication::primaryScreen()->geometry().size();

    ui->setupUi(this);

    ui->ver_data->setText("CuteSchedule ver. " VERSION " | (c) blek! All rights reserved.");

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
    this->lesn = new lessonView(ui->menu);
    this->authr = new about(ui->menu);
    selector->hide();
    gview->hide();
    tview->hide();
    lesn->hide();
    authr->hide();
    connect(ui->about, SIGNAL(clicked()), this, SLOT(op_authr()));
    connect(this->selector, &gradeSelect::send_selected, this, &gui::receive_selected_grade);
    connect(this->gview, &gradeView::send_lesson, this, &gui::info_lesson);

    if (QFile::exists(getConfParam("posters/1"))) {
        ui->poster1->setStyleSheet(QString("background: url(").append(getConfParam("posters/1")).append(");\n"));
        ui->p1warning->hide();
    } else {
        ui->p1warning->setStyleSheet("background: url(:/noposter)");
        ui->p2warning->show();
    } if (QFile::exists(getConfParam("posters/2"))) {
        ui->poster2->setStyleSheet(QString("background: url(").append(getConfParam("posters/2")).append(");"));
        ui->p2warning->hide();
    } else {
        ui->p2warning->setStyleSheet("background: url(:/noposter)");
        ui->p2warning->show();
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


    // localization
    ui->bottom_logo_text->setText(locale::get(4));
    ui->uiTitle->setText(locale::get(5));
    ui->buttonLeft->setText(locale::get(6));
    ui->buttonRight->setText(locale::get(7));
    ui->about->setText(locale::get(8));
    ui->exit->setText(locale::get(9));
    ui->back->setText(locale::get(10));
    if (std::string(locale::get(11)).find("github@b1ek") != std::string::npos) {
        ui->footer->setText(locale::get(11));
    }
    ui->perr1->setText(locale::get(12));
    ui->perr2->setText(locale::get(12));
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
    out << manager::getDate(locale::get(3));
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
    this->lesn->hide();
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
    delete looper;
    delete selector;
    delete gview;
    delete tview;
    delete lesn;
    delete authr;
}


void gui::setTitle(QString value) {
    lastActive = manager::getMSTime();
    ui->uiTitle->setText(value);
}

void gui::receive_selected_grade(QString id) {
    back();
    lastActive = manager::getMSTime();

    this->gview->setID(id);
    ui->mainMenu->hide();
    this->gview->show();
}

void gui::info_lesson(QString id) {
    back();
    lesn->setID(id.toStdString().c_str());
    ui->mainMenu->hide();
    lesn->show();
}
