#include "equipement.h"
#include <QDebug>
#include <QPrinter>
#include "qpainter.h"
#include <QTextDocument>
equipement::equipement()
{
    nb=0;
    name="";
    dispo="";

}

equipement::equipement(int nb, QString name, QString dispo )
{
    this->nb=nb;
    this->name=name;
    this->dispo=dispo;
 }

void equipement::printPDF(QTableView* table)
{
    QPixmap pix(table->size());
      QPainter painter(&pix);
      table->render(&painter);
      painter.end();
      QPrinter printer(QPrinter::HighResolution);
      printer.setOrientation(QPrinter::Landscape);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName("equipement.pdf"); // will be in build folder

      painter.begin(&printer);
      double xscale = printer.pageRect().width() / double(pix.width());
      double yscale = printer.pageRect().height() / double(pix.height());
      double scale = qMin(xscale, yscale);
      painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                        printer.paperRect().y() + printer.pageRect().height() / 2);
      painter.scale(scale, scale);
      painter.translate(-table->width() / 2, -table->height() / 2);
      painter.drawPixmap(0, 0, pix);

    QTextDocument doc;

    doc.setHtml("");
    doc.drawContents(&painter);

      painter.end();

}
int equipement::get_nb(){return nb;}
QString equipement::get_name(){return name;}
QString equipement::get_dispo(){return dispo;}
bool equipement::add(){
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (NB, NAME, DISPO)"
                  "VALUES(:NB, :NAME, :DISPO )");
    query.bindValue(":NB",nb);
    query.bindValue(":NAME",name);
    query.bindValue(":DISPO",dispo);
    return query.exec();
}

QSqlQueryModel * equipement::show()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT NB, NAME, DISPO FROM equipement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

QSqlQueryModel * equipement::showSearch(QString txt)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT NB, NAME, DISPO FROM equipement  where (NAME LIKE '%"+txt+"%') OR (NB LIKE '%"+txt+"%') OR (DISPO LIKE '%"+txt+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

bool equipement::remove(int nb)
{
QSqlQuery query;
QString toSearch= QString::number(nb);
query.prepare("DELETE FROM EQUIPEMENT WHERE NB = :NB");
query.bindValue(":NB", toSearch);
return    query.exec();
}
QSqlQueryModel * equipement::show_name()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT NB, NAME, DISPO FROM STUDIO ORDER BY name DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}
void equipement::set_nb(int id){this->nb=id;}

QSqlQueryModel * equipement::show_dispo()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT ORDER BY DISPO DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}
QSqlQueryModel * equipement::show_nb()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT NB, NAME, DISPO FROM EQUIPEMENT ORDER BY ID DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}
QSqlQueryModel * equipement::show_one()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT NB, NAME, DISPO FROM EQUIPEMENT ORDER BY ID DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DISPO"));
        return model;
}

