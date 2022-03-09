#ifndef GRADESELECT_H
#define GRADESELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

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

private:
    Ui::gradeSelect *ui;
};

#endif // GRADESELECT_H
