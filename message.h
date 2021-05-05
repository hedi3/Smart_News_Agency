#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QPlainTextEdit>

class message
{
public:
    message();
    void addMessage(QString, QString);
    void showMessages(QPlainTextEdit*);

};

#endif // MESSAGE_H
