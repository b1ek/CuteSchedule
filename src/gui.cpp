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

    this->selectWidget = new gradeSelect(ui->menu);
    this->gview = new gradeView(ui->menu);
    this->tview = new teacherView(ui->menu);
    selectWidget->hide();
    gview->hide();
    tview->hide();
    connect(this->selectWidget, &gradeSelect::send_selected, this, &gui::receive_selected_grade);

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

    buttonRight_press();
    raise();
    show();
}

inline long gui::minutes(int c) {
    return c * 60;
}

void gui::warnNexit() {/*
    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Предупреждение о выходе из программы");
    msg->setText("Выходите из программы только если вы уверены, что делаете.\n"
                 "Любые не санкционированные действия(удаление файлов, запуск неизвестных программ) будут преследоваться.\n\n"
                 "Если вы точно хотите выйти, закройте это окно и нажмите кнопку выхода ещё раз.");
    msg->addButton(QMessageBox::Ok);
    msg->show();*/
    qApp->exit(7);

}

gui::gui(Config c) : gui(nullptr) {
    this->conf = c;
}

void gui::posterightclick() {
    //QMessageBox::information(this, "info", "you clicked a poster!");
}

void gui::posterleftclick() {

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
    this->selectWidget->hide();
    this->gview->hide();
    this->tview->hide();

    ui->mainMenu->show();
}

void gui::buttonRight_press() {
    back();
    ui->mainMenu->hide();

    tview->show();
}

void gui::buttonLeft_pressed() {
    back();
    ui->mainMenu->hide();

    selectWidget->show();
}

gui::~gui() {
    delete ui;
}

void gui::receive_selected_grade(QString id) {
    this->selectWidget->hide();

    this->gview->setID(id);
    this->gview->show();
}


void gui::setTitle(QString value) {
    ui->uiTitle->setText(value);
}
