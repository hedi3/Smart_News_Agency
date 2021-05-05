#include "programme.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
programme::programme()
{
    id=0;  nom="";
    lieuprog="";
}
programme::programme(QString nom, QDate dateprog, QString lieuprog)
{
    this->nom=nom; this->dateprog=dateprog;
    this->lieuprog=lieuprog;
}
int programme::getid(){return id;}
QString programme::getnom(){return nom;}
QDate programme::getdateprog(){return dateprog;}
QString programme::getlieuprog(){return lieuprog;}

void programme::setid(int id){this->id=id;}
void programme::setnom(QString nom){this->nom=nom;}
void programme::setdateprog(QDate dateprog){this->dateprog=dateprog;}
void programme::setlieuprog(QString lieuprog){this->lieuprog=lieuprog;}
bool programme::ajouter()
{
    QSqlQuery query;

        query.prepare("INSERT INTO programme (nom, dateprog, lieuprog) "
                      "VALUES (:nom, :dateprog, :lieuprog)");
        query.bindValue(0, nom);
        query.bindValue(1, dateprog);
        query.bindValue(2,lieuprog);


    return query.exec();

}
bool programme::supprimer(int id)
{
    QSqlQuery query;

        query.prepare("Delete from programme where id=:id");
        query.bindValue(0, id);

    return query.exec();
}
QSqlQueryModel* programme::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM programme ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateprog"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieuprog"));
    return model;
}
bool programme::modifier() {
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("UPDATE programme set nom=:nom, dateprog=:dateprog, lieuprog=:lieuprog where id=:id");
    query.bindValue(3, id_string);
    query.bindValue(0, nom);
    query.bindValue(1, dateprog);
    query.bindValue(2, lieuprog);
    return query.exec();
}
QSqlQueryModel* programme::listId() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id FROM programme");
    return model;
}

QSqlQueryModel* programme::Trier(QString tri) {
    QSqlQueryModel* model = new QSqlQueryModel();
    if(tri=="nom") {
        model->setQuery("SELECT * FROM programme ORDER BY nom");
    }
    else if(tri=="lieuprog") {
        model->setQuery("SELECT * FROM programme ORDER BY lieuprog");
    }

    return model;
}
