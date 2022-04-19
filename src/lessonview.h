#ifndef LESSONVIEW_H
#define LESSONVIEW_H

#include <QWidget>

#include "scheduleObjects/lesson.h"
#include "locale.h"

namespace Ui {
class lessonView;
}

class lessonView : public QWidget
{
    Q_OBJECT

public:
    explicit lessonView(QWidget *parent = nullptr);
    ~lessonView();
    void setID(const char* id);
    void refresh();

private:
    Ui::lessonView *ui;
    qbs::lesson lesn;
    QString lesn_id;
};

#endif // LESSONVIEW_H
