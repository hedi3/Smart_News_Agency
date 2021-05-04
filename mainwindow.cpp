#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mission.h"
#include<QMessageBox>
#include"equipe.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QSqlQuery>
#include "smtp.h"
#include<QPropertyAnimation>
#include <QSqlTableModel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView_4->setModel(tmpequipe.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_pushButton_clicked()
{

    //animation
        QPushButton button("Appuyer sur OK! ");
            button.show();

            QPropertyAnimation animation(&button, "geometry");
            animation.setDuration(3000);
            animation.setStartValue(QRect(500, 500, 200, 30));
            animation.setEndValue(QRect(580, 180, 300, 50));

            animation.setEasingCurve(QEasingCurve::OutBounce);

            animation.start();
            int ID_mission=ui->lineEdit_id_miss->text().toInt();

            QString nom_mission=ui->lineEdit_nom_miss->text();
            QString lieu_mission=ui->lineEdit_lieu_miss->text();


        mission d( ID_mission , nom_mission , lieu_mission );
        bool test=d.ajouter();
        if(test)
        {
            ui->tableView_miss->setModel(d.afficher());
            ui->combo->setModel(d.aficher_id());
            ui->comboBox->setModel(d.aficher_id());

            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("ajout effectue \n click cancel to exit."), QMessageBox::Cancel);
        }else  QMessageBox::critical(nullptr,QObject::tr("erreur"),QObject::tr("verifier votre saisie\n click cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_5_clicked()
{
    mission Etmp;

            {ui->tableView_miss->setModel(Etmp.afficher());}
}

void MainWindow::on_pushButton_3_clicked()
{
    mission s;

        //click modif
                int ID_mission = ui->lineEdit_id_modif->text().toInt();
                QString nom_mission = ui->lineEdit_nom_modif_miss->text();
                QString lieu_mission= ui->lineEdit_lieu_modif_miss->text();


                mission  ( ID_mission , nom_mission,  lieu_mission ) ;
                bool test =s.modifier( ID_mission , nom_mission,  lieu_mission );
                if(test)
                {ui->tableView_miss->setModel(s.afficher());
                    QMessageBox::information(nullptr, QObject::tr("modifier une mission "),
                                             QObject::tr("mission  modifié.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);}
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier une mission"),
                                          QObject::tr("Erreur !.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_4_clicked()
{
    mission Etmp;

        //click supp
            Etmp.set_ID_mission(ui->lineEdit_supp_miss->text().toInt());
            QMessageBox msgbox;
                msgbox.setWindowTitle("supprimer");
                msgbox.setText("voulez_vous supprimer cette mission ?");
                msgbox.setStandardButtons(QMessageBox ::Yes);
                msgbox.addButton(QMessageBox::No);
                if(msgbox.exec()==QMessageBox::Yes)
                {

          bool test=Etmp.supprimer(Etmp. getID_mission());
          QMessageBox msgBox;

          if(test)
          {
              QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("suppression effectuée \n click cancel to exit."), QMessageBox::Cancel);
              {ui->tableView_miss->setModel(Etmp.afficher());}

          }
          else
              QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("suppression non effectuer.\n click cancel to exit."), QMessageBox::Cancel);
          msgBox.exec();

        }
}





void MainWindow::on_pushButton_11_clicked()
{
    //  recherche mission
              QString text;
              mission e;

               text=ui->lineEdit_recherche_nom->text();

               if(text == "")

               {

                   ui->tableView_miss->setModel(e.afficher());

               }

               else

               {
                   ui->tableView_miss->setModel(e.recherche_nom(text)); }
}

void MainWindow::on_pushButton_6_clicked()
{
    equipe m;

            int ID_equipe=ui->lineEdit_11->text().toInt();
            QString nom_equipe=ui->lineEdit_12->text();
            int nbr_equipe=ui->lineEdit_13->text().toInt();
            int id_mission= ui->combo->currentText().toInt();


        equipe d( ID_equipe , nbr_equipe , nom_equipe,id_mission );
        bool test=d.ajouter();
        if(test)
        {
            ui->tableView_4->setModel(d.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("ajout effectue \n click cancel to exit."), QMessageBox::Cancel);
            printf("test");
        }else  QMessageBox::critical(nullptr,QObject::tr("erreur"),QObject::tr("verifier votre saisie\n click cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_9_clicked()
{
    equipe Etmp;

            {ui->tableView_4->setModel(Etmp.afficher());}
}

void MainWindow::on_pushButton_7_clicked()
{
    equipe s;

        //click modif
                int ID_equipe = ui->lineEdit_14->text().toInt();
                int nbr_equipe = ui->lineEdit_16->text().toInt();
                QString nom_equipe= ui->lineEdit_15->text();
                int id_mission= ui->comboBox->currentText().toInt();


                equipe  ( ID_equipe , nbr_equipe,  nom_equipe,id_mission ) ;
                bool test =s.modifier( ID_equipe , nbr_equipe,  nom_equipe,id_mission );
                if(test)
                {ui->tableView_4->setModel(s.afficher());
                    QMessageBox::information(nullptr, QObject::tr("modifier une equipe "),
                                             QObject::tr("equipe  modifié.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);}
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier une mission"),
                                          QObject::tr("Erreur !.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_8_clicked()
{
    equipe Etmp;

        //click supp
            Etmp.set_ID_equipe(ui->lineEdit_17->text().toInt());
            QMessageBox msgbox;
                msgbox.setWindowTitle("supprimer");
                msgbox.setText("voulez_vous supprimer cette mission ?");
                msgbox.setStandardButtons(QMessageBox ::Yes);
                msgbox.addButton(QMessageBox::No);
                if(msgbox.exec()==QMessageBox::Yes)
                {

          bool test=Etmp.supprimer(Etmp. getID_equipe());
          QMessageBox msgBox;

          if(test)
          {
              QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("suppression effectuée \n click cancel to exit."), QMessageBox::Cancel);
              {ui->tableView_4->setModel(Etmp.afficher());}

          }
          else
              QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("suppression non effectuer.\n click cancel to exit."), QMessageBox::Cancel);
          msgBox.exec();

        }
}




void MainWindow::on_pushButton_12_clicked()
{
    //trier par nbr
        equipe Etmp;
        ui->tableView_4->setModel(Etmp.trier_nbr());
}



void MainWindow::on_pushButton_13_clicked()
{
    QDialog QFileDialog;
         QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("reclamation.pdf"); }

                 QPrinter printer(QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setPaperSize(QPrinter::A4);
                 printer.setOutputFileName(fileName);

                 /*QPrinter printer;*/
                 ui->tableView_4->render(&printer);




                 QTextDocument doc;
                 QSqlQuery q;
                 q.prepare("SELECT * FROM reclamation ");
                 q.exec();
                 QString pdf="<br> <img src='D:/Esprit/2A2/projet c++/logo/debug2.png' height='42' width='144'/> <h1  style='color:red'>LISTE DES RECLAMATION  <br></h1>\n <br> <table>  <tr>  <th> CODE </th> <th> SUJET </th> <th> COMMENTAIRE </th> <th> DATE AJOUT </th>  </tr>" ;


                 while ( q.next()) {

                     pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>   <td>   " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +"  "" " "</td>   <td>"+q.value(3).toString()+"</td>    <td>"+q.value(4).toString()+" </td>" ;

                 }
                 doc.setHtml(pdf);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
              /*   doc.print(&printer);*/
                 ui->tableView_4->render(&printer);
}

void MainWindow::on_pushButton_2_clicked()
{
    equipe s;
        ui->label_stat1->setNum(((s.stati1())*100/s.nb_total()));
}

void MainWindow::on_pushButton_14_clicked()
{
    equipe s;
        ui->label_stat2->setNum(((s.stati2())*100/s.nb_total()));
}

void MainWindow::on_pushButton_15_clicked()
{
    equipe s;
        ui->label_stat3->setNum(((s.stati3())*100/s.nb_total()));

}








void MainWindow::on_sendBtn_4_clicked()
{
    printf("test");
        Smtp* smtp = new Smtp(ui->uname_4->text(), ui->paswd_4->text(), ui->server_4->text(), ui->port_4->text().toUShort());
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


            smtp->sendMail(ui->uname_4->text(), ui->rcpt_4->text() , ui->subject_4->text(),ui->msg_4->toPlainText());
        QString status;
        QMessageBox::information(this,"OK","notification envoyé!");
            if(status == "Message sent")
                QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
