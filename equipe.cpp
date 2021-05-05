#include "equipe.h"
#include<QPainter>
#include<QtPrintSupport/QPrinter>
#include<QPixmap>
#include<QSqlQuery>
#include<QTextDocument>

equipe::equipe(int ID_equipe , int nbr_equipe,  QString nom_equipe,int id_mission  )
{
this->ID_equipe=ID_equipe;
    this->nbr_equipe=nbr_equipe;
    this->nom_equipe=nom_equipe;
    this->id_mission=id_mission;

}
bool equipe::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(ID_equipe);
    QString res1=QString::number(nbr_equipe);


         query.prepare("INSERT INTO equipe (ID_EQUIPE , NBR_EQUIPE , NOM_EQUIPE , id_mission ) "
                            "VALUES (:ID_equipe , :nbr_equipe , :nom_equipe , :id_mission )");


        query.bindValue(":ID_equipe", res);
        query.bindValue(":nbr_equipe", res1);


        query.bindValue(":nom_equipe", nom_equipe);
        query.bindValue(":id_mission", id_mission);






        return    query.exec();
     }







    QSqlQueryModel * equipe::afficher()
    {
        {QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from equipe");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_equipe"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_equipe"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom_equipe "));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_mission "));


            return model;
        }
    }


bool equipe  :: modifier( int ID_equipe ,int nbr_equipe, QString nom_equipe,int id_mission)
{

    QSqlQuery qry;
        qry.prepare("UPDATE equipe set nbr_equipe=(?),nom_equipe=(?),id_mission=(?) where ID_equipe=(?)");


        qry.addBindValue(nbr_equipe);
        qry.addBindValue(nom_equipe);
        qry.addBindValue(id_mission);
         qry.addBindValue(ID_equipe);
   return  qry.exec();
}
bool equipe::supprimer(int ID_equipe)
{

    QSqlQuery query;
    QString res= QString::number(ID_equipe);
    query.prepare("Delete from equipe where ID_equipe = :ID_equipe ");
    query.bindValue(":ID_equipe", res);
    return    query.exec();
}
QSqlQueryModel * equipe::trier_nbr()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from equipe order by nbr_equipe desc");
    model->setHeaderData(0,Qt::Vertical,QObject::tr("ID_equipe"));
    model->setHeaderData(1,Qt::Vertical,QObject::tr("nbr_equipe"));
    model->setHeaderData(2,Qt::Vertical,QObject::tr("nom_equipe"));


    return model ;

}
QSqlQueryModel * equipe::aficher_id()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select ID_MISSION from MISSION");
return model;
}
