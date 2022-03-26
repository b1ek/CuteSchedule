#include "teacherview.h"
#include "ui_teacherview.h"

teacherView::teacherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherview)
{
    ui->setupUi(this);
    ui->teachersS->hide();
    ui->teachersS->setStyle(QStyleFactory::create("fusion"));
    ui->teachersS->verticalHeader()->setVisible(false);
    ui->teachersS->setColumnCount(6);
    ui->teachersS->setRowCount(qbs::teacher::allTeachers.size());

#define allT qbs::teacher::allTeachers
    ui->teachersS->setRowCount(allT.size());

    ui->teachersS->setHorizontalHeaderLabels(QStringList({"ID", "Имя", "Полное имя", "Кабинет"}));

    int i = 0;
    for (auto tchr = allT.begin(); tchr != allT.end(); ++tchr) {
#define t tchr->second
        auto id = new QTableWidgetItem(tchr->first.c_str());
        //id->setFont(QFont("Segoe UI", -1, QFont::Bold, false));
        ui->teachersS->setItem(i, 0, id);

        auto name = new QTableWidgetItem(t.name.c_str());
        ui->teachersS->setItem(i, 1, name);

        auto fname = new QTableWidgetItem(t.fullName.c_str());
        fname->setFont(QFont("Segoe UI", 9, -1, false));
        ui->teachersS->setItem(i, 2, fname);
        i++;
    }
#undef allT

    ui->teachersS->show();
}

teacherView::~teacherView() {
    delete ui;
}
