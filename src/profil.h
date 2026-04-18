#ifndef PROFIL_H
#define PROFIL_H

#include <QMainWindow>
#include <employee.h>
#include <client.h>
#include <service.h>
#include <station.h>
#include <stock.h>
#include <reglage.h>

#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class profil; }
QT_END_NAMESPACE

class profil : public QMainWindow
{
    Q_OBJECT

public:
    profil(QWidget *parent = nullptr);
    ~profil();

private slots:
    void on_pushButton_profil_clicked();

    void on_pushButton_client_clicked();

    void on_pushButton_employee_clicked();

    void on_pushButton_station_clicked();

    void on_pushButton_service_clicked();

    void on_pushButton_stock_clicked();

    void on_pushButton_quitter_clicked();

    void on_pushButton_reglage_clicked();

private:
    Ui::profil *ui;
    client C;
    employee E;
    service S;
    station ST;
    stock SCK;
    reglage R;
};
#endif // PROFIL_H
