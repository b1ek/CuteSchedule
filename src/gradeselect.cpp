#include "gradeselect.h"
#include "./ui_gradeselect.h"

gradeSelect::gradeSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeSelect) {
    ui->setupUi(this);

    int col = 0;
    int row = 0;

    std::map<std::string, qbs::grade> gr = qbs::grade::allGrades;
    QGridLayout *lay = new QGridLayout();
    for (auto i = gr.begin(); i != gr.end(); ++i) {
        QPushButton *lbl = new QPushButton(i->first.c_str());
        if (col >= 4) {
            row++;
            col = 0;
        }
        lbl->setText(i->first.c_str());
        lay->addWidget(lbl, row, col);
        lbl->setStyleSheet("QPushButton {min-width: 128px;min-height: 64px;max-width: 128px;max-height: 64px;}");
        connect(lbl, &QPushButton::clicked, this, [=](){this->handle_b(dynamic_cast<QPushButton*>(sender())->text());});

        lbl->show();
        col++;
    }
    setLayout(lay);
}

void gradeSelect::handle_b(QString id) {
    emit send_selected(id);
}

void gradeSelect::setupUi() {
    ui->setupUi(this);
}

gradeSelect::~gradeSelect() {
    delete ui;
}
