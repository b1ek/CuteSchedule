#ifndef GRADESELECT_H
#define GRADESELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStyle>
#include <QString>
#include <QSignalMapper>
#include <iostream>

#include "scheduleObjects/all.h"

namespace Ui {
class gradeSelect;
}

class gradeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit gradeSelect(QWidget *parent = nullptr);
    void setupUi();
    ~gradeSelect();

private slots:
    void handle_bclick();

private:
    Ui::gradeSelect *ui;
};

#endif // GRADESELECT_H
