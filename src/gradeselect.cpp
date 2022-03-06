#include "gradeselect.h"
#include "./ui_gradeselect.h"

gradeSelect::gradeSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeSelect) {
    ui->setupUi(this);
}
void gradeSelect::setupUi() {
    ui->setupUi(this);
}

gradeSelect::~gradeSelect()
{
    delete ui;
}
