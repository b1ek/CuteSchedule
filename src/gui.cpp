#include "gui.h"
#include "./ui_gui.h"

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    //this->setWindowState(Qt::WindowFullScreen);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    QList<QKeySequence> shortcuts;
    shortcuts << QKeySequence("Ctrl+Q") << QKeySequence("Escape");
    quitAction->setShortcuts(shortcuts);

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    ui->setupUi(this);
}

void gui::on_buttonLeft_pressed() {
    ui->mainMenu->hide();

    this->selectWidget = new gradeSelect(ui->menu);
    this->selectWidget->setLayout(ui->menu->layout());
    this->selectWidget->show();
    connect(this->selectWidget, &gradeSelect::send_selected, this, &gui::receive_selected_grade);
}

gui::~gui() {
    delete ui;
}

void gui::receive_selected_grade(QString id) {
    this->selectWidget->close();
    disconnect(this->selectWidget, &gradeSelect::send_selected, this, &gui::receive_selected_grade);
    delete selectWidget;

    this->gview = new gradeView();
    this->gview->setID(id);
    this->gview->setLayout(ui->menu->layout());
    this->gview->show();
}


void gui::setTitle(QString value) {
    ui->uiTitle->setText(value);
}




