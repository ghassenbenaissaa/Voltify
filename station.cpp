#include "station.h"
#include "ui_station.h"
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
#include <QSqlRecord>






station::station(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::station)
{
    ui->setupUi(this);
    //affichage tableau1
    //***********arduino******************************
         int ret=A.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
    // Appel de la fonction dans votre code
    QSqlTableModel* model1 = tableView_station();
    ui->tableView_station->setModel(model1);
    ui->tableView_station->resizeColumnsToContents();
    ui->tableView_station->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_station->setColumnHidden(2, true);
    ui->tableView_station->setColumnHidden(3, true);
    ui->tableView_station->setColumnHidden(5, true);
    ui->tableView_station->setColumnHidden(6, true);
    ui->tableView_station->setColumnHidden(10, true);
    ui->tableView_station->setColumnHidden(11, true);
    ui->tableView_station->setColumnHidden(12, true);
    //affichage tabelau2
    ui->tableView_station_2->setModel(tableView_station_2());
    ui->tableView_station2->setModel(tableView_station2());
    ui->tableView_station_2->resizeColumnsToContents();
    ui->tableView_station_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_station_2->setColumnHidden(4, true);
    ui->tableView_station_2->setColumnHidden(7, true);
    ui->tableView_station_2->setColumnHidden(9, true);
    ui->tableView_station_2->setColumnHidden(11, true);
    ui->tableView_station_2->setColumnHidden(12, true);
    //affichage id
    ui->comboBox_id->setModel(comboBox_id());
    ui->comboBox_id_2->setModel(comboBox_id_2());
    //date
    ui->dateEdit_man->setDate(QDate::currentDate());
    //************statestique**********************
    QPixmap* chartPixmapPtr = statistique(); // Appel à votre fonction pour récupérer le QPixmap*
        if (chartPixmapPtr) {
            ui->label_7->setPixmap(*chartPixmapPtr); // Mise à jour de l'image de la QLabel
            delete chartPixmapPtr; // Libération de la mémoire allouée dynamiquement pour le QPixmap
        }
    QPixmap* chartPixmapPtr2 = statistique2(); // Appel à votre fonction pour récupérer le QPixmap*
         if (chartPixmapPtr2) {
             ui->statestique->setPixmap(*chartPixmapPtr2); // Mise à jour de l'image de la QLabel
             delete chartPixmapPtr2; // Libération de la mémoire allouée dynamiquement pour le QPixmap
        }
    //************appelinit**************************
        /* QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(checkAndUpdateCONC_ST()));
         timer->start(3600000); // Appeler la fonction toutes les heures*/
    //**********proposition**************************
         proposition();
         afficherImageSelonMode();

         QTimer* timer = new QTimer(this);
         connect(timer, &QTimer::timeout, this, &station::capteur);
         timer->start(2000); // Appeler toutes les secondes (3000 ms)

         QTimer* timer1 = new QTimer(this);
         connect(timer1, &QTimer::timeout, this, &station::lcd);
         timer1->start(3000); // Appeler toutes les secondes (3000 ms)

        /* QTimer* timer3 = new QTimer(this);
       connect(timer3, &QTimer::timeout, this, &station::arduino);
         timer3->start(1000); // Appeler toutes les secondes (3000 ms)
        lcd();
         QTimer* timer2 = new QTimer(this);
         connect(timer2, &QTimer::timeout, this, &station::aff7);
         timer2->start(3000); // Appeler toutes les secondes (3000 ms)*/


}

station::~station()
{
    delete ui;
}


QSqlTableModel* station::tableView_station()
{
    QSqlTableModel* model1 = new QSqlTableModel(this);
    model1->setTable("STATIONS");
    model1->setEditStrategy(QSqlTableModel::OnFieldChange);

   // Spécifier les colonnes à afficher et leurs noms d'en-tête
    model1->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, tr("Type"));
    model1->setHeaderData(4, Qt::Horizontal, tr("Date de Maintenance"));
    model1->setHeaderData(7, Qt::Horizontal, tr("Etat"));
    model1->setHeaderData(8, Qt::Horizontal, tr("Vitesse"));
    model1->setHeaderData(9, Qt::Horizontal, tr("Mode"));

    // Masquer les colonnes non souhaitées
    ui->tableView_station->setColumnHidden(2, true);
    ui->tableView_station->setColumnHidden(3, true);
    ui->tableView_station->setColumnHidden(5, true);
    ui->tableView_station->setColumnHidden(6, true);
    ui->tableView_station->setColumnHidden(10, true);
    ui->tableView_station->setColumnHidden(11, true);
    ui->tableView_station->setColumnHidden(12, true);

    // Activer le tri par défaut sur la colonne ID_ST
    model1->setSort(0, Qt::AscendingOrder);

    // Sélectionner les données de la table
    model1->select();

    // Activer le tri sur le TableView
    ui->tableView_station->setSortingEnabled(true);

    return model1;
}


