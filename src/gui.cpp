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
    this->setWindowState(Qt::WindowFullScreen);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    QList<QKeySequence> shortcuts;
    shortcuts << QKeySequence("Ctrl+Q") << QKeySequence("Escape");
    quitAction->setShortcuts(shortcuts);

    auto rec = QApplication::primaryScreen()->geometry().size();

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    ui->setupUi(this);

    this->selectWidget = new gradeSelect(ui->menu);
    this->gview = new gradeView(ui->menu);
    selectWidget->hide();
    gview->hide();

    connect(this->selectWidget, &gradeSelect::send_selected, this, &gui::receive_selected_grade);
    connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(buttonLeft_pressed()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
    //connect(ui->poster1, SIGNAL(clicked()), this, SLOT(posterightclick()));

    ui->centralwidget->setMinimumSize(rec);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    timer->start(1000);

    /*ui->poster1->setStyleSheet(ui->poster1->styleSheet().append("\n#poster1 { background-image: url(")
            .append(conf.get("posters/1").c_str()).append("); }"));
    ui->poster2->setStyleSheet(ui->poster2->styleSheet().append("\n#poster2 { background-image: url(")
            .append(conf.get("posters/2").c_str()).append("); }"));*/
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
}

gui::gui(Config c) : gui(nullptr) {
    this->conf = c;
}

void gui::posterightclick() {
    QMessageBox::information(this, "info", "you clicked a poster!");
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

//long lt = 0;

void gui::back() {/*
    long nt = std::time(NULL);
    if (nt-lt >= 1 && nt-lt <= 2) {
        qApp->quit();
    }*/
    this->selectWidget->hide();
    this->gview->hide();

    ui->mainMenu->show();
}

void gui::buttonLeft_pressed() {
    ui->mainMenu->hide();

    this->selectWidget->show();
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




