#ifndef EQUIPE_H
#define EQUIPE_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QSqlQueryModel>

class equipe
{
private:

    int ID_equipe , nbr_equipe,id_mission;
    QString nom_equipe ;
public:
    //constructeurs
    equipe(){};
    equipe(int,int,QString,int);
    // getters
    int getID_equipe(){return ID_equipe;}

    //setters
    void set_ID_equipe(int n ){ID_equipe=n;}
    void set_nbr(int p){nbr_equipe=p;}

    void set_nom(QString hd){nom_equipe=hd;}

    //fonctions de base relative a equipe
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int, int , QString,int );

    bool supprimer(int);
    QSqlQueryModel *  trier_nbr();
    QSqlQueryModel * aficher_id();

};

#endif // EQUIPE_H
