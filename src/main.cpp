#include "profil.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnexion();
    profil w;

    if(test)
    {
    w.show();
    }
    return a.exec();
}