QSqlTableModel* station::tableView_station_2()
{
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable("STATIONS");

    // Spécifier les colonnes à afficher et leurs noms d'en-tête
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, tr("Profit"));
    model->setHeaderData(3, Qt::Horizontal, tr("Nbr de Charge"));
    model->setHeaderData(5, Qt::Horizontal, tr("Consommation Jour"));
    model->setHeaderData(6, Qt::Horizontal, tr("Consommation Courante"));
    model->setHeaderData(8, Qt::Horizontal, tr("Vitesse"));
    model->setHeaderData(10, Qt::Horizontal, tr("Prix_KW"));

    // Masquer les colonnes non souhaitées
    ui->tableView_station_2->setColumnHidden(4, true);
    ui->tableView_station_2->setColumnHidden(7, true);
    ui->tableView_station_2->setColumnHidden(9, true);
    ui->tableView_station_2->setColumnHidden(11, true);
    ui->tableView_station_2->setColumnHidden(12, true);

    // Activer le tri par défaut sur la colonne ID_ST
    model->setSort(0, Qt::AscendingOrder);

    // Sélectionner les données de la table
    model->select();

    // Activer le tri sur le TableView
    ui->tableView_station_2->setSortingEnabled(true);

    return model;
}

QSqlQueryModel* station::comboBox_id()
{
    QSqlQueryModel* model3=new QSqlQueryModel();
    QSqlQuery query3("SELECT ID_ST FROM STATIONS");
    model3->setQuery(query3);
    return model3;
}
QSqlQueryModel* station::comboBox_id_2()
{
    QSqlQueryModel* model4=new QSqlQueryModel();
    QSqlQuery query4("SELECT ID_ST FROM STATIONS");
    model4->setQuery(query4);
    return model4;
}


station::station(QString type_st,QDate ddm_st,int vitesse_st,QString mode_st,float prix_kw_st,QString etat_st)
{
    this->TYPE_ST=type_st;
    this->DDM_ST=ddm_st;
    this->VITESSE_ST=vitesse_st;
    this->MODE_ST=mode_st;
    this->PRIX_KW_ST=prix_kw_st;
    this->ETAT_ST=etat_st;
}



bool station::Ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO STATIONS (TYPE_ST,DDM_ST,VITESSE_ST,MODE_ST,PRIX_KW_ST)"
                  "VALUES (:type,:ddm,:vitesse,:mode,:prix_kw)");

    query.bindValue(":type",TYPE_ST);
    query.bindValue(":ddm",DDM_ST);
    query.bindValue(":vitesse",VITESSE_ST);
    query.bindValue(":mode", MODE_ST);
    query.bindValue(":prix_kw",static_cast<double>(PRIX_KW_ST));
    return query.exec();
}
bool station::Modifier(QString id)
{
    QSqlQuery query;
    qDebug() << "arduino is available but not connected to :" <<ETAT_ST;
    query.prepare("UPDATE STATIONS SET TYPE_ST = :type, DDM_ST = :ddm, ETAT_ST = :etat, VITESSE_ST = :vitesse, MODE_ST = :mode, PRIX_KW_ST = :prix_kw WHERE ID_ST = '"+id+"'");
    query.bindValue(":id",ID_ST);
    query.bindValue(":type",TYPE_ST);
    query.bindValue(":ddm",DDM_ST);
    query.bindValue(":etat",ETAT_ST);
    query.bindValue(":vitesse",VITESSE_ST);
    query.bindValue(":mode", MODE_ST);
    query.bindValue(":prix_kw",static_cast<double>(PRIX_KW_ST));
    return query.exec();
}




