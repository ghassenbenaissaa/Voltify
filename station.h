#ifndef STATION_H
#define STATION_H
#include"fonction_st.h"
#include <QDialog>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include <QSqlTableModel>
#include <QStandardPaths>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include "arduino.h"
namespace Ui {
class station;

}

class station : public QDialog
{
    Q_OBJECT


public:
    explicit station(QWidget *parent = nullptr);
    ~station();
    station(QString type_st,QDate ddm_st,int vitesse_st,QString mode_st,float prix_kw_st,QString etat_st);
    bool Ajouter();
    bool Modifier(QString id);
    QSqlTableModel* tableView_station();
    QSqlTableModel* tableView_station(QString val);
    QSqlTableModel* tableView_station_2();
    //QSqlQueryModel* tableView_station(QString val);
    QSqlQueryModel* tableView_station2();
    //QSqlQueryModel* tableView_station_2();
  /*  ////////////////////getters/////////////////////////
    QString gettype_st(){return TYPE_ST;}
    int getprofit_st(){return PROFIT_ST;}
    int getnbr_charge_st(){return NBR_CHARGE_ST;}
    QDate getddm_st(){return DDM_ST;}
    int getconsj_st(){return CONSJ_ST;}
    int getconsc_st(){return CONSC_ST;}
    QString getetat_st(){return ETAT_ST;}
    int getvitesse_st(){return VITESSE_ST;}
    QString getmode_st(){return MODE_ST;}
    int getprix_kw_st(){return PRIX_KW_ST;}
    //////////////////////setters////////////////////////////
    void settype_st(QString type_st){this->TYPE_ST=type_st;}
    void setprofit_st(int profit_st){this->PROFIT_ST=profit_st;}
    void setnbr_charge_st(int nbr_charge_st){this->NBR_CHARGE_ST=nbr_charge_st;}
    void setddm_st( QDate ddm_st){this->DDM_ST=ddm_st;}
    void setconsj_st(int consj_st){this->CONSJ_ST=consj_st;}
    void setconsc_st(int consc_st){this->CONSC_ST=consc_st;}
    void setetat_st(QString etat_st){this->ETAT_ST=etat_st;}
    void setvitesse_st(int vitesse_st){this->VITESSE_ST=vitesse_st;}
    void setmode_st(QString mode_st){this->MODE_ST=mode_st;}
    void setprix_kw_st(int prix_kw_st){this->PRIX_KW_ST=prix_kw_st;}*/


private:
    Ui::station *ui;
    QString  TYPE_ST,ETAT_ST,MODE_ST,ID_ST;
    int PROFIT_ST,NBR_CHARGE_ST,CONSJ_ST,CONSC_ST,VITESSE_ST;
    QDate DDM_ST;
    float PRIX_KW_ST;
    QByteArray data; // variable contenant les données reçues

    arduino A; // objet temporaire




private slots:

    QSqlQueryModel* comboBox_id();
    QSqlQueryModel* comboBox_id_2();
    QPixmap * statistique();
    QPixmap * statistique2();
    void on_pushButton_valider_clicked();
    void on_tableView_station_activated(const QModelIndex &index);
    void on_comboBox_id_currentIndexChanged();
    void on_pushButton_valider_2_clicked();
    void on_pushButton_supp_clicked();
    void on_pushButton_suppt_clicked();
    void on_calendarWidget_clicked(const QDate &date);
    void on_calendarWidget_2_clicked(const QDate &date);
    void on_lineEdit_textChanged(const QString &arg1);
    void generatePDF(QString filename);
    void on_pushButton_pdf_clicked();
    //void checkAndUpdateCONC_ST();
    void proposition();
    void afficherImageSelonMode();
    void on_pushButton_Eco_clicked();
    void on_pushButton_Eco_des_clicked();
    void on_tableView_station_2_activated(const QModelIndex &index);
    void arduino();
    void aff7();
    void lcd();
    void capteur();
};
#endif // STATION_H
