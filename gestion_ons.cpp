#include "gestion_ons.h"
#include "ui_gestion_ons.h"
#include "notifications.h"
#include "mainwindow.h"
#include <QDialog>
#include "serverwindow.h"
#include "ui_serverwindow.h"

gestion_ons::gestion_ons(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_ons)
{
    ui->setupUi(this);

    get_journaliste();

    //affichage contenu base
    show_tables();
}

gestion_ons::~gestion_ons()
{
    delete ui;
}


void gestion_ons::show_tables()
{
    show_journaliste();
    show_article();
}

/*********************************** journaliste ****************************/


//**********************************ADD

//get form content
QString gestion_ons::specialite() const { //combo box

    return ui->specialite->currentText();
}

QString gestion_ons::id() const { //line edit

    return ui->id->text();
}

QString gestion_ons::nom() const { //line edit

    return ui->nom->text();
}

//remplissage des champs du formulaire a partir de la base

void gestion_ons::fill_form(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from JOURNALISTES where ID= :id");
    query.bindValue(":id", selected);
    query.exec();
    while(query.next()){
  ui->id->setText(query.value(0).toString()); //line edit
   ui->nom->setText(query.value(1).toString()); //line edit
   ui->specialite->setCurrentText(query.value(2).toString()); //combobox
   ui->nb_articles->setText(query.value(3).toString()); //line edit

    }

}








//************************ crud

//ajout
void gestion_ons::on_actionadd_journaliste_clicked()
{


    Notifications *n = new Notifications();
    n->notifications_modifiercadeau();

      //recuperation des donnees
        QString s1=id();
        QString s2=nom();
        QString s3=specialite();


        //ajout
        journaliste mc(s1,s2,s3);
        mc.ajouter();

        get_journaliste();

        //refresh du tableau (affichage)
          show_journaliste();
}

//selection
void gestion_ons::on_table_journaliste_clicked(const QModelIndex &index)
{
    selected_journaliste=ui->table_journaliste->model()->data(index).toString();
}

//modification
void gestion_ons::on_table_journaliste_doubleClicked(const QModelIndex &index)
{

  fill_form(selected_journaliste);




}

//suppression
void gestion_ons::on_actiondelete_journaliste_clicked()
{
    journaliste mc;
  mc.supprimer(selected_journaliste);

  get_journaliste();


 //refresh du tableau (affichage)
   show_journaliste();
}

//affichage
void gestion_ons::show_journaliste()
{
    //creation model (masque du tableau) : permet recherche et tri
        proxy_journaliste = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy_journaliste->setSourceModel(tmp_journaliste.afficher());

     //pour la recherche
        proxy_journaliste->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)

        //remplissage tableau avec le masque
        ui->table_journaliste->setModel(proxy_journaliste);
}

//************************ metiers


//recherche dynamique
void gestion_ons::on_journaliste_sel_col_currentIndexChanged(const QString &arg1)
{
    sel_col_journaliste=ui->journaliste_sel_col->currentIndex()-1;
    proxy_journaliste->setFilterKeyColumn(sel_col_journaliste); // chercher dans tout le tableau (-1) ou donner le numero de la colone
}
void gestion_ons::on_rech_journaliste_textChanged(const QString &arg1)
{
    proxy_journaliste->setFilterFixedString(arg1);
}

