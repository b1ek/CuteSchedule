#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QWidget>

namespace Ui {
class teacherview;
}

class teacherView : public QWidget
{
    Q_OBJECT

public:
    explicit teacherView(QWidget *parent = nullptr);
    ~teacherView();

private:
    Ui::teacherview *ui;
};

#endif // TEACHERVIEW_H
