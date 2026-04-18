#include "insertdata.h"
#include "ui_station.h"
#include "station.h"

insertData::insertData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insertData)
{
    ui->setupUi(this);
}

insertData::~insertData()
{
    delete ui;
}

void insertData::on_pushButton_clicked()
{
    QString name = ui->textEdit->toPlainText();
    QString pass = ui->textEdit_2->text();

    MainWindow m ;
    m.InsertData(name,pass);

}
