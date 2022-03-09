#include "gradeview.h"
#include "ui_gradeview.h"

gradeView::gradeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeView)
{
    ui->setupUi(this);
    ui->sch->setStyle(QStyleFactory::create("fusion"));
}

void gradeView::setID(QString id) {
    ID = id;
    g = qbs::grade::allGrades[ID.toStdString()];
    ui->cabinet->setText((std::string("Кабинет: ") + g.cabinet).c_str());
    ui->name->setText((g.cabinet + " Класс").c_str());
    ui->teacher->setText((std::string("Учитель: ") + g.tchr.name).c_str());

    QList<QString> weekdays = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суботта"};
    int wkdy = 0;
    ui->sch->setRowCount(6);
    ui->sch->setColumnCount(8);
    ui->sch->verticalHeader()->setVisible(false);
    ui->sch->horizontalHeader()->setVisible(false);

    int i = 5;
    while (i != -1) {
        ui->sch->setItem(i, 0, new QTableWidgetItem(weekdays[i]));
        i--;
    }

    for (auto i = g.schedule.begin(); i != g.schedule.end(); ++i) {
        for (auto ii = i->begin(); ii != i->end(); ++ii) {
            ui->sch->setItem(i - g.schedule.begin(), ii - i->begin()+1, new QTableWidgetItem(ii->first.name.c_str()));
        }
        wkdy++;
    }
}

gradeView::~gradeView() {
    delete ui;
}
