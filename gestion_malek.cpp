#include "gestion_malek.h"
#include "ui_gestion_malek.h"
#include "mainwindow.h"

gestion_malek::gestion_malek(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_malek)
{
    ui->setupUi(this);

    //show database content
    show_tables();

    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    //fill sponsor combobox
    get_sponsor();

}

gestion_malek::~gestion_malek()
{
    delete ui;
}

void gestion_malek::show_tables()
{
    show_publicite();
    show_sponsor();
}

void gestion_malek::clear_fields()
{
ui->id->clear();
ui->id2->clear();
ui->nom->clear();
ui->prenom->clear();
ui->cout->clear();
ui->type->setCurrentIndex(0);
ui->sponsor->clear();

}

/*********************************** sponsor ****************************/


//get form content
QString gestion_malek::prenom() const { //combo box

    return ui->prenom->text();
}

QString gestion_malek::id2() const { //line edit

    return ui->id2->text();
}

QString gestion_malek::nom() const { //line edit

    return ui->nom->text();
}

//remplissage des champs du formulaire a partir de la base

void gestion_malek::fill_form2(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from SPONSOR where ID= :id");
    query.bindValue(":id", selected);
    query.exec();
    while(query.next()){
  ui->id2->setText(query.value(0).toString()); //line edit
   ui->nom->setText(query.value(1).toString()); //line edit
   ui->prenom->setText(query.value(2).toString()); //line edit

    }

}


//************************ crud

//ajout
void gestion_malek::on_actionadd_sponsor_clicked()
{

      //recuperation des donnees
        QString s1=id2();
        QString s2=nom();
        QString s3=prenom();


        //ajout
        sponsor mc(s1,s2,s3);
        mc.ajouter();

        //refresh du tableau (affichage)
          show_sponsor();

          //fill sponsor combobox
          get_sponsor();

          clear_fields();
}

//selection
void gestion_malek::on_table_sponsor_clicked(const QModelIndex &index)
{
    selected_sponsor=ui->table_sponsor->model()->data(index).toString();
}

//modification
void gestion_malek::on_table_sponsor_doubleClicked(const QModelIndex &index)
{

  fill_form2(selected_sponsor);

}

void gestion_malek::on_actionedit_sponsor_clicked()
{
    //recuperation des donnees
      QString s2=nom();
      QString s3=prenom();


      //mofication
      sponsor mc(selected_sponsor,s2,s3);
      mc.modifier(selected_sponsor);

      //refresh du tableau (affichage)
        show_sponsor();

        clear_fields();
}

//suppression
void gestion_malek::on_actiondelete_sponsor_clicked()
{
    sponsor mc;
  mc.supprimer(selected_sponsor);

 //refresh du tableau (affichage)
   show_sponsor();

   //fill sponsor combobox
   get_sponsor();
}

//affichage
void gestion_malek::show_sponsor()
{
    //creation model (masque du tableau) : permet recherche et tri
        proxy_sponsor = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy_sponsor->setSourceModel(tmp_sponsor.afficher());

     //pour la recherche
        proxy_sponsor->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)

        //remplissage tableau avec le masque
        ui->table_sponsor->setModel(proxy_sponsor);
}

//************************ metiers


//recherche dynamique
void gestion_malek::on_sponsor_sel_col_currentIndexChanged(const QString &arg1)
{
    sel_col_sponsor=ui->sponsor_sel_col->currentIndex()-1;
    proxy_sponsor->setFilterKeyColumn(sel_col_sponsor); // chercher dans tout le tableau (-1) ou donner le numero de la colone
}
void gestion_malek::on_rech_sponsor_textChanged(const QString &arg1)
{
    proxy_sponsor->setFilterFixedString(arg1);
}

//mailing
void  gestion_malek::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   gestion_malek::sendMail()
{
    Smtp* smtp = new Smtp("malek.benkhedher@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("malek.benkhedher@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("malek.benkhedher@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   gestion_malek::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


/*********************************** publicite ****************************/


//get form content
QString gestion_malek::type() const { //combo box

    return ui->type->currentText();
}

double gestion_malek::cout() const{ //float

    return ui->cout->value();
}


QString gestion_malek::sponsors() const { //combo box

    return ui->sponsor->currentText();
}

QString gestion_malek::id() const { //line edit

    return ui->id->text();
}

//remplissage des champs du formulaire a partir de la base

void gestion_malek::fill_form(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from PUBLICITE where ID= :id");
    query.bindValue(":id", selected);
    query.exec();
    while(query.next()){
  ui->id->setText(query.value(0).toString()); //line edit
   ui->type->setCurrentText(query.value(1).toString()); //combobox
   ui->cout->setValue(query.value(2).toReal()); // reel
   ui->sponsor->setCurrentText(query.value(3).toString()); //combobox

    }

}

//remplissage du combobox des journaliste a partir de la base
void gestion_malek::get_sponsor(){
    QSqlQuery query;
    QSqlQueryModel * modal=new QSqlQueryModel();
    query.prepare("select ID from SPONSOR");
    query.exec();
    modal->setQuery(query);
    ui->sponsor->setModel(modal);


}


//************************ crud

//ajout

void gestion_malek::on_actionadd_publicite_clicked()
{


      //recuperation des donnees
        QString s1=id();
        QString s2=type();
        QString s3=sponsors();
        double x=cout();


        //ajout
        publicite mc(s1,s2,x,s3);
        mc.ajouter();

        //refresh du tableau (affichage)
          show_publicite();

          clear_fields();
}

//selection
void gestion_malek::on_table_publicite_clicked(const QModelIndex &index)
{
    selected_publicite=ui->table_publicite->model()->data(index).toString();
}

//modification
void gestion_malek::on_table_publicite_doubleClicked(const QModelIndex &index)
{

  fill_form(selected_publicite);
}

void gestion_malek::on_actionedit_publicite_clicked()
{
    //recuperation des donnees
    QString s2=type();
    QString s3=sponsors();
    double x=cout();


      //mofication
      publicite mc(selected_publicite,s2,x,s3);
      mc.modifier(selected_publicite);

      //refresh du tableau (affichage)
        show_publicite();

        clear_fields();
}



//suppression
void gestion_malek::on_actiondelete_publicite_clicked()
{
    publicite mc;
  mc.supprimer(selected_publicite);

 //refresh du tableau (affichage)
   show_publicite();
}

//affichage
void gestion_malek::show_publicite()
{
    //creation model (masque du tableau) : permet recherche et tri
        proxy_publicite = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy_publicite->setSourceModel(tmp_publicite.afficher());

     //pour la recherche
        proxy_publicite->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)

        //remplissage tableau avec le masque
        ui->table_publicite->setModel(proxy_publicite);
}

//************************ metiers

//recherche dynamique
void gestion_malek::on_publicite_sel_col_currentIndexChanged(const QString &arg1)
{
    sel_col_publicite=ui->publicite_sel_col->currentIndex()-1;
    proxy_publicite->setFilterKeyColumn(sel_col_publicite); // chercher dans tout le tableau (-1) ou donner le numero de la colone

}
void gestion_malek::on_rech_publicite_textChanged(const QString &arg1)
{
    proxy_publicite->setFilterFixedString(arg1);
}

//stat
void gestion_malek::on_stat_clicked()
{
    s = new stat_publicite();

  s->setWindowTitle("statistique");
  s->choix_pie();
  s->show();

}






void gestion_malek::on_actiondeconnecter_triggered()
{
    close();
        MainWindow *ws;
    ws = new MainWindow();
ws->setWindowTitle("News Agency");
ws->show();
}
