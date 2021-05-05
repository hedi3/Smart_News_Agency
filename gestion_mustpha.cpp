#include "gestion_mustpha.h"
#include "ui_gestion_mustpha.h"
#include "mainwindow.h"

gestion_mustpha::gestion_mustpha(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_mustpha)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);


}

gestion_mustpha::~gestion_mustpha()
{
    delete ui;
}

void gestion_mustpha::on_pushButton_clicked()
{
    ui->T_invite ->setModel(I.afficher());
       ui->CB_idInv ->setModel(I.listId());
     ui->stackedWidget->setCurrentIndex(1);
}

void gestion_mustpha::on_B_Ajouterinv_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void gestion_mustpha::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void gestion_mustpha::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de l'ajout", "Confirmer l'ajout du citoyen?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {

        QString nom = ui->LE_Anominv->text();
        QString prenom = ui->LE_Prenominv->text();
        QString adresse = ui->LE_Adresseinv->text();
    invite I(nom,prenom,adresse);
    if(I.ajouter()) {
        ui->T_invite ->setModel(I.afficher());
        ui->CB_idInv->setModel(I.listId());
        ui->stackedWidget->setCurrentIndex(1);

        ui->LE_Anominv ->setText("");
        ui->LE_Prenominv ->setText("");
        ui->LE_Adresseinv->setText("");

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Nope"), QObject::tr("L'ajout a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
    }
    }
}

void gestion_mustpha::on_B_modifierinv_clicked()
{
    QSqlQuery qry;
    QString id_string = QString::number(ui->CB_idInv->currentText().toInt());
    qry.prepare("SELECT * FROM invite where id=:id");
    qry.bindValue(0, id_string);
    if(qry.exec()) {
        while(qry.next()) {
            ui->LE_Mnominv ->setText(qry.value(1).toString());
            ui->LE_MPrenominv->setText(qry.value(2).toString());
            ui->LE_MAdresseinv->setText(qry.value(3).toString());

        }
    }
    ui->stackedWidget->setCurrentIndex(3);
}

void gestion_mustpha::on_annulermodif_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_mustpha::on_confirmermodif_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de la modification", "Confirmer la modification du citoyen?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        invite I;
        I.setid(ui->CB_idInv ->currentText().toInt());
        I.setnom(ui->LE_Mnominv ->text());
        I.setprenom(ui->LE_MPrenominv ->text());
        I.setadresse(ui->LE_MAdresseinv ->text());
        if(I.modifier()) {
            ui->T_invite->setModel(I.afficher());
            ui->CB_idInv->setModel(I.listId());
            ui->stackedWidget->setCurrentIndex(1);
            ui->LE_Anominv->setText("");
            ui->LE_Prenominv->setText("");
            //QDate date_Naiss = ui->DE_MDateNaissCit->date();
          //  ui->DE_MDateNaissCit->setDate();
            ui->LE_Adresseinv->setText("");
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Nope"), QObject::tr("La modification a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
        }
    }
}

void gestion_mustpha::on_B_supprimerrinv_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de la suppression", "Confirmer la suppression du service?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        I.setid(ui->CB_idInv->currentText().toInt());
        if(I.supprimer(I.getid())) {
            qDebug() << "Suppression Complet";
            ui->T_invite->setModel(I.afficher());
            ui->CB_idInv->setModel(I.listId());

        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Nope"),
                        QObject::tr("Suppression a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
        }
    }
}

void gestion_mustpha::on_B_Ajouterprog_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void gestion_mustpha::on_B_modifierprog_clicked()
{
    QSqlQuery qry;
    QString id_string = QString::number(ui->CB_idprog->currentText().toInt());
    qry.prepare("SELECT * FROM programme where id=:id");
    qry.bindValue(0, id_string);
    if(qry.exec()) {
        while(qry.next()) {
            ui->LE_Mnomprog ->setText(qry.value(1).toString());
            ui->Mdate_prog->setDate(qry.value(2).toDate());
            ui->LE_Mdresseprog->setText(qry.value(3).toString());
        }
    }
    ui->stackedWidget->setCurrentIndex(6);
}

void gestion_mustpha::on_annulerajoutprog_clicked()
{
   ui->stackedWidget->setCurrentIndex(4);
}

