

#include "mission.h"
#include"QString"
#include<QPainter>
#include<QtPrintSupport/QPrinter>
#include<QPixmap>
#include<QTextDocument>
#include<QSqlQuery>

mission::mission(int ID_mission , QString nom_mission , QString lieu_mission )
{
this->ID_mission=ID_mission;
    this->nom_mission=nom_mission;
    this->lieu_mission=lieu_mission;

}
bool mission::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(ID_mission);


if((0<ID_mission) && (ID_mission<999999)){
         query.prepare("INSERT INTO mission (ID_MISSION  , NOM_MISSION , LIEU_MISSION) "
                            "VALUES (:ID_mission  , :nom_mission , :lieu_mission )");


        query.bindValue(":ID_mission", res);
        query.bindValue(":lieu_mission", lieu_mission);
        query.bindValue(":nom_mission", nom_mission);


}



        return    query.exec();
     }






QSqlQueryModel * mission::afficher()
{
    {QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from mission");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_mission"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("lieu_mission "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom_mission"));


        return model;
    }
}

bool mission  :: modifier( int ID_mission ,QString nom_mission , QString lieu_mission)
{

    QSqlQuery qry;
        qry.prepare("UPDATE MISSION set NOM_MISSION=(?) , LIEU_MISSION=(?) where ID_MISSION=(?)");


        qry.addBindValue(nom_mission);
        qry.addBindValue(lieu_mission);



         qry.addBindValue(ID_mission);
   return  qry.exec();
}
bool mission::supprimer(int ID_mission)
{

    QSqlQuery query;
    QString res= QString::number(ID_mission);
    query.prepare("Delete from mission where ID_mission = :ID_mission ");
    query.bindValue(":ID_mission", res);
    return    query.exec();
}
QSqlQueryModel * mission::recherche_nom(const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from mission where (( nom_mission ) LIKE '%"+aux+"%')");
    model->setHeaderData(0,Qt::Vertical,QObject::tr("ID_mission"));
    model->setHeaderData(1,Qt::Vertical,QObject::tr("nom_mission"));
    model->setHeaderData(2,Qt::Vertical,QObject::tr("lieu_mission"));


    return model;
}
