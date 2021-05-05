#ifndef STUDIO_H
#define STUDIO_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class studio
{
public:
    studio();
    studio(int,QString,QString);

    int get_id();
    QString get_salle();
    QString get_dispo();
void set_id(int);
    //functions
    bool add();
    bool remove(int);
    bool modify();
     QSqlQueryModel * show();
     QSqlQueryModel * tri();
     QSqlQueryModel * search(const QString&);
     QSqlQueryModel * show_salle();
     QSqlQueryModel * show_dispo();
     QSqlQueryModel * show_id();
     QSqlQueryModel * show_one();

private:
    QString dispo, salle ;
    int id ;
};

#endif // STUDIO_H
