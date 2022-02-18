#ifndef GRADESELECT_H
#define GRADESELECT_H

#include <QWidget>

namespace Ui {
class gradeSelect;
}

class gradeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit gradeSelect(QWidget *parent = nullptr);
    ~gradeSelect();

private:
    Ui::gradeSelect *ui;
};

#endif // GRADESELECT_H
