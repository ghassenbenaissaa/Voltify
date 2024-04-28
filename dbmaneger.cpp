#include <dbmaneger.h>

Connection::Connection(){}

bool Connection::createconnexion()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("esprit");//inserer mot de passe de cet utilisateur


    if(db.open())
        test=true;
    return test;
}

void Connection::closeconnexion()
{

    db.close();
}



bool DbManager::addUser(const QString& TYPE_ST ,const QDate& DDM_ST,const float& VITESSE_ST,const QString& MODE_ST,const float& PRIX_KW_ST)
{
    bool success = false;

        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO STATIONS (ID_ST, TYPE_ST, PROFIT_ST, NBR_CHARGE_ST, DDM_ST, CONJ_ST, CONSC_ST, ETAT_ST, VITESSE_ST, MODE_ST, PRIX_KW_ST) "
                          "VALUES (?, ?,?,?,?,?,?,?,?,?,?)");
        queryAdd.bindValue(2,TYPE_ST);
        queryAdd.bindValue(5,DDM_ST);
        queryAdd.bindValue(9,VITESSE_ST);
        queryAdd.bindValue(10,MODE_ST);
        queryAdd.bindValue(11,PRIX_KW_ST);

        if(queryAdd.exec())
        {

            qDebug() << "Success";
        }
        else
        {
            qDebug() <<"Error adding user:" << queryAdd.lastError();
        }



    return success;
}
