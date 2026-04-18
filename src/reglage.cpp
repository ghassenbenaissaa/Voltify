#include "reglage.h"
#include "ui_reglage.h"

reglage::reglage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reglage)
{
    ui->setupUi(this);
}

reglage::~reglage()
{
    delete ui;
}
