#include "client.h"
#include<QSqlQuery>
#include<QSqlQueryModel>




CLIENT::CLIENT(QString nom , QString prenom, int age )

{

this->nom=nom;

    this->prenom=prenom;

    this->age=age;


}

bool CLIENT::ajouter()

{

    QSqlQuery query;

    QString res=QString::number(age);






        query.prepare("INSERT INTO CLIENT (nom , prenom, age ) "

                           "VALUES (:nom, :prenom, :age)");







query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
 query.bindValue(":age", res);





    return    query.exec();



}
