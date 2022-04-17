#include "teacherview.h"
#include "ui_teacherview.h"

teacherView::teacherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherview)
{
    ui->setupUi(this);
    hide();


    ui->teachersS->setStyle(QStyleFactory::create("fusion"));
    ui->teachersS->verticalHeader()->setVisible(false);
    ui->teachersS->setColumnCount(5);
    ui->teachersS->setRowCount(qbs::teacher::allTeachers.size());

#define allT qbs::teacher::allTeachers
    ui->teachersS->setRowCount(allT.size());

    ui->teachersS->setHorizontalHeaderLabels(QStringList({locale::get(22), locale::get(23), locale::get(24), locale::get(25), locale::get(26)}));
    int i = 0;
    int ttlw = 0;
    for (auto tchr = allT.begin(); tchr != allT.end(); ++tchr) {
#define t tchr->second
#define font_sz 4
        auto id = new QTableWidgetItem(tchr->first.c_str());
        id->setFont(QFont("Segoe UI", -1, -1, true));
        if (tchr->first.size() * (font_sz-2) >= ui->teachersS->columnWidth(0)) {
            ui->teachersS->setColumnWidth(1, tchr->first.size() * (font_sz-2));
            ttlw += tchr->first.size()*(font_sz-2);
        }
        ui->teachersS->setItem(i, 0, id);

        auto name = new QTableWidgetItem(t.name.c_str());
        name->setFont(QFont("Segoe UI", 9, -1, false));
        ui->teachersS->setItem(i, 1, name);
        if (t.name.size() * font_sz >= ui->teachersS->columnWidth(1)) {
            ui->teachersS->setColumnWidth(1, t.name.size() * font_sz);
            ttlw += t.name.size()*font_sz;
        }

        auto fname = new QTableWidgetItem(t.fullName.c_str());
        fname->setFont(QFont("Segoe UI", 9, -1, false));
        ui->teachersS->setItem(i, 2, fname);
        if (t.fullName.size() *font_sz >= ui->teachersS->columnWidth(2)) {
            ui->teachersS->setColumnWidth(2, t.fullName.size() * font_sz);
            ttlw += t.fullName.size()*font_sz;
        }

        auto cab = new QTableWidgetItem(t.cabinet.c_str());
        cab->setFont(QFont("Segoe UI", 9, -1, false));
        ui->teachersS->setItem(i, 3, cab);
        if (t.cabinet.size() * (font_sz) >= ui->teachersS->columnWidth(3)) {
            ui->teachersS->setColumnWidth(3, t.cabinet.size()*(font_sz));
            ttlw += t.cabinet.size()*(font_sz);
        }

        ui->teachersS->setItem(i, 4, new QTableWidgetItem(locale::get(27)));

        ui->teachersS->setRowHeight(i, 20);

        i++;
    }

    if (ttlw >= 640) ttlw = 600;

    ui->teachersS->setMinimumWidth(ttlw);
    ui->teachersS->setMaximumWidth(ttlw);
    ui->teachersS->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

#undef t
#undef allT

    // localize statics
    ui->note_title->setText(locale::get(28));
    ui->note_contents->setText(locale::get(29));
    ui->hide_note_btn->setText(locale::get(30));

    connect(ui->hide_note_btn, SIGNAL(clicked()), this, SLOT(hd_note()));
    show();
}

void teacherView::hideEvent(QHideEvent *event) {
    sw_note();
}

void teacherView::hd_note() {
    ui->note_container->hide();
}

void teacherView::sw_note() {
    ui->note_container->show();
}

teacherView::~teacherView() {
    delete ui;
}
