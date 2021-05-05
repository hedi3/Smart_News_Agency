#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connexion.h"
#include "gestion_ons.h"
#include "gestion_malek.h"
#include "gestion_youssef.h"
#include "gestion_hedi.h"
#include "gestion_mustpha.h"
#include<QTimer>
#include<QDateTime>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString userID;
    QString given_password;

    private slots:
        void on_pushButton_submit_clicked();
        void myfunction1();

private:
    Ui::MainWindow *ui;
     Connexion c;
     QTimer *timer;
     invite __invite;
     journaliste __journaliste;
};
#endif // MAINWINDOW_H
