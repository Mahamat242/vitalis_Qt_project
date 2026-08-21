#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class databaseManager
{
    public :
        static bool connexion()
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("127.0.0.1");
            db.setPort(3306);
            db.setDatabaseName("vitalis_db");
            db.setUserName("vitalis_user");
            db.setPassword("vitalis_pwd");

            if(!db.open())
            {
                qCritical() << "erreur de connexion à mySql : " << db.lastError().text();
                return false;
            }

            qInfo() << "connexion réussie à mySql";
            return true;
        };
};

#endif // DBMANAGER_H
