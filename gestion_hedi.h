#ifndef GESTION_HEDI_H
#define GESTION_HEDI_H

#include <QMainWindow>
#include "mission.h"
#include<QMessageBox>
#include"equipe.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QSqlQuery>
#include "stat_combo.h"

#include<QPropertyAnimation>

namespace Ui {
class gestion_hedi;
}

class gestion_hedi : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_hedi(QWidget *parent = nullptr);
    ~gestion_hedi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_actiondeconnecter_triggered();

    void on_sendBtn_4_clicked();

    void on_stat_clicked();

    void on_tableView_4_clicked(const QModelIndex &index);

private:
    Ui::gestion_hedi *ui;
    equipe tmpequipe;
    mission tmpmission;
    stat_combo *s;
};

#endif // GESTION_HEDI_H
