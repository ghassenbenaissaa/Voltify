#include "fonction_st.h"
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include<QString>
#include<QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
fonction_st::fonction_st()
{

}





QString fonction_st:: gettype_st(){return TYPE_ST;}
//int fonction_st::getprofit_st(){return PROFIT_ST;}
//int fonction_st::getnbr_charge_st(){return NBR_CHARGE_ST;}
QDate fonction_st::getddm_st(){return DDM_ST;}
//int fonction_st::getconsj_st(){return CONSJ_ST;}
//int fonction_st::getconsc_st(){return CONSC_ST;}
//QString fonction_st::getetat_st(){return ETAT_ST;}
int fonction_st::getvitesse_st(){return VITESSE_ST;}
QString fonction_st::getmode_st(){return MODE_ST;}
int fonction_st::getprix_kw_st(){return PRIX_KW_ST;}



void fonction_st::settype_st(QString type_st){this->TYPE_ST=type_st;}
//void fonction_st::setprofit_st(int profit_st){this->PROFIT_ST=profit_st;}
//void fonction_st::setnbr_charge_st(int nbr_charge_st){this->NBR_CHARGE_ST=nbr_charge_st;}
void fonction_st::setddm_st( QDate ddm_st){this->DDM_ST=ddm_st;}
//void fonction_st::setconsj_st(int consj_st){this->CONSJ_ST=consj_st;}
//void fonction_st::setconsc_st(int consc_st){this->CONSC_ST=consc_st;}
//void fonction_st::setetat_st(QString etat_st){this->ETAT_ST=etat_st;}
void fonction_st::setvitesse_st(int vitesse_st){this->VITESSE_ST=vitesse_st;}
void fonction_st::setmode_st(QString mode_st){this->MODE_ST=mode_st;}
void fonction_st::setprix_kw_st(int prix_kw_st){this->PRIX_KW_ST=prix_kw_st;}





