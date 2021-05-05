#ifndef GESTION_MUSTPHA_H
#define GESTION_MUSTPHA_H

#include <QMainWindow>
#include "invite.h"
#include "programme.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QDebug>
#include <QPainter>
#include <QtPrintSupport/QPrinter>


namespace Ui {
class gestion_mustpha;
}

class gestion_mustpha : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_mustpha(QWidget *parent = nullptr);
    ~gestion_mustpha();


private slots:
    void on_pushButton_clicked();

    void on_B_Ajouterinv_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_B_modifierinv_clicked();

    void on_annulermodif_clicked();

    void on_confirmermodif_clicked();

    void on_B_supprimerrinv_clicked();

    void on_B_Ajouterprog_clicked();

    void on_B_modifierprog_clicked();

    void on_annulerajoutprog_clicked();

    void on_confirmeajoutprog_clicked();

    void on_annulermodifprog_clicked();

    void on_confirmemodifprog_clicked();

    void on_B_supprimerprog_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_trier_clicked();

    void on_pushButton_2_clicked();

    void on_actiondeconnecter_triggered();


    void on_B_retour_clicked();

    void on_B_retour_2_clicked();

private:
    Ui::gestion_mustpha *ui;
    invite I;
    programme P;

};

#endif // GESTION_MUSTPHA_H