void station::on_pushButton_valider_clicked()
{
    QString TYPE_ST = ui->comboBox_type->currentText();
    QDate DDM_ST = ui->dateEdit_man->date();
    int VITESSE_ST = ui->comboBox_vitesse->currentText().toInt();
    QString MODE_ST = ui->comboBox_mode->currentText();
    qfloat16 PRIX_KW_ST= ui->doubleSpinBox_prix->value();
    // Vérifier si la date est valide
    QDate currentDate = QDate::currentDate();//la date actuelle
            if (DDM_ST <= currentDate) {

                QMessageBox::warning(this, "Erreur de saisie", "La date doit être supérieure à celle d'aujourd'huit");
                qDebug() <<"Error date!" ;
                return; // arrêter l'exécution de la fonction
            }
            if(ui->doubleSpinBox_prix->value() <= 2.0){
                   QMessageBox::warning(this,tr("Erreur de saisie"),tr("La valeur doit être supérieure à 2."));
                   qDebug() <<"Error date!" ;
                   return; // arrêter l'exécution de la fonction
               }
    station S(TYPE_ST,DDM_ST,VITESSE_ST,MODE_ST,PRIX_KW_ST,"");
    bool test=S.Ajouter();
    if(test)
   {
        QMessageBox::information(nullptr,QObject::tr("Base de données"),
        QObject::tr("Ajout effectuée\n"),QMessageBox::Yes);
        ui->tableView_station->setModel(tableView_station());
        ui->tableView_station->resizeColumnsToContents();
        ui->tableView_station_2->setModel(tableView_station_2());
        ui->tableView_station_2->resizeColumnsToContents();
        ui->comboBox_id->setModel(comboBox_id());
        ui->comboBox_id_2->setModel(comboBox_id_2());
        QPixmap* chartPixmapPtr = statistique(); // Appel à votre fonction pour récupérer le QPixmap*
            if (chartPixmapPtr) {
                ui->label_7->setPixmap(*chartPixmapPtr); // Mise à jour de l'image de la QLabel
                delete chartPixmapPtr; // Libération de la mémoire allouée dynamiquement pour le QPixmap
            }
        QPixmap* chartPixmapPtr2 = statistique2(); // Appel à votre fonction pour récupérer le QPixmap*
             if (chartPixmapPtr2) {
                 ui->statestique->setPixmap(*chartPixmapPtr2); // Mise à jour de l'image de la QLabel
                 delete chartPixmapPtr2; // Libération de la mémoire allouée dynamiquement pour le QPixmap
            }
   }
    else
       QMessageBox::critical(nullptr,QObject::tr("Base de données"),
       QObject::tr("Ajout non effectuée\n"),QMessageBox::Yes);
}
void station::on_pushButton_valider_2_clicked()
{
    QString ID_ST = ui->comboBox_id->currentText();
    QString TYPE_ST = ui->comboBox_type_2->currentText();
    QDate DDM_ST = ui->dateEdit_man_2->date();
    QString ETAT_ST = ui->comboBox_etat_2->currentText();
    int VITESSE_ST = ui->comboBox_vitesse_2->currentText().toInt();
    QString MODE_ST = ui->comboBox_mode_2->currentText();
    qfloat16 PRIX_KW_ST= ui->doubleSpinBox_prix_2->value();
    // Vérifier si la date est valide
    QDate currentDate = QDate::currentDate();//la date actuelle
            if (DDM_ST <= currentDate) {

                QMessageBox::warning(this, "Erreur de saisie", "La date doit être supérieure à celle d'aujourd'huit");
                qDebug() <<"Error date!" ;
                return; // arrêter l'exécution de la fonction
            }
            if(ui->doubleSpinBox_prix_2->value() <= 2.0){
                   QMessageBox::warning(this,tr("Erreur de saisie"),tr("La valeur doit être supérieure à 2."));
                   qDebug() <<"Error date!" ;
                   return; // arrêter l'exécution de la fonction
               }
    station S(TYPE_ST,DDM_ST,VITESSE_ST,MODE_ST,PRIX_KW_ST,ETAT_ST);
    bool test=S.Modifier(ID_ST);
    if(test)
   {
       QMessageBox::information(nullptr,QObject::tr("Base de données"),
       QObject::tr("Modification effectuée\n"),QMessageBox::Yes);
        ui->tableView_station->setModel(tableView_station());
        ui->tableView_station->resizeColumnsToContents();
        ui->tableView_station_2->setModel(tableView_station_2());
        ui->tableView_station_2->resizeColumnsToContents();
        ui->comboBox_id->setModel(comboBox_id());
        ui->comboBox_id_2->setModel(comboBox_id_2());
        QPixmap* chartPixmapPtr = statistique(); // Appel à votre fonction pour récupérer le QPixmap*
            if (chartPixmapPtr) {
                ui->label_7->setPixmap(*chartPixmapPtr); // Mise à jour de l'image de la QLabel
                delete chartPixmapPtr; // Libération de la mémoire allouée dynamiquement pour le QPixmap
            }
        QPixmap* chartPixmapPtr2 = statistique2(); // Appel à votre fonction pour récupérer le QPixmap*
             if (chartPixmapPtr2) {
                 ui->statestique->setPixmap(*chartPixmapPtr2); // Mise à jour de l'image de la QLabel
                 delete chartPixmapPtr2; // Libération de la mémoire allouée dynamiquement pour le QPixmap
            }
             proposition();
             afficherImageSelonMode();

   }
    else
       QMessageBox::critical(nullptr,QObject::tr("Base de données"),
       QObject::tr("Modification non effectuée\n"),QMessageBox::Yes);
}




void station::on_tableView_station_activated(const QModelIndex &index)
{
    QString val=ui->tableView_station->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from STATIONS where ID_ST='"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->comboBox_id->setCurrentText(query.value(0).toString());
            ui->comboBox_type_2->setCurrentText(query.value(1).toString());
            ui->dateEdit_man_2->setDate(query.value(4).toDate());
            ui->comboBox_etat_2->setCurrentText(query.value(7).toString());
            ui->comboBox_mode_2->setCurrentText(query.value(9).toString());
            ui->comboBox_vitesse_2->setCurrentText(query.value(8).toString());
            QString str = query.value(10).toString();
            double prix = str.toDouble();
            ui->doubleSpinBox_prix_2->setValue(prix);
           ui->tabWidget->setCurrentIndex(3);
        }
    }
    else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
    }
}

