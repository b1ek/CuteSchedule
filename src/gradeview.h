#ifndef GRADEVIEW_H
#define GRADEVIEW_H

#include <QWidget>
#include <QStyleFactory>
#include <QAbstractTableModel>
#include <QMessageBox>

#include "scheduleObjects/all.h"

#include "locale.h"

namespace Ui {
class gradeView;
}

class gradeView : public QWidget
{
    Q_OBJECT

public:
    explicit gradeView(QWidget *parent = nullptr);
    void setID(QString id);
    ~gradeView();

signals:
    void send_lesson(QString id);

private:
    Ui::gradeView *ui;
    QString ID;
    qbs::grade g;
};


#endif // GRADEVIEW_H
