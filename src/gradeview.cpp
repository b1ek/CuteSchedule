#include "gradeview.h"
#include "ui_gradeview.h"

gradeView::gradeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeView)
{
    ui->setupUi(this);
}

void gradeView::setID(QString id) {
    ID = id;
    g = qbs::grade::allGrades[ID.toStdString()];
    ui->cabinet->setText(g.cabinet.c_str());
    ui->name->setText(g.name.c_str());
    ui->teacher->setText(g.tchr.name.c_str());
}

gradeView::~gradeView() {
    delete ui;
}
