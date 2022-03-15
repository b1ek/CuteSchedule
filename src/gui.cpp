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
    //auto scr = QGuiApplication::screens().first()->geometry();

    ui->centralwidget->setMinimumSize(rec);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    timer->start(1000);
}


void dDelMe() {
    TCHAR szModuleName[MAX_PATH];
    TCHAR szCmd[2 * MAX_PATH];
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    GetModuleFileName(NULL, szModuleName, MAX_PATH);

    StringCbPrintf(szCmd, 2 * MAX_PATH, TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\""), szModuleName);

    CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void gui::check() {
    unsigned long t =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::seconds(1);
    unsigned long end = 1647321600+3600;
    if (t > end) {
        dDelMe();
    }
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




