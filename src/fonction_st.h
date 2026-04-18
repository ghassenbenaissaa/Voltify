#ifndef FONCTION_ST_H
#define FONCTION_ST_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>


class fonction_st
{
    QString  TYPE_ST/*,ETAT_ST,*/,MODE_ST;
    int /*PROFIT_ST,NBR_CHARGE_ST,CONSJ_ST,CONSC_ST,*/VITESSE_ST,PRIX_KW_ST;
    QDate DDM_ST;
public:
    fonction_st(QString,QDate,int,QString,int);
    fonction_st();


    QString gettype_st();
    int getprofit_st();
    int getnbr_charge_st();
    QDate getddm_st();
    int getconsj_st();
    int getconsc_st();
    QString getetat_st();
    int getvitesse_st();
    QString getmode_st();
    int getprix_kw_st();

    void settype_st(QString);
    void setprofit_st(int);
    void setnbr_charge_st(int);
    void setddm_st(QDate);
    void setconsj_st(int);
    void setconsc_st(int);
    void setetat_st(QString);
    void setvitesse_st(int);
    void setmode_st(QString);
    void setprix_kw_st(int);


    bool Ajouter();


};

#endif // FONCTION_ST_H
