#ifndef JOURNALISTE_H
#define JOURNALISTE_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class journaliste
{
public:
    journaliste();
    journaliste(QString,QString,QString);

    bool ajouter();
    bool modifier(QString);
     QSqlQueryModel * afficher();
      bool supprimer(QString);
    bool login(QString __input) ;

    QString id,nom,specialite;

};

#endif // JOURNALISTE_H
