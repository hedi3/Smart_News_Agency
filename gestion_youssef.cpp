#include "gestion_youssef.h"
#include "ui_gestion_youssef.h"

#include "studio.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include  "QtSql"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "connexion.h"
#include <QComboBox>
#include "equipement.h"
#include "mainwindow.h"

gestion_youssef::gestion_youssef(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_youssef)
{
    ui->setupUi(this);
}

gestion_youssef::~gestion_youssef()
{
    delete ui;
}

void gestion_youssef::on_ajouter_clicked()
{
    int id=ui->id->text().toInt();
   QString dispo=ui->dispo->currentText();
   QString salle=ui->salle->currentText();

 bool test=studio(id,salle,dispo).add();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");

     msgBox.exec();
 }
 else{
     msgBox.setText("Echec d'ajout");
    msgBox.exec();
}
}

void gestion_youssef::on_afficher_clicked()
{
    QString choice =ui->comboBox_studio->currentText();
    if (choice == "Par date")
    {
    ui->Afficher_2->setModel(s1.show());
}
    if (choice == "ID")
    {
        ui->Afficher_2->setModel(s1.show_id());

    }
    if (choice == "Salle")
     {
        ui->Afficher_2->setModel(s1.show_salle());

    }
    if (choice == "Dispo")
     {
        ui->Afficher_2->setModel(s1.show_dispo());

    }

}

void gestion_youssef::on_supp_clicked()
{

    studio s;
    s.set_id(ui->read_studio->text().toInt());
       bool test=s.remove(s.get_id());
       QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
        msgBox.exec();

    }
    else{
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}
}

void gestion_youssef::on_ajouter_2_clicked()
{
    int nb=ui->nb->text().toInt();
   QString dispo_2=ui->dispo_2->currentText();
   QString name=ui->name->currentText();

 bool test=equipement(nb,name,dispo_2).add();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");

     msgBox.exec();
 }
 else{
     msgBox.setText("Echec d'ajout");
    msgBox.exec();
}
}

void gestion_youssef::on_afficher_3_clicked()
{

    QString choice =ui->comboBox_equipement->currentText();
    if (choice == "Par date")
    {
    ui->Afficher_4->setModel(eq1.show());
}
    if (choice == "nb")
    {
        ui->Afficher_4->setModel(eq1.show_nb());

    }
    if (choice == "dispo")
     {
        ui->Afficher_4->setModel(eq1.show_dispo());

    }
    if (choice == "name")
     {
        ui->Afficher_4->setModel(eq1.show_name());

    }
}

void gestion_youssef::on_supp_3_clicked()
{
    equipement  eq;
    eq.set_nb(ui->read_equipement->text().toInt());
       bool test=eq.remove(eq.get_nb());
       QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
        msgBox.exec();

    }
    else{
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}
}

void gestion_youssef::on_read_equipement_textChanged(const QString &arg1)
{


    //QModelIndexList indexes = ui->Afficher_4->model()->match(ui->Afficher_4->model()->index(0,0),Qt::EditRole,arg1,-1, Qt::MatchFlags(Qt::MatchContains|Qt::MatchWrap));

    /*if(indexes.length() > from){
        QModelIndex ix = indexes.at(from);
        ui->Afficher_4->setCurrentIndex(ix);
        ui->Afficher_4->scrollTo(ix);
    }*/

}

void gestion_youssef::on_read_equipement_returnPressed()
{
    ui->Afficher_4->setModel(eq1.showSearch(ui->read_equipement->text()));
}

void gestion_youssef::on_pdfEquip_clicked()
{
    equipement::printPDF(ui->Afficher_4);
    QMessageBox::information(nullptr, QObject::tr("PDF Saved"),
                      QObject::tr("PDF file saved as equipement.pdf"), QMessageBox::Ok);

}

void gestion_youssef::on_actiondeconnecter_triggered()
{
    close();
        MainWindow *ws;
    ws = new MainWindow();
ws->setWindowTitle("News Agency");
ws->show();
}
