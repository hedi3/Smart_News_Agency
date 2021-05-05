#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QWidget>
#include<QSqlQueryModel>
class mission
{
private:

    int ID_mission ;
    QString   nom_mission, lieu_mission ;
public:
    //constructeurs
    mission(){};
    mission(int,QString,QString);
    // getters
    int getID_mission(){return ID_mission;}

    QString get_nom(){return nom_mission;}
    QString get_lieu(){return lieu_mission;}
    //setters
    void set_ID_mission(int n ){ID_mission=n;}

    void set_nom(QString hd){nom_mission=hd;}
    void set_type(QString hf){lieu_mission=hf;}
    //fonctions de base relative a l'entite employee
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int,QString , QString );

    bool supprimer(int);
    QSqlQueryModel * recherche_nom(const QString &aux);
};
#endif // MISSION_H
