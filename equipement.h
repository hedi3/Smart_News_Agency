#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>


class equipement
{
public:
    equipement();
    equipement(int,QString,QString);

    int get_nb();
    QString get_name();
    QString get_dispo();
    void set_nb(int);
    //functions
    bool add();
    bool remove(int);
    bool modify();
    QSqlQueryModel * show();
    QSqlQueryModel * tri();
    QSqlQueryModel * search(const QString&);
     QSqlQueryModel * show_name();
     QSqlQueryModel * show_dispo();
     QSqlQueryModel * show_nb();
     QSqlQueryModel * show_one();
     QSqlQueryModel * showSearch(QString txt);
     static void printPDF(QTableView* table);

private:
    QString dispo, name ;
    int nb ;
};

#endif // STUDIO_H
