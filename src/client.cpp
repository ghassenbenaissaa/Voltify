#include "client.h"
#include "station.h"
#include "ui_client.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QDate>
#include <QFloat16>
#include <QSqlTableModel>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QStandardPaths>
#include <QtCharts/QBarSet>
#include <QtCharts>
#include <QChartView>

client::client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    ui->comboBox->setModel(comboBox_id());

}

client::~client()
{
    delete ui;
}

QSqlQueryModel* client::comboBox_id()
{
    QSqlQueryModel* model3=new QSqlQueryModel();
    QSqlQuery query3("SELECT ID_ST FROM STATIONS");
    model3->setQuery(query3);
    return model3;
}

client::client(int consj_st)
{
    this->CONSJ_ST=consj_st;
}
bool client::Modifier(QString id, int consj_st)
{
    QSqlQuery query0;
    query0.prepare("SELECT * FROM stations WHERE ID_ST = :id");
    query0.bindValue(":id", id);
    if (!query0.exec()) {
        qDebug() << "Erreur lors de la sélection de la station : " << query0.lastError().text();
        return false;
    }
    if (query0.next()) {
        int aconsj = query0.value("CONSJ_ST").toInt();
        int consc_st = query0.value("CONSC_ST").toInt();
        float profit = query0.value("PROFIT_ST").toFloat();
        float prix = query0.value("PRIX_KW_ST").toFloat();
        int consm_st = query0.value("CONSM_ST").toInt();
        QString etat = query0.value("ETAT_ST").toString();
        QString eco = query0.value("MODE_ST").toString();
        int NBR = query0.value("NBR_CHARGE_ST").toInt();
        qDebug() << "CONSJ_ST avant modification :" << aconsj;
        int total = aconsj + consj_st;
        int total2 = consc_st + consj_st;
        float pro = total * prix;
        int pro2 = pro + profit;
        int consm = consm_st + consj_st;
        NBR = NBR + 1;
        if (eco == "Economique")
        {
        if (total >= 300)
        {
            etat = "En repos";
        }
        }
        QSqlQuery query;
        query.prepare("UPDATE STATIONS SET PROFIT_ST = :pro2, NBR_CHARGE_ST = :NBR ,CONSJ_ST = :total, ETAT_ST = :etat, CONSC_ST= :total2, CONSM_ST= :consm WHERE ID_ST = '"+id+"'");
        query.bindValue(":pro2",pro2);
        query.bindValue(":total",total);
        query.bindValue(":etat",etat);
        query.bindValue(":total2",total2);
        query.bindValue(":NBR",NBR);
        query.bindValue(":consm",consm);
        if (query.exec()) {
            qDebug() << "Modification effectuée avec succès.";
            return true;
        } else {
            qDebug() << "Erreur lors de la modification : " << query.lastError().text();
            return false;
        }
    } else {
        qDebug() << "La station avec l'ID " << id << " n'existe pas.";
        return false;
    }
}

bool client::Verif(QString id, int CONSJ, int& reste, QString& eco)
{
    // Vérifier si la station est en mode économique
    QSqlQuery query;
    query.prepare("SELECT * FROM stations WHERE ID_ST = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la sélection de la station : " << query.lastError().text();
        return false;
    }
    if (query.next()) {
         eco = query.value("MODE_ST").toString();
        reste = 0;
        if (eco == "Economique") {
            // Vérifier si la consommation après modification ne dépasse pas 300
            int aconsj = query.value("CONSJ_ST").toInt();
            int total = aconsj + CONSJ;
            reste = 300 - total;
            if (total > 300) {
                int reste1 = 300 - aconsj;
                QMessageBox::warning(nullptr, QObject::tr("Attention"),
                QObject::tr("Impossible d'ajouter la consommation, la station est en mode économique et la consommation journalière totale dépasse 300 kWh.\nIl vous reste que %1 kWh pour aujourd'hui.").arg(reste1), QMessageBox::Ok);
                return false;
            }
        }
    }
    return true;
}

void client::on_pushButton_clicked()
{
    QString ID_ST = ui->comboBox->currentText();
    int CONSJ = ui->spinBox->value();
    station S;
    int reste;
    QString eco;
    bool test2 = Verif(ID_ST,CONSJ,reste,eco);
    if (test2) {
        client C(CONSJ);
        bool test=C.Modifier(ID_ST,CONSJ);
        if(test)
       {
             if (eco == "Economique"){
           QMessageBox::information(nullptr,QObject::tr("Base de données"),
           QObject::tr("Modification effectuée.\nIl vous reste que %1 kWh pour aujourd'hui.").arg(reste),QMessageBox::Yes);
             }else {
             QMessageBox::information(nullptr,QObject::tr("Base de données"),
             QObject::tr("Modification effectuée."),QMessageBox::Yes);}
       }
        else
           QMessageBox::critical(nullptr,QObject::tr("Base de données"),
           QObject::tr("Modification non effectuée\n"),QMessageBox::Yes);
            }
}

