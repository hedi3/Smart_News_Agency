#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    ui->plainTextEdit->clear();
    __msg.showMessages(ui->plainTextEdit);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_lineEdit_returnPressed()
{
    __msg.addMessage("<"+type+"> "+nom, ui->lineEdit->text());
    ui->lineEdit->setText("");
    __msg.showMessages(ui->plainTextEdit);
}

void Chat::on_pushButton_clicked()
{
    this->close();
}
