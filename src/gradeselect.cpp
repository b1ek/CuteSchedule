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
        QLabel *lbl = new QLabel(i->first.c_str());
        if (col >= 6) {
            col = 0;
            row++;
        }
        if (row <= 5) {
            lbl->setText(i->first.c_str());
            lay->addWidget(lbl, row, col);
            lbl->show();
        }
    }
    setLayout(lay);
    ui->setupUi(this);
}
void gradeSelect::setupUi() {
    ui->setupUi(this);
}

gradeSelect::~gradeSelect() {
    delete ui;
}
