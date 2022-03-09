#include "gradeselect.h"
#include "./ui_gradeselect.h"

gradeSelect::gradeSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeSelect) {

    int col = 0;
    int row = 0;

    std::map<std::string, qbs::grade> gr = qbs::grade::allGrades;
    QGridLayout *lay = new QGridLayout();
    for (auto i = gr.begin(); i != gr.end(); ++i) {
        QPushButton *lbl = new QPushButton(i->first.c_str());
        if (col >= 6) {
            col = 0;
            row++;
        }
        if (row <= 5) {
            lbl->setText(i->first.c_str());
            lay->addWidget(lbl, row, col);
            // "QPushButton {min-width: 128px;min-height: 64px;max-width: 128px;max-height: 64px;}"
            lbl->setStyleSheet("QPushButton {min    -width: 128px;min-height: 64px;max-width: 128px;max-height: 64px;}");
            connect(lbl, SIGNAL(clicked()), this, SLOT(handle_bclick()));

            lbl->show();
        }
    }
    setLayout(lay);
    ui->setupUi(this);
}

void handle_bclick() {
}

void gradeSelect::setupUi() {
    ui->setupUi(this);
}

gradeSelect::~gradeSelect() {
    delete ui;
}
