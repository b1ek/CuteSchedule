#ifndef GRADEVIEW_H
#define GRADEVIEW_H

#include <QWidget>

namespace Ui {
class gradeView;
}

class gradeView : public QWidget
{
    Q_OBJECT

public:
    explicit gradeView(QWidget *parent = nullptr);
    ~gradeView();

private:
    Ui::gradeView *ui;
};

#endif // GRADEVIEW_H