//export excel
void gestion_ons::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->table_journaliste);

    //colums to export
    obj.addField(0, "ID", "char(20)");
    obj.addField(1, "Nom", "char(20)");
    obj.addField(2, "Specialite", "char(20)");
    obj.addField(3, "Nb_Articles", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

//imprimer
void gestion_ons::on_pushButton_4_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->table_journaliste->model()->rowCount();
    const int columnCount =ui->table_journaliste->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"


        "<meta Content=\"Text gdghdhdgdg/html; charset=Windows-1251\">\n"

        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
            "<h1>  Tableau Journaliste  </h1>"
        "<table border=1 cellspacing=0 cellpadding=2>\n";





    // headers
    out << "<thead><tr bgcolor=#FB0404>";
    for (int column = 0; column < columnCount; column++)
      //  if (ui->table_journaliste->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->table_journaliste->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table


    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->table_journaliste->isColumnHidden(column)) {
                QString data = ui->table_journaliste->model()->data(ui->table_journaliste->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}


/*********************************** article ****************************/



//get form content
QString gestion_ons::type2() const { //combo box

    return ui->type2->currentText();
}

QString gestion_ons::journaliste2() const { //combo box

    return ui->journaliste2->currentText();
}

QString gestion_ons::id2() const { //line edit

    return ui->id2->text();
}

//remplissage des champs du formulaire a partir de la base

void gestion_ons::fill_form2(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from ARTICLES where ID= :id");
    query.bindValue(":id", selected);
    query.exec();
    while(query.next()){
  ui->id2->setText(query.value(0).toString()); //line edit
   ui->type2->setCurrentText(query.value(1).toString()); //combobox
   ui->journaliste2->setCurrentText(query.value(2).toString()); //combobox

    }

}

//remplissage du combobox des journaliste a partir de la base
void gestion_ons::get_journaliste(){
    QSqlQuery query;
    QSqlQueryModel * modal=new QSqlQueryModel();
    query.prepare("select NOM from JOURNALISTES");
    query.exec();
    modal->setQuery(query);
    ui->journaliste2->setModel(modal);


}






//************************ crud

//ajout

void gestion_ons::on_actionadd_article_clicked()
{

    Notifications *n = new Notifications();
    n->notifications_modifierparticipation();
      //recuperation des donnees
        QString s1=id2();
        QString s2=type2();
        QString s3=journaliste2();


        //ajout
        article mc(s1,s2,s3);
        mc.ajouter();
        mc.count_articles();

        //refresh du tableau (affichage)
          show_tables();
}

//selection
void gestion_ons::on_table_article_clicked(const QModelIndex &index)
{
    selected_article=ui->table_article->model()->data(index).toString();
}

//modification
void gestion_ons::on_table_article_doubleClicked(const QModelIndex &index)
{

  fill_form2(selected_article);



}

//suppression
void gestion_ons::on_actiondelete_article_clicked()
{
    article mc;
  mc.supprimer(selected_article);
  mc.count_articles();

 //refresh du tableau (affichage)
   show_tables();
}

//affichage
void gestion_ons::show_article()
{
    //creation model (masque du tableau) : permet recherche et tri
        proxy_article = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy_article->setSourceModel(tmp_article.afficher());

     //pour la recherche
        proxy_article->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)

        //remplissage tableau avec le masque
        ui->table_article->setModel(proxy_article);
}

//************************ metiers

//recherche dynamique
void gestion_ons::on_article_sel_col_currentIndexChanged(const QString &arg1)
{
    sel_col_article=ui->article_sel_col->currentIndex()-1;
    proxy_article->setFilterKeyColumn(sel_col_article); // chercher dans tout le tableau (-1) ou donner le numero de la colone

}
void gestion_ons::on_rech_article_textChanged(const QString &arg1)
{
    proxy_article->setFilterFixedString(arg1);
}

//stat
void gestion_ons::on_stat_clicked()
{
    s = new stat_type();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();

}

//imprimer
void gestion_ons::on_pushButton_2_clicked()
{

        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->table_article->model()->rowCount();
        const int columnCount =ui->table_article->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
                 "<h1>tableau ARTICLE</h1>"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
           // if (ui->table_article->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->table_article->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->table_article->isColumnHidden(column)) {
                    QString data = ui->table_article->model()->data(ui->table_article->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }

        delete document;
}

//export excel

void gestion_ons::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->table_article);

    //colums to export
    obj.addField(0, "ID", "char(20)");
    obj.addField(1, "Type", "char(20)");
    obj.addField(2, "Journaliste", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}


void gestion_ons::on_actionedit_journaliste_clicked()
{
    //recuperation des donnees
      QString s2=nom();
      QString s3=specialite();


      //mofication
      journaliste mc(selected_journaliste,s2,s3);
      mc.modifier(selected_journaliste);

      get_journaliste();

      //refresh du tableau (affichage)
        show_journaliste();
}



void gestion_ons::on_actionedit_article_clicked()
{
    //recuperation des donnees
      QString s2=type2();
      QString s3=journaliste2();


      //mofication
      article mc(selected_article,s2,s3);
      mc.modifier(selected_article);
      mc.count_articles();

      //refresh du tableau (affichage)
        show_tables();
}

void gestion_ons::on_actiondeconnecter_triggered()
{
    close();
        MainWindow *ws;
    ws = new MainWindow();
ws->setWindowTitle("News Agency");
ws->show();
}

void gestion_ons::on_pushButton_5_clicked()
{
   ServerWindow s;
    s.exec();
}
