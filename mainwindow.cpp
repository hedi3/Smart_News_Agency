#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include<QDateTime>
#include <QMainWindow>
#include "chat.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction1()));
    timer->start(1000);

    c.createconnect();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction1()
{
QTime time=QTime::currentTime();
QString time_text=time.toString("hh : mm : ss");
if ((time.second()% 2)==0){
    time_text[3]=' ';
    time_text[8]=' ';


}
ui->label_datetime->setText(time_text);


}

void MainWindow::on_pushButton_submit_clicked()
{
    QString userID;


    //extract userId and password

    userID=ui->lineEdit_userID->text();
    given_password= ui->lineEdit_password->text();

    //check if user is in default list
    QString users="ons/malek/youssef/hedi/mustpha"; // you add your ID in format admin(first 2 letters of your departement name)
    bool user_ex = users.contains(userID);

    //check if password is in default list
    QString password ="admin/1234"; // you add your password in format ADM-(first 2 letters of your departement name)
    bool pass_ex = password.contains(given_password);



   if( userID.length()<1 )
           ui->statusbar->showMessage("Check userID format",3000);
        else if( given_password.length()<4 )
               ui->statusbar->showMessage("Password too short",3000);
  else
       if(ui->rb_admin->isChecked()) {
           if(user_ex && pass_ex){



close();

//open ons Space
/*
 ---------------pour tester------------
 username : ons
 mdp : admin
 --------------------------------------
*/

if (userID=="ons"){
gestion_ons *ws;
ws = new gestion_ons();
ws->setWindowTitle("News Agency");
ws->show();
}

//open malek Space
/*
 ---------------pour tester------------
 username : malek
 mdp : admin
 --------------------------------------
*/

if (userID=="malek"){
gestion_malek *ws;
ws = new gestion_malek();
ws->setWindowTitle("News Agency");
ws->show();
}

//open youssef Space
/*
 ---------------pour tester------------
 username : youssef
 mdp : admin
 --------------------------------------
*/

if (userID=="youssef"){
gestion_youssef *ws;
ws = new gestion_youssef();
ws->setWindowTitle("News Agency");
ws->show();
}


//open hedi Space
/*
 ---------------pour tester------------
 username : hedi
 mdp : admin
 --------------------------------------
*/

if (userID=="hedi"){
gestion_hedi *ws;
ws = new gestion_hedi();
ws->setWindowTitle("News Agency");
ws->show();
}

//open mustpha Space
/*
 ---------------pour tester------------
 username : mustpha
 mdp : admin
 --------------------------------------
*/

if (userID=="mustpha"){
gestion_mustpha *ws;
ws = new gestion_mustpha();
ws->setWindowTitle("News Agency");
ws->show();
}

    }
//end test login

else ui->statusbar->showMessage("login and password don't match",3000);

}
       else if (ui->rb_invite->isChecked()) {
           QString username =ui->lineEdit_userID->text();
           QString password = ui->lineEdit_password->text();
           if( username == password ) {
               if(__invite.login(username)) {
                   Chat *ws = new Chat();
                   ws->nom = username;
                   ws->type = "Invite";
                   ws->show();
               }
               else
                ui->statusbar->showMessage("login and password don't match",3000);
           }
       }
       else if (ui->rb_journaliste->isChecked()) {
           QString username =ui->lineEdit_userID->text();
           QString password = ui->lineEdit_password->text();
           if( username == password ) {
               if(__journaliste.login(username)) {
                   Chat *ws = new Chat();
                   ws->nom = username;
                   ws->type = "Journaliste";
                   ws->show();
               }
               else
                ui->statusbar->showMessage("login and password don't match",3000);
           }
       }

}
