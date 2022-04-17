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

    QStringList weekdays = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суботта"};
    int wkdy = 0;
    ui->sch->setRowCount(7);
    ui->sch->setColumnCount(6);
    ui->sch->verticalHeader()->setVisible(false);
    ui->sch->setHorizontalHeaderLabels(weekdays);

    for (auto i = g.schedule.begin(); i != g.schedule.end(); ++i) {
        for (auto ii = i->begin(); ii != i->end(); ++ii) {
            auto item =  new QTableWidgetItem(ii->first.name.c_str());
            item->setTextAlignment(Qt::AlignCenter);
            // item->setForeground(QBrush(QColor::fromRgb(128, 0, 0)));
            ui->sch->setItem(ii - i->begin(), i - g.schedule.begin(), item);
        }
        wkdy++;
    }
}

gradeView::~gradeView() {
    delete ui;
}
