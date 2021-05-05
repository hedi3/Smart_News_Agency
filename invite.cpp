#include "invite.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
invite::invite()
{
    id=0;  nom=""; prenom="";
    adresse="";
}
invite::invite(QString nom, QString prenom, QString adresse)
{
    this->nom=nom; this->prenom=prenom;
    this->adresse=adresse;
}
int invite::getid(){return id;}
QString invite::getnom(){return nom;}
QString invite::getprenom(){return prenom;}
QString invite::getadresse(){return adresse;}

void invite::setid(int id){this->id=id;}
void invite::setnom(QString nom){this->nom=nom;}
void invite::setprenom(QString prenom){this->prenom=prenom;}
void invite::setadresse(QString adresse){this->adresse=adresse;}
bool invite::ajouter()
{
    QSqlQuery query;

        query.prepare("INSERT INTO invite (nom, prenom, adresse) "
                      "VALUES (:nom, :prenom, :adresse)");
        query.bindValue(0, nom);
        query.bindValue(1, prenom);
        query.bindValue(2,adresse);


    return query.exec();

}
bool invite::supprimer(int id)
{
    QSqlQuery query;

        query.prepare("Delete from invite where id=:id");
        query.bindValue(0, id);

    return query.exec();
}
QSqlQueryModel* invite::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM invite ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    return model;
}
bool invite::modifier() {
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("UPDATE invite set nom=:nom, prenom=:prenom, adresse=:adresse where id=:id");
    query.bindValue(3, id_string);
    query.bindValue(0, nom);
    query.bindValue(1, prenom);
    query.bindValue(2, adresse);
    return query.exec();
}
QSqlQueryModel* invite::listId() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id FROM invite");
    return model;
}

QSqlQueryModel* invite::rechercher(QString rechercher,QString by) {
    QSqlQueryModel* model = new QSqlQueryModel();
    if(by=="nom") {
        model->setQuery("SELECT * FROM invite WHERE nom LIKE '"+rechercher+"%'");
    }
    else if(by=="prenom") {
       model->setQuery("SELECT * FROM invite WHERE prenom LIKE '"+rechercher+"%'");
    }

    return model;
}


bool invite::login(QString __input) {
    QSqlQuery query;
    query.prepare("select * from invite where nom = ?");
    query.addBindValue(__input);
    query.exec();
    while (query.next()) {
        this->id = query.value(0).toInt();
        this->nom = query.value(1).toString();
        this->prenom = query.value(2).toString();
        this->adresse = query.value(3).toString();
    }
    if (this->nom == __input) {
        return true;
    }
    return false;
}
