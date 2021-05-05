#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H

#include <QString>
#include <QSqlQueryModel>
class Equipement
{
public:
    Equipement();
    Equipement(int ,QString,QString,int);
    int getid_equipement();
    QString getmateriel();
    QString getposte();
    int getid_employee();
    void setid_equipement(int);
    void setmateriel(QString);
    void setposte(QString);
    void setid_employee(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int id_equipement);
    bool modifier(int id_equipement);
private:
    int id_equipement;
    QString materiel , poste;
       int id_employee;

   };

   #endif // EQUIPEMENTS_H