void station::on_tableView_station_2_activated(const QModelIndex &index)
{
    QString val=ui->tableView_station_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from STATIONS where ID_ST='"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->comboBox_id->setCurrentText(query.value(0).toString());
            ui->comboBox_type_2->setCurrentText(query.value(1).toString());
            ui->dateEdit_man_2->setDate(query.value(4).toDate());
            ui->comboBox_etat_2->setCurrentText(query.value(7).toString());
            ui->comboBox_mode_2->setCurrentText(query.value(9).toString());
            ui->comboBox_vitesse_2->setCurrentText(query.value(8).toString());
            QString str = query.value(10).toString();
            double prix = str.toDouble();
            ui->doubleSpinBox_prix_2->setValue(prix);
           ui->tabWidget->setCurrentIndex(3);
        }
    }
    else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
    }
}

void station::on_comboBox_id_currentIndexChanged()
{
    QString ID_ST=ui->comboBox_id->currentText();
    QSqlQuery query;
    query.prepare("select * from STATIONS WHERE ID_ST='"+ID_ST+"'");
    if(query.exec())
    {
        while(query.next())
        {
            ui->comboBox_type_2->setCurrentText(query.value(1).toString());
            ui->dateEdit_man_2->setDate(query.value(4).toDate());
            ui->comboBox_etat_2->setCurrentText(query.value(7).toString());
            ui->comboBox_mode_2->setCurrentText(query.value(9).toString());
            ui->comboBox_vitesse_2->setCurrentText(query.value(8).toString());
            QString str = query.value(10).toString();
            double prix = str.toDouble();
            ui->doubleSpinBox_prix_2->setValue(prix);
        }
    }
}




//**********************supprimer****************
void station::on_pushButton_supp_clicked()
{
    QString id;
    id=ui->comboBox_id_2->currentText();
    QSqlQuery query;
    query.prepare("DELETE FROM STATIONS WHERE ID_ST='"+id+"'");

    QMessageBox::StandardButton reply = QMessageBox::warning(this,"Base de données", "Etes vous sur de le supprimer?", QMessageBox::Yes | QMessageBox::No);
           if(reply == QMessageBox::Yes) {
               if(query.exec()){
                   QMessageBox::information(this,tr("Base de données"),tr("Suppression effectuée"));
                   ui->tableView_station->setModel(tableView_station());
                   ui->tableView_station->resizeColumnsToContents();
                   ui->tableView_station_2->setModel(tableView_station_2());
                   ui->tableView_station_2->resizeColumnsToContents();
                   ui->comboBox_id->setModel(comboBox_id());
                   ui->comboBox_id_2->setModel(comboBox_id_2());
                   QPixmap* chartPixmapPtr = statistique(); // Appel à votre fonction pour récupérer le QPixmap*
                       if (chartPixmapPtr) {
                           ui->label_7->setPixmap(*chartPixmapPtr); // Mise à jour de l'image de la QLabel
                           delete chartPixmapPtr; // Libération de la mémoire allouée dynamiquement pour le QPixmap
                       }
                   QPixmap* chartPixmapPtr2 = statistique2(); // Appel à votre fonction pour récupérer le QPixmap*
                        if (chartPixmapPtr2) {
                            ui->statestique->setPixmap(*chartPixmapPtr2); // Mise à jour de l'image de la QLabel
                            delete chartPixmapPtr2; // Libération de la mémoire allouée dynamiquement pour le QPixmap
                       }
                        proposition();
                        afficherImageSelonMode();

           } else {QMessageBox::information(this,tr("Base de données"),tr("Suppression non effectuée"));
          }
}else QMessageBox::critical(this,tr("Base de données"),tr("Suppression non effectuée"));
}
void station::on_pushButton_suppt_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM STATIONS ");
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Base de données", "Etes vous sur de supprimer toute les données?", QMessageBox::Yes | QMessageBox::No);
               if(reply == QMessageBox::Yes) {
                   if(query.exec()){
                       QMessageBox::information(this,tr("Base de données"),tr("Suppression effectuée"));
                       ui->tableView_station->setModel(tableView_station());
                       ui->tableView_station->resizeColumnsToContents();
                       ui->tableView_station_2->setModel(tableView_station_2());
                       ui->tableView_station_2->resizeColumnsToContents();
                       ui->comboBox_id->setModel(comboBox_id());
                       ui->comboBox_id_2->setModel(comboBox_id_2());
                       QPixmap* chartPixmapPtr = statistique(); // Appel à votre fonction pour récupérer le QPixmap*
                           if (chartPixmapPtr) {
                               ui->label_7->setPixmap(*chartPixmapPtr); // Mise à jour de l'image de la QLabel
                               delete chartPixmapPtr; // Libération de la mémoire allouée dynamiquement pour le QPixmap
                           }
                       QPixmap* chartPixmapPtr2 = statistique2(); // Appel à votre fonction pour récupérer le QPixmap*
                            if (chartPixmapPtr2) {
                                ui->statestique->setPixmap(*chartPixmapPtr2); // Mise à jour de l'image de la QLabel
                                delete chartPixmapPtr2; // Libération de la mémoire allouée dynamiquement pour le QPixmap
                           }
                            proposition();
                            afficherImageSelonMode();

               } else {QMessageBox::critical(this,tr("Base de données"),tr("Suppression non effectuée"));
              }
    }else QMessageBox::information(this,tr("Base de données"),tr("Suppression non effectuée"));
}


