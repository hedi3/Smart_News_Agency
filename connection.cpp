#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_Projet2a");//inserer le nom de la source de données ODBC
db.setUserName("hedi");//inserer nom de l'utilisateur
db.setPassword("system");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::fermerConnexion()
{
    db.close();}
