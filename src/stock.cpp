#include "stock.h"
#include "ui_stock.h"

stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
}

stock::~stock()
{
    delete ui;
}
