#include "equipements.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QObject>
Equipement::Equipement()
{
id_equipement=0;
materiel="";
poste="";
id_employee=0;
}

Equipement::Equipement(int id_equipement ,QString materiel, QString poste, int id_employee)
{this->id_equipement=id_equipement;
    this->materiel=materiel;
    this->poste=poste;
    this->id_employee=id_employee;}
int Equipement::getid_equipement(){return id_equipement;}
QString Equipement::getmateriel(){return materiel;}
QString Equipement::getposte() {return poste;}
int Equipement::getid_employee(){return id_employee;}
void Equipement::setid_equipement(int id_equipement) {this->id_equipement=id_equipement;}
void Equipement::setmateriel(QString materiel){this->materiel;}
void Equipement::setposte(QString poste){this->poste;}
void Equipement::setid_employee(int id_employee){this->id_employee;}
bool Equipement::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Equipement (id_equipement,materiel,poste,id_employee) VALUES (:id_equipement,:materiel,:poste,:id_employee)");
    query.bindValue(":id_equipement",id_equipement);
    query.bindValue(":materiel",materiel);
    query.bindValue(":poste",poste);
    query.bindValue(":id_employee",id_employee);
    return query.exec();
}
bool Equipement::supprimer(int id_equipement)
{
    QSqlQuery query;
    query.prepare("delete from EQUIPEMENT where id_equipement = :id_equipement") ;

    query.bindValue(":id_equipement",id_equipement);

    return query.exec();
}
QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();





          model->setQuery("SELECT * FROM Equipement");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("materiel"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("poste"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_employee"));
    return model;
}

bool Equipement::modifier(int id_equipement)
{
    QSqlQuery query;
    query.prepare("UPDATE Equipement SET materiel =:materiel,poste =:poste,id_employee =:id_employee WHERE id_equipement=:id_equipement ");
    query.bindValue(":id_equipement",id_equipement);
    query.bindValue(":materiel",materiel);
    query.bindValue(":poste",poste);
    query.bindValue(":id_employee",id_employee);
    return query.exec();
}

