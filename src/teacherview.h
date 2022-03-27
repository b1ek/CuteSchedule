#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QWidget>
#include <QStyleFactory>
#include <QTimer>

#include "scheduleObjects/all.h"

namespace Ui {
class teacherview;
}

class teacherView : public QWidget {
    Q_OBJECT

public:
    explicit teacherView(QWidget *parent = nullptr);
    ~teacherView();

private slots:
    void hd_note();
    void sw_note();
    void hideEvent(QHideEvent* e);

private:
    Ui::teacherview *ui;
};

#endif // TEACHERVIEW_H
