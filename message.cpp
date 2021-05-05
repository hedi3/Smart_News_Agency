#include "message.h"
#include <QSqlQuery>

message::message()
{

}

void message::addMessage(QString __input1, QString __input2)
{
    QSqlQuery query;
    query.prepare("insert into message (nom, message) values (?, ?)");
    query.addBindValue(__input1);
    query.addBindValue(__input2);
    query.exec();

}

void message::showMessages(QPlainTextEdit * p)
{
    QSqlQuery query;
    p->clear();
    query.exec("select nom, message from message order by id");
    while (query.next()) {
        p->insertPlainText(""+query.value(0).toString()+":  "+query.value(1).toString()+" \r");
    }
}


