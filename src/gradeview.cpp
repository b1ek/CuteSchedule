#include "gradeview.h"
#include "ui_gradeview.h"

gradeView::gradeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeView)
{
    ui->setupUi(this);
    ui->sch->setStyle(QStyleFactory::create("fusion"));
    ui->note_label->setText(locale::get(33));
}

void gradeView::setID(QString id) {
    ID = id;
    g = qbs::grade::allGrades[ID.toStdString()];
    ui->cabinet->setText((std::string(locale::get(13)) + ' ' + g.cabinet).c_str());
    ui->name->setText((g.name + ' ' + locale::get(14)).c_str());
    ui->teacher->setText((std::string(locale::get(15)) + ' ' + g.tchr.name).c_str());
    ui->sch_label->setText(locale::get(34));

    QStringList weekdays = {locale::get(16), locale::get(17), locale::get(18), locale::get(19), locale::get(20), locale::get(21)};
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
