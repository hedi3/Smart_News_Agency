#ifndef PROGRAMME_H
#define PROGRAMME_H

#include<QString>
#include<QDate>
#include <QSqlQueryModel>
class programme
{
public:
    programme();

    programme(QString, QDate, QString);
    int getid();
    QString getnom();
    QDate getdateprog();
    QString getlieuprog();
    void setid(int);
    void setnom(QString);
    void setdateprog(QDate);
    void setlieuprog(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
     bool modifier();
     QSqlQueryModel* Trier(QString);
    QSqlQueryModel* listId();
private:
    int id ;
    QString nom , lieuprog ;
    QDate dateprog;
};

#endif // PROGRAMME_H
