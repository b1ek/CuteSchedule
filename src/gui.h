#ifndef GUI_H
#define GUI_H

#include "gradeview.h"
#include "gradeselect.h"
#include "teacherview.h"
#include "config.h"
#include "manager.h"
#include "about.h"
#include "locale.h"
#include "lessonview.h"

#include <ctime>
#include <iostream>
#include <windows.h>
#include <strsafe.h>
#include <stdlib.h>

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
    void back();
    void warnNexit();
    void check();
    void posterightclick();
    void posterleftclick();
    void loop();
    void op_authr();

    void receive_selected_grade(QString id);
    void info_lesson(QString id);

private:
    inline long minutes(int c);

    uint64_t lastActive;
    long activeDelay;
    bool autoBackAllowed;

    QTimer *looper;

    Ui::gui *ui;

    gradeSelect *selector;
    gradeView *gview;
    teacherView *tview;
    lessonView *lesn;
    about *authr;

    Config conf;
    long lastExitPress;
    QString getConfParam(std::string query);
};
#endif // GUI_H
