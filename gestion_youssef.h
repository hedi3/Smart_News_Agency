#ifndef GESTION_YOUSSEF_H
#define GESTION_YOUSSEF_H

#include <QMainWindow>
#include "equipement.h"
#include "studio.h"
#include "connexion.h"


namespace Ui {
class gestion_youssef;
}

class gestion_youssef : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_youssef(QWidget *parent = nullptr);
    ~gestion_youssef();

private slots:

    void on_ajouter_clicked();

    void on_afficher_clicked();

    void on_supp_clicked();

    void on_ajouter_2_clicked();

    void on_afficher_3_clicked();




    void on_supp_3_clicked();

    void on_read_equipement_textChanged(const QString &arg1);

    void on_read_equipement_returnPressed();

    void on_pdfEquip_clicked();


    void on_actiondeconnecter_triggered();

private:
    Ui::gestion_youssef *ui;
    studio s1;
    equipement eq1;
};

#endif // GESTION_YOUSSEF_H