//********************SELECTIONNER_DEPUIT_CALANDRIER****************
void station::on_calendarWidget_clicked(const QDate &date)
{
    ui->dateEdit_man->setDate(date);
}

void station::on_calendarWidget_2_clicked(const QDate &date)
{
    ui->dateEdit_man_2->setDate(date);
}


QSqlTableModel* station::tableView_station(QString val)
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("STATIONS");
    model->setFilter(QString("ID_ST LIKE '%%1%' OR TYPE_ST LIKE '%%1%' OR DDM_ST LIKE '%%1%' OR ETAT_ST LIKE '%%1%' OR VITESSE_ST LIKE '%%1%' OR MODE_ST LIKE '%%1%'").arg(val));
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, tr("Date de Maintenance"));
    model->setHeaderData(7, Qt::Horizontal, tr("Etat"));
    model->setHeaderData(8, Qt::Horizontal, tr("Vitesse"));
    model->setHeaderData(9, Qt::Horizontal, tr("Mode"));

    // Masquer les colonnes non souhaitées
    ui->tableView_station->setColumnHidden(2, true);
    ui->tableView_station->setColumnHidden(3, true);
    ui->tableView_station->setColumnHidden(5, true);
    ui->tableView_station->setColumnHidden(6, true);
    ui->tableView_station->setColumnHidden(10, true);
    ui->tableView_station->setColumnHidden(11, true);
    ui->tableView_station->setColumnHidden(12, true);
    model->select();
    return model;
}
void station::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
    ui->tableView_station->setModel(tableView_station());
    } else {
    ui->tableView_station->setModel(tableView_station(arg1));
    }

}


//*************GENERER_PDF********************

QSqlQueryModel* station::tableView_station2()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query1("SELECT ID_ST, TYPE_ST, PROFIT_ST, NBR_CHARGE_ST, SUBSTR(DDM_ST, 1, 10) AS DATE_DD_ST, CONSC_ST, ETAT_ST, VITESSE_ST, MODE_ST, PRIX_KW_ST FROM STATIONS ORDER BY ID_ST ASC;");
    model->setQuery(query1);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, tr("PROFIT"));
    model->setHeaderData(3, Qt::Horizontal, tr("NBR_CHARGE"));
    model->setHeaderData(4, Qt::Horizontal, tr("DDM"));
    model->setHeaderData(5, Qt::Horizontal, tr("CONSC"));
    model->setHeaderData(6, Qt::Horizontal, tr("ETAT"));
    model->setHeaderData(7, Qt::Horizontal, tr("VITESSE"));
    model->setHeaderData(8, Qt::Horizontal, tr("MODE"));
    model->setHeaderData(9, Qt::Horizontal, tr("PRIX_KW"));

    for(int i=0;i<model->rowCount();i++){
        QString datetimeString = model->record(i).value("DDM_ST").toString();
        QDateTime datetime = QDateTime::fromString(datetimeString, "yyyy-MM-ddThh:mm:ss");
        QString dateString = datetime.toString("yyyy-MM-dd");
        model->setData(model->index(i, 4), dateString);
    }

    return model;
}

void station::generatePDF(QString filename)
{
    // Récupérer le chemin du répertoire du bureau de l'utilisateur
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Concaténer le chemin du bureau avec le nom de fichier fourni
    QString fullPath = desktopPath + "/" + filename;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fullPath);

    QPainter painter;
    if(!painter.begin(&printer))
    {
        qDebug() <<"ERREUR";
        return;
    }

    // Ajouter le logo
    painter.drawPixmap(30,25,QPixmap(":/new/prefix1/ICON/loo.png"));
    painter.drawPixmap(-200,-200,QPixmap(":/new/prefix1/ICON/llll.png"));

    // Ajouter le titre
        QString title = "LES STATIONS";
        QFont titleFont("Arial", 18, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(370,100, title);
        QFont defaultFont;
        painter.setFont(defaultFont);
    // Récupérer les noms des colonnes
    QHeaderView *header = ui->tableView_station2->horizontalHeader();
    QStringList headers;
    int x = 250;
    int y = 20;
    int w = 0;
    int z = 0;
    int a = 30;

    for(int i=0; i<header->count(); i++)
    {
        QString headerText = header->model()->headerData(i, Qt::Horizontal).toString();
        headers << headerText;
        painter.drawText(0+ a, x,headerText);
        a += 95;
    }

    // Afficher les noms de colonnes

    QModelIndex index;
    for(int row=0; row<ui->tableView_station2->model()->rowCount(); row++)
    {
        y = 280; // incrémenter la position verticale pour afficher la prochaine ligne de données
        x = 30;
        w = y+z;
        for(int col=0; col<ui->tableView_station2->model()->columnCount(); col++)
        {
            index = ui->tableView_station2->model()->index(row, col);
            QString data = ui->tableView_station2->model()->data(index).toString();
            painter.drawText(x, w, data);
            x += 95;
        }
        z += 30;
    }
    painter.drawText(310,1350, "Toutes les données ont été générées par l'application Voltify.");
    // Fin du dessin
    painter.end();

    qDebug() << "Fichier PDF enregistré avec succès:" << fullPath;
    QMessageBox::information(this,tr("Voltify"),tr("Votre fichier pdf a ete généré"));
}

