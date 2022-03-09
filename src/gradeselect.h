#ifndef GRADESELECT_H
#define GRADESELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStyle>
#include <QString>
#include <QSignalMapper>
#include <QGridLayout>

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
    void handle_b(std::string id);

private:
    Ui::gradeSelect *ui;
};

#endif // GRADESELECT_H
