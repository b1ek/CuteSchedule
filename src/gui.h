#ifndef GUI_H
#define GUI_H

#include "gradeview.h"
#include "gradeselect.h"
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
    void receive_selected_grade(QString id);
    void back();
    void check();
    void posterightclick();
    void posterleftclick();

private:
    Ui::gui *ui;
    gradeSelect *selectWidget;
    gradeView *gview;
    Config conf;
    QString getConfParam(std::string query);
};
#endif // GUI_H
