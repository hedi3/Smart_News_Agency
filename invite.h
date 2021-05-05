#ifndef INVITE_H
#define INVITE_H

#include<QString>
#include <QSqlQueryModel>
class invite
{
public:
    invite();

    invite(QString, QString, QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
     bool modifier();
     QSqlQueryModel* rechercher(QString,QString);
    QSqlQueryModel* listId();
    bool login(QString __input);

private:
    int id ;
    QString nom , prenom , adresse;
};

#endif // INVITE_H
