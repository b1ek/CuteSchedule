#include "license_window.h"
#include "ui_license_window.h"

license_window::license_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::license_window)
{
    ui->setupUi(this);
}

license_window::~license_window()
{
    delete ui;
}