void station::on_pushButton_pdf_clicked()
{
    QString filename = "stations.pdf";
    generatePDF(filename);
}
//*********************statistique****************

QPixmap * station::statistique()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from STATIONS where TYPE_ST='Autre voiture' ");
     int number1=model->rowCount();
     model->setQuery("select * from STATIONS where TYPE_ST='Tesla' ");
     int number2=model->rowCount();
     model->setQuery("select * from STATIONS where TYPE_ST='Porsche' ");
     int number3=model->rowCount();
     model->setQuery("select * from STATIONS where TYPE_ST='Toyota' ");
     int number4=model->rowCount();
       int total=0;
      total=number1+number2+number3+number4;
     if(total!=0)
    {
     QString a = QString("Autre voiture"+QString::number((number1*100)/total,'f',2)+"%" );
     QString b = QString("Tesla"+QString::number((number2*100)/total,'f',2)+"%" );
     QString c = QString("Porsche"+QString::number((number3*100)/total,'f',2)+"%" );
     QString d = QString("Toyota" +QString::number((number4*100)/total,'f',2)+"%" );


    QPieSeries *series = new QPieSeries();
     series->append(a,number1);
     series->append(b,number2);
     series->append(c,number3);
     series->append(d,number4);
     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
              slice1->setPen(QPen());
     }
     if(number3!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice2 = series->slices().at(2);
              //slice1->setExploded();
              slice2->setLabelVisible();

              slice2->setPen(QPen());
     }
     if(number4!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice3 = series->slices().at(3);
              //slice1->setExploded();
              slice3->setLabelVisible();
              slice3->setPen(QPen());
     }
             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("Nombre de stations par type");
             chart->legend()->hide();

             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(500,300);

           // chartView->show();
             // Créer un QPixmap à partir de la vue de graphique
             QPixmap* chartPixmap = new QPixmap(chartView->grab());
               return chartPixmap;
     }
     else {
         QChart *chart = new QChart();
        chart->setBackgroundBrush(QBrush(QColor(238, 238, 238)));
         chart->setTheme(QChart::ChartThemeLight);

         // Create chart view
         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->resize(700, 500);

         // Create pixmap from chart view
         QPixmap* chartPixmap = new QPixmap(chartView->grab());
         return chartPixmap;
     }


}
QPixmap *station::statistique2()
{
    // Créer un modèle de requête SQL
    QSqlQueryModel *model = new QSqlQueryModel();

    // Exécuter une requête SQL pour obtenir la somme de la consommation totale pour chaque station
    model->setQuery("SELECT ID_ST, SUM(CONSC_ST) as total_consommation FROM STATIONS GROUP BY ID_ST ORDER BY total_consommation DESC");

    // Créer un graphique à barres
    QChart *chart = new QChart();

    // Ajouter des séries de données pour chaque station
    QBarSeries *series = new QBarSeries();

    // Parcourir les résultats de la requête et ajouter chaque ID_ST et total de consommation comme une barre dans la série
    for (int i = 0; i < model->rowCount(); i++) {
        QString id_st = model->index(i, 0).data().toString();
        int total_consommation = model->index(i, 1).data().toInt();
        QBarSet *set = new QBarSet(id_st);
        *set << total_consommation;
        series->append(set);
    }

    // Ajouter les séries au graphique
    chart->addSeries(series);

    // Définir l'axe des x pour afficher les ID_ST des stations
    QStringList categories;
    for (int i = 0; i < model->rowCount(); i++) {
        categories << model->index(i, 0).data().toString();
    }
    chart->createDefaultAxes();

    // Définir l'axe des y pour afficher les valeurs de CONSC_ST
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Consommation totale");
    chart->setAxisY(axisY, series);

    // Définir les titres et les couleurs
    chart->setTitle("Consommation totale par station");
    chart->setTheme(QChart::ChartThemeLight);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Créer la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 300);

    // Créer un QPixmap à partir de la vue du graphique
    QPixmap *chartPixmap = new QPixmap(chartView->grab());
    return chartPixmap;
}

