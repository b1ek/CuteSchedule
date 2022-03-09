#include "gradeview.h"
#include "ui_gradeview.h"

gradeView::gradeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeView)
{
    ui->setupUi(this);
}

gradeView::~gradeView()
{
    delete ui;
}
