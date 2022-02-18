#include "gui.h"
#include "./ui_gui.h"

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);
    //this->setWindowState(Qt::WindowFullScreen);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    QList<QKeySequence> shortcuts;
    shortcuts << QKeySequence("Ctrl+Q") << QKeySequence("Escape");
    quitAction->setShortcuts(shortcuts);


    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    this->selectWidget.setParent(ui->menu);
    std::cout << "Is it working?" << std::endl;
    ui->buttonLeft->setEnabled(true);
}

gui::~gui()
{
    delete ui;
}

void gui::on_buttonLeft_clicked() {
    ui->mainMenu->setMaximumHeight(0);
    std::cout << "You clicked a button!" << std::endl;
    this->selectWidget.show();
    this->setTitle("Выберите класс");
}
void gui::setTitle(QString value) {
    ui->uiTitle->setText(value);
}
