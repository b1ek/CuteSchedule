#ifndef GUI_H
#define GUI_H

#include "gradeselect.h"

#include <iostream>

#include <QMainWindow>
#include <QAction>
#include <QResource>
#include <QMessageBox>
#include <QKeySequence>
#include <QFile>

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
    void on_buttonLeft_clicked();
    void setTitle(QString text);

private:
    Ui::gui *ui;
    gradeSelect selectWidget;
};
#endif // GUI_H
