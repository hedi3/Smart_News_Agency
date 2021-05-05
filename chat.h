#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include "message.h"

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

    message __msg;
    QString nom;
    QString type;

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();


private:
    Ui::Chat *ui;

};

#endif // CHAT_H