//**********Proposition*********************
/*void station::checkAndUpdateCONC_ST()
{
    // Récupérer la date actuelle
    QDate currentDate = QDate::currentDate();

    // Vérifier si c'est le premier jour du mois
    if (currentDate.day() == 1) {
        // Initialiser l'attribut CONC_ST
       int CONSM_ST = 0;
    //qDebug() << "Execution de checkkk";
        // Enregistrer les modifications dans la base de données
        QSqlQuery query;
        query.prepare("UPDATE STATIONS SET CONSM_ST = ?");
        query.addBindValue(CONSM_ST);
        query.exec();
        ui->tableView_station->setModel(tableView_station());
        ui->tableView_station->resizeColumnsToContents();
        ui->tableView_station_2->setModel(tableView_station_2());
        ui->tableView_station_2->resizeColumnsToContents();
        ui->comboBox_id->setModel(comboBox_id());
        ui->comboBox_id_2->setModel(comboBox_id_2());
    }
}*/
void station::proposition()
{
    // Récupérer la date actuelle
    QDate currentDate = QDate::currentDate();

    // Vérifier si c'est le jour du mois souhaité
    // tbadel date 28 akher chehar yafficher les proposition
    if (currentDate.day() > 5) {

        QSqlQuery query;
        query.prepare("SELECT ID_ST, CONSM_ST, WARNING FROM STATIONS WHERE (CONSM_ST < 300 OR CONSM_ST > 5000) AND (ETAT_ST != 'En panne' AND ETAT_ST != 'En repos')");

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
            return;
        }
        QString message = ""; // Initialiser la chaîne de messages
        while (query.next()) {
            int id_st = query.value(0).toInt();
            int consm_st = query.value(1).toInt();
            int warning = query.value(2).toInt();

            if (consm_st < 300) {
                if (warning > 5){
                    int war = warning + 1;
                    QSqlQuery query0;
                    query0.prepare("UPDATE STATIONS SET WARNING = :pro2 WHERE ID_ST = :id_st");
                    query0.bindValue(":pro2", war);
                    query0.bindValue(":id_st", id_st);
                    query0.exec();
                   // qDebug() << "Salut pour la station" << id_st;
                    message += "-URGENT-Mettre la station " + QString::number(id_st) + " en pause pour économiser de l'énergie.<br><br>";
                }else {
                     int war = warning + 1;
                    QSqlQuery query0;
                    query0.prepare("UPDATE STATIONS SET WARNING = :pro2 WHERE ID_ST = :id_st");
                    query0.bindValue(":pro2", war);
                    query0.bindValue(":id_st", id_st);
                    query0.exec();
                    //qDebug() << "Salut pour la station" << id_st;
                    message += "-Mettre la station " + QString::number(id_st) + " en pause pour économiser de l'énergie.<br><br>";
                }
            } else if (consm_st > 5000) {
                if (warning > 2){
                     int war = warning + 1;
                    QSqlQuery query0;
                    query0.prepare("UPDATE STATIONS SET WARNING = :pro2 WHERE ID_ST = :id_st");
                    query0.bindValue(":pro2", war);
                    query0.bindValue(":id_st", id_st);
                    query0.exec();
                    //qDebug() << "Bonne nuit pour la station" << id_st;
                    message += "-URGENT-Mettre la station " + QString::number(id_st) + " en pause pendant 1 jour pour garder la bonne fonctionnaliter de station.<br><br>";
                }else {
                     int war = warning + 1;
                    QSqlQuery query0;
                    query0.prepare("UPDATE STATIONS SET WARNING = :pro2 WHERE ID_ST = :id_st");
                    query0.bindValue(":pro2", war);
                    query0.bindValue(":id_st", id_st);
                    query0.exec();
                    //qDebug() << "Bonne nuit pour la station" << id_st;
                    message += "-Mettre la station " + QString::number(id_st) + " en pause pour 1 jour pour garder la bonne fonctionnaliter de station.<br><br>";
                }
            }
        }
        // Afficher les messages
        ui->textBrowser->setText(message);
    }
}
//******************Mode_Economique*********************
void station::on_pushButton_Eco_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this,"Base de données", "Etes vous sur d'activer le mode economique?\n\n\nIMPORTANT\nMode Economique: Dès l'activation, il va changer le mode de toutes les stations en économique, ce qui va obliger la station à générer seulement 300 kWh par jour.", QMessageBox::Yes | QMessageBox::No);
           if(reply == QMessageBox::Yes) {
    QSqlQuery query;
       bool success = query.exec("UPDATE STATIONS SET MODE_ST='Economique'");
       if (success) {
           // La mise à jour a réussi
           // Actualiser le modèle de la table pour afficher les nouvelles valeurs
           ui->tableView_station->setModel(tableView_station());
           ui->tableView_station->resizeColumnsToContents();
           ui->tableView_station_2->setModel(tableView_station_2());
           ui->tableView_station_2->resizeColumnsToContents();
           proposition();
           afficherImageSelonMode();

       } else {
           // La mise à jour a échoué
           // Afficher un message d'erreur
           QMessageBox::critical(this, tr("Erreur"), tr("Impossible de mettre à jour les données des stations."));
       }
       }else QMessageBox::information(this,tr("Base de données"),tr("Activation de mode economique non effectué"));
}



