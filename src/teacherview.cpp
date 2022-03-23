#include "teacherview.h"
#include "ui_teacherview.h"

teacherView::teacherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherview)
{
    ui->setupUi(this);
}

teacherView::~teacherView() {
    delete ui;
}