void gestion_mustpha::on_confirmeajoutprog_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de l'ajout", "Confirmer l'ajout du citoyen?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {

        QString nom = ui->LE_Anomprog->text();
        QDate dateprog= ui->date_prog->date();
        QString lieuprog = ui->LE_Adresseprog->text();

    programme P(nom,dateprog,lieuprog);
    if(P.ajouter()) {
        ui->T_progrmme ->setModel(P.afficher());
        ui->CB_idprog ->setModel(P.listId());
        ui->stackedWidget->setCurrentIndex(4);

        ui->LE_Anomprog ->setText("");
        ui->LE_Adresseprog->setText("");

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Nope"), QObject::tr("L'ajout a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
    }
    }
}

void gestion_mustpha::on_annulermodifprog_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void gestion_mustpha::on_confirmemodifprog_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de la modification", "Confirmer la modification du citoyen?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        programme P;
        P.setid(ui->CB_idprog ->currentText().toInt());
        P.setnom(ui->LE_Mnomprog ->text());
        P.setdateprog(ui->Mdate_prog ->date());
        P.setlieuprog(ui->LE_Mdresseprog ->text());


        if(P.modifier()) {
            ui->T_progrmme->setModel(P.afficher());
            ui->CB_idprog->setModel(P.listId());
            ui->stackedWidget->setCurrentIndex(4);
            ui->LE_Anomprog->setText("");

            ui->LE_Adresseprog->setText("");
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Nope"), QObject::tr("La modification a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
        }
    }
}

void gestion_mustpha::on_B_supprimerprog_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de la suppression", "Confirmer la suppression du service?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        P.setid(ui->CB_idprog->currentText().toInt());
        if(P.supprimer(P.getid())) {
            qDebug() << "Suppression Complet";
            ui->T_progrmme->setModel(P.afficher());
            ui->CB_idprog->setModel(P.listId());

        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Nope"),
                        QObject::tr("Suppression a échoué.\n" "Cliquer Ok."), QMessageBox::Ok);
        }
    }
}

void gestion_mustpha::on_pushButton_5_clicked()
{
    ui->T_progrmme ->setModel(P.afficher());
       ui->CB_idprog ->setModel(P.listId());
    ui->stackedWidget->setCurrentIndex(4);
}

void gestion_mustpha::on_lineEdit_textChanged(const QString &arg1)
{
    QString by=ui->boxi->currentText();
         ui->T_invite->setModel(I.rechercher(arg1,by));
}

void gestion_mustpha::on_trier_clicked()
{
    QString Tri = ui->boxp->currentText();
            ui->T_progrmme->setModel(P.Trier(Tri));
}

void gestion_mustpha::on_pushButton_2_clicked()
{
    QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C:/Users/user/Desktop/MonPDF.pdf");
            QPainter painter;
            painter.begin(&printer);

            QFont font;
            //QString code=ui->lineEdit_code_pdf_3->text();
            QSqlQuery query;
            int id=0;
            QString nom,prenom,address;
            int toTest = ui->CB_idInv->currentText().toInt();
            QString test = QString::number(toTest);

            if (test!="")
            {
                query.prepare("select * from invite where id='"+test+"'");
                if (query.exec())
                {
                    while (query.next())
                    {
                        id=query.value(0).toInt();
                        nom=query.value(1).toString();
                        prenom=query.value(2).toString();
                        address=query.value(3).toString();

                    }
                }
                QString id_s = QString::number(id);
                font.setPixelSize(50);
                painter.setFont(font);
                painter.setPen(Qt::red);
                painter.drawText(350,150,"invité");

                font.setPixelSize(35);
                painter.setFont(font);
                painter.setPen(Qt::blue);
                painter.drawText(20,300,"ID: ");
                painter.drawText(20,450,"Nom:");
                painter.drawText(20,600,"Prenom:");
                painter.drawText(20,750,"Address:");


                font.setPixelSize(22);
                painter.setFont(font);
                painter.setPen(Qt::black);
                painter.drawText(300,300,id_s);
                painter.drawText(300,450,nom);
                painter.drawText(300,600,prenom);
                painter.drawText(300,750,address);

            }

            QImage image("C:/Users/user/Desktop/Nouveau dossier (2)/img");
            painter.drawImage(-30,-100,image);

            painter.end();
            qDebug()<<"le pdf a ete cree";
            QMessageBox::information(this,"pdf cree","ce pdf a ete cree");
}




void gestion_mustpha::on_actiondeconnecter_triggered()
{
    close();
        MainWindow *ws;
    ws = new MainWindow();
ws->setWindowTitle("News Agency");
ws->show();
}

void gestion_mustpha::on_B_retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void gestion_mustpha::on_B_retour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
