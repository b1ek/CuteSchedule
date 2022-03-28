#ifndef LICENSE_WINDOW_H
#define LICENSE_WINDOW_H

#include <QWidget>

namespace Ui {
class license_window;
}

class license_window : public QWidget
{
    Q_OBJECT

public:
    explicit license_window(QWidget *parent = nullptr);
    ~license_window();

private:
    Ui::license_window *ui;
};

#endif // LICENSE_WINDOW_H
