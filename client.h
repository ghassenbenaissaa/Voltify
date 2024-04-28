#ifndef CLIENT_H
#define CLIENT_H
#include <station.h>
#include <QDialog>
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
namespace Ui {
class client;
}

class client : public QDialog
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
    client(int consj_st);
    bool Ajouter();
    bool Modifier(QString id, int consj_st);
    bool Verif(QString id, int CONSJ, int& reste, QString& eco);

private:
    Ui::client *ui;
    int CONSJ_ST;
     QString  ID_ST;

private slots:

    QSqlQueryModel* comboBox_id();
    void on_pushButton_clicked();
};

#endif // CLIENT_H
