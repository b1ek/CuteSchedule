#ifndef GUI_H
#define GUI_H

#include "gradeview.h"
#include "gradeselect.h"
#include "teacherview.h"
#include "config.h"

#include <ctime>
#include <iostream>
#include <windows.h>
#include <strsafe.h>

#include <QMainWindow>
#include <QAction>
#include <QResource>
#include <QMessageBox>
#include <QKeySequence>
#include <QFile>
#include <QScreen>
#include <QTimer>
#include <QDialogButtonBox>

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    gui(Config c);
    ~gui();

private slots:
    void setTitle(QString text);
    void buttonLeft_pressed();
    void buttonRight_press();
    void receive_selected_grade(QString id);
    void back();
    void warnNexit();
    void check();
    void posterightclick();
    void posterleftclick();

private:
    inline long minutes(int c);

    Ui::gui *ui;
    gradeSelect *selectWidget;
    gradeView *gview;
    teacherView *tview;
    Config conf;
    long lastExitPress;
    QString getConfParam(std::string query);
};
#endif // GUI_H
