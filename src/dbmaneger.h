#ifndef DBMANEGER_H
#define DBMANEGER_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class Connection
{private:
    QSqlDatabase db;
public:
    Connection();
    bool createconnexion();
    void closeconnexion();
};


#endif // DBMANEGER_H
