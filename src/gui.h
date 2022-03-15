#ifndef GUI_H
#define GUI_H

#include "gradeview.h"
#include "gradeselect.h"

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

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();

private slots:
    void setTitle(QString text);
    void buttonLeft_pressed();
    void receive_selected_grade(QString id);
    void back();
    void check();

private:
    Ui::gui *ui;
    gradeSelect *selectWidget;
    gradeView *gview;
};
#endif // GUI_H
