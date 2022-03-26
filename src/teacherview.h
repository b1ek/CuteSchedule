#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QWidget>
#include <QStyleFactory>

#include "scheduleObjects/all.h"

namespace Ui {
class teacherview;
}

class teacherView : public QWidget {
    Q_OBJECT

public:
    explicit teacherView(QWidget *parent = nullptr);
    ~teacherView();

private:
    Ui::teacherview *ui;
};

#endif // TEACHERVIEW_H
