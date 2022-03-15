#include "gui.h"
#include "./ui_gui.h"

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    this->setWindowState(Qt::WindowFullScreen);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    QList<QKeySequence> shortcuts;
    shortcuts << QKeySequence("Ctrl+Q") << QKeySequence("Escape");
    quitAction->setShortcuts(shortcuts);

    //QRect rec = QApplication::desktop()->screenGeometry();

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
    auto scr = QGuiApplication::primaryScreen()->geometry();

    ui->centralwidget->setMinimumSize(scr.size());

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




