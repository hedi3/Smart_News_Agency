#ifndef GESTION_MALEK_H
#define GESTION_MALEK_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QtWidgets/QMessageBox>


#include "publicite.h"
#include "sponsor.h"
#include "smtp.h"
#include "stat_publicite.h"



namespace Ui {
class gestion_malek;
}

class gestion_malek : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_malek(QWidget *parent = nullptr);
    ~gestion_malek();

    //publicite
    double cout() const;
    QString sponsors() const;
    QString type() const;
    QString id() const ;

    void get_sponsor();
    void fill_form(QString);


    //sponsor
    QString prenom() const;
    QString nom() const;
    QString id2() const ;

    void fill_form2(QString);

    void clear_fields();

    sponsor tmp_sponsor;
    publicite tmp_publicite;
    QSortFilterProxyModel *proxy_sponsor,*proxy_publicite;
    void show_sponsor();
    void show_publicite();
    void show_tables();
private slots:
    void on_actionadd_sponsor_clicked();

    void on_table_sponsor_clicked(const QModelIndex &index);

    void on_table_sponsor_doubleClicked(const QModelIndex &index);

    void on_actionedit_sponsor_clicked();

    void on_actiondelete_sponsor_clicked();

    void on_sponsor_sel_col_currentIndexChanged(const QString &arg1);

    void on_rech_sponsor_textChanged(const QString &arg1);

    void on_actionadd_publicite_clicked();

    void on_table_publicite_clicked(const QModelIndex &index);

    void on_table_publicite_doubleClicked(const QModelIndex &index);

     void on_actionedit_publicite_clicked();

    void on_actiondelete_publicite_clicked();

    void on_publicite_sel_col_currentIndexChanged(const QString &arg1);

    void on_rech_publicite_textChanged(const QString &arg1);

    void on_stat_clicked();

    void sendMail();

    void mailSent(QString);

    void browse();




    void on_actiondeconnecter_triggered();

private:
    Ui::gestion_malek *ui;
    QString selected_sponsor="",selected_publicite="";
    int sel_col_sponsor=-1,sel_col_publicite=-1;
    stat_publicite *s;
    QStringList files;

};

#endif // GESTION_MALEK_H
