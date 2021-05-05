#include "studio.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

studio::studio()
{
    id=0;
    salle="";
    dispo="";

}

studio::studio(int id, QString salle, QString dispo )
{
    this->id=id;
    this->salle=salle;
    this->dispo=dispo;
 }

int studio::get_id(){return id;}
QString studio::get_salle(){return salle;}
QString studio::get_dispo(){return dispo;}
void studio::set_id(int id){this->id=id;}
bool studio::add(){
    QSqlQuery query;
    query.prepare("INSERT INTO STUDIO (ID, SALLE, DISPO)"
                  "VALUES(:ID, :SALLE, :DISPO )");
    query.bindValue(":ID",id);
    query.bindValue(":SALLE",salle);
    query.bindValue(":DISPO",dispo);
    return query.exec();
}

QSqlQueryModel * studio::show()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STUDIO");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

bool studio::remove(int id)
{
QSqlQuery query;
QString toSearch= QString::number(id);
query.prepare("DELETE FROM STUDIO WHERE ID = :ID");
query.bindValue(":ID", toSearch);
return    query.exec();
}
QSqlQueryModel * studio::show_salle()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STUDIO ORDER BY salle DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

QSqlQueryModel * studio::show_dispo()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STUDIO ORDER BY DISPO DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}
QSqlQueryModel * studio::show_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STUDIO ORDER BY ID DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}
QSqlQueryModel * studio::show_one()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STUDIO ORDER BY ID DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

