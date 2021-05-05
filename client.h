#ifndef CLIENT_H
#define CLIENT_H
#include<QString>


class CLIENT
{

    private:

        int age   ;
        QString nom , prenom ;
    public:
        //constructeurs
        CLIENT(){};
        CLIENT(QString,QString,int);

        //fonctions de base relative a l'entite employee
        bool ajouter();




};

#endif // CLIENT_H
