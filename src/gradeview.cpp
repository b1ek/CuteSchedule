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

    QStringList weekdays = {locale::get(16), locale::get(36),
                            locale::get(17), locale::get(36),
                            locale::get(18), locale::get(36),
                            locale::get(19), locale::get(36),
                            locale::get(20), locale::get(36),
                            locale::get(21), locale::get(36),};
    int wkdy = 0;
    ui->sch->setRowCount(7);
    ui->sch->setColumnCount(12);
    ui->sch->verticalHeader()->setVisible(false);
    ui->sch->setHorizontalHeaderLabels(weekdays);
    ui->sch->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sch->setFocusPolicy(Qt::NoFocus);
    ui->sch->setSelectionMode(QAbstractItemView::NoSelection);

    int row = 0;
    int col;
    int mxcb = 0;
    for (auto i = g.schedule.begin(); i != g.schedule.end(); ++i) {
        col = 0; mxcb = 0;
        for (auto ii = i->begin(); ii != i->end(); ++ii) {
            auto les = new QTableWidgetItem(ii->first.name.c_str());
            les->setTextAlignment(Qt::AlignCenter);
            ui->sch->setItem(row, col, les);
            col++;

            auto cab = new QTableWidgetItem(ii->first.cabinet.c_str());
            cab->setTextAlignment(Qt::AlignCenter);
            ui->sch->setItem(row, col, cab);

            auto sz = QFontMetrics(cab->font());
            if (mxcb < sz.horizontalAdvance(ii->first.cabinet.c_str()) + 8) {
                mxcb = sz.horizontalAdvance(ii->first.cabinet.c_str()) + 8;
            }
            ui->sch->setColumnWidth(col, mxcb);
            col++;
        }
        row++;
    }

    connect(ui->sch, &QTableWidget::cellClicked, this, [this](int row, int col){
        if (col % 2 == 0) {
            //QMessageBox::information(nullptr, "You clicked on", g.schedule.at(row).at(col).first.name.c_str());
            this->send_lesson(g.schedule.at(row).at(col).second.c_str());
        }
    });
}

gradeView::~gradeView() {
    delete ui;
}
