#include "lessonview.h"
#include "ui_lessonview.h"

lessonView::lessonView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lessonView)
{
    ui->setupUi(this);
    lesn = qbs::lesson::Empty();
    refresh();
}

lessonView::~lessonView() {
    delete ui;
}

void lessonView::refresh() {

    ui->title->setText(locale::get(37));
    ui->name->setText(QString(locale::get(38)) + ' ' + lesn.name.c_str());
    ui->cabn->setText(QString(locale::get(39)) + ' ' + lesn.cabinet.c_str());
    ui->teacher->setText(QString(locale::get(40)) + ' ' + lesn.__teacher.fullName.c_str());

}

void lessonView::setID(const char* id) {
    lesn = qbs::lesson::find(id);
    refresh();
}
