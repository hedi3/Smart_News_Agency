#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
class Employe
{
public:
    Employe();
    Employe(int ,QString,QString,QString,int);
    int getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    int gettelephone();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void settelephone(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int);
    bool modifier(int id);
    QSqlQueryModel * Find_Employe();
    QSqlQueryModel * rechercher(QString search);
    QSqlQueryModel * tri();
private:
    int id;
    QString nom , prenom,adresse ;
       int telephone;

   };

   #endif //
