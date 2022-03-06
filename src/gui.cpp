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

    std::cout << "Is it working?" << std::endl;
    //ui->buttonLeft->setEnabled(true);

    connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(on_buttonLeft_pressed()));

    //ui->peace->setStyle()

    ui->setupUi(this);

}

void gui::on_buttonLeft_pressed() {
    ui->mainMenu->hide();

    this->selectWidget = new gradeSelect(ui->menu);
    this->selectWidget->setLayout(ui->menu->layout());
    this->selectWidget->show();

    std::cout << "Pressed left button" << std::endl;
}
void gui::on_buttonRight_clicked() {
    std::cout << "Pressed right button" << std::endl;
}

gui::~gui()
{
    delete ui;
}


void gui::setTitle(QString value) {
    ui->uiTitle->setText(value);
}