void station::on_pushButton_Eco_des_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this,"Base de données", "Etes vous sur de désactiver le mode economique?\n\n\nIMPORTANT\nMode Economique: Dès le désactivation, il va changer le mode de toutes les stations en Normale.", QMessageBox::Yes | QMessageBox::No);
           if(reply == QMessageBox::Yes) {
    QSqlQuery query;
       bool success = query.exec("UPDATE STATIONS SET MODE_ST='Normal'");
       if (success) {
           // La mise à jour a réussi
           // Actualiser le modèle de la table pour afficher les nouvelles valeurs
           ui->tableView_station->setModel(tableView_station());
           ui->tableView_station->resizeColumnsToContents();
           ui->tableView_station_2->setModel(tableView_station_2());
           ui->tableView_station_2->resizeColumnsToContents();
           proposition();
           afficherImageSelonMode();

       } else {
           // La mise à jour a échoué
           // Afficher un message d'erreur
           QMessageBox::critical(this, tr("Erreur"), tr("Impossible de mettre à jour les données des stations."));
       }
       }else QMessageBox::information(this,tr("Base de données"),tr("Activation de mode economique non effectué"));
}


//************Image_Economique********************
void station::afficherImageSelonMode() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM STATIONS WHERE MODE_ST = 'Economique'");
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QPixmap image(":/new/prefix1/ICON/economie-denergie.png"); // charger l'image X depuis les ressources de l'application
            ui->label_4->setPixmap(image);
        } else {
            QPixmap image(":/new/prefix1/ICON/economie-denergie2.png"); // charger l'image Y depuis les ressources de l'application
            ui->label_4->setPixmap(image);
        }
    } else {
        // afficher une erreur si la requête a échoué
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer les données des stations."));
    }
}

//************************************************************************arduino****************************************************************************
void station::arduino()
{
 data=A.read_from_arduino();
     QString state;
    QSqlQuery query;
    query.prepare("SELECT ETAT_ST FROM STATIONS WHERE ID_ST = 61");

    if(query.exec() && query.next()) {
           state = query.value(0).toString();
       }
if(state == "Libre") {
     A.write_to_arduino("0");}
else if(state == "Occupe")
{
     A.write_to_arduino("1");}
else if(state == "En panne")
{
     A.write_to_arduino("2");}
else if(state == "En repos")
{
     A.write_to_arduino("2");}



}


void station::capteur()
{
    data=A.read_from_arduino();

    if(data=="1")
    {
        QString state;
        QSqlQuery query1;
        query1.prepare("SELECT ETAT_ST FROM STATIONS WHERE ID_ST = 61");

        if(query1.exec() && query1.next()) {
               state = query1.value(0).toString();
           }
        if(state == "Libre")
               {
            QString neew = "Occupe";
            QSqlQuery query0;
            query0.prepare("UPDATE STATIONS SET ETAT_ST = :neew WHERE ID_ST = 61");
            query0.bindValue(":neew", neew);
            query0.exec();
        }
    }
    if(data=="2")
    {
        QString state;
        QSqlQuery query1;
        query1.prepare("SELECT ETAT_ST FROM STATIONS WHERE ID_ST = 61");

        if(query1.exec() && query1.next()) {
               state = query1.value(0).toString();
           }
        if(state == "Occupe")
               {
            QString neewe = "Libre";
            QSqlQuery query0;
            query0.prepare("UPDATE STATIONS SET ETAT_ST = :neewe WHERE ID_ST = 61");
            query0.bindValue(":neewe", neewe);
            query0.exec();
        }
    }

    ui->tableView_station->setModel(tableView_station());
    ui->tableView_station->resizeColumnsToContents();
    ui->tableView_station_2->setModel(tableView_station_2());
    ui->tableView_station_2->resizeColumnsToContents();


}


void station::aff7()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM STATIONS WHERE ETAT_ST = 'Libre'");
    int x = 0;
    static int y = 0; // initialiser y à -1 pour la première exécution de la fonction
    if (query.next()) {
        x = query.value(0).toInt();
    }

    if (y != 2) { // Si x est différent de la valeur précédente de y*/
        y++;
             qDebug() << "station despo :" << x;
          A.write_to_arduino(QByteArray::number(x));
    }
}



void station::lcd()
{
    QString state;
    QSqlQuery query1;
    query1.prepare("SELECT MODE_ST FROM STATIONS WHERE ID_ST = 61");
    query1.exec();
    if (query1.next()) { // Vérifie si la requête a renvoyé une ligne
        state = query1.value(0).toString();
        if(state == "Economique"){
            QSqlQuery query;
            query.prepare("SELECT CONSJ_ST FROM STATIONS WHERE ID_ST = 61");
            query.exec();
            if (query.next()) { // Vérifie si la requête a renvoyé une ligne
                int total = query.value(0).toInt();
                int reste = 300 - total;
                 qDebug() << "reste:" << reste;
                A.write_to_arduino(QByteArray::number(reste));
            }
        }
        else {
            int reste=301;
            A.write_to_arduino(QByteArray::number(reste));
        }
    }
}

