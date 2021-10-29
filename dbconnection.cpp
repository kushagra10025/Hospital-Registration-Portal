#include "dbconnection.h"

DBConnection::DBConnection()
{
    conn_open();


}

DBConnection::~DBConnection()
{
    conn_close();
}

void DBConnection::conn_open()
{
//    myDB = QSqlDatabase::addDatabase("QSQLITE");
//    myDB.setDatabaseName("E:/OtherProjects/HHC_DB/hhc_main.sqlite");

    confsett = std::make_shared<ConfigSettings>();
    confsett->AppSettings()->sync();

    confsett->AppSettings()->beginGroup("db_settings");
    QString DBType = confsett->AppSettings()->value("type").toString();
    QString HostName = confsett->AppSettings()->value("host").toString();
    QString UserName = confsett->AppSettings()->value("username").toString();
    QString Password = confsett->AppSettings()->value("password").toString();
    QString DBName = confsett->AppSettings()->value("db").toString();
    confsett->AppSettings()->endGroup();

    myDB = QSqlDatabase::addDatabase(DBType);
    myDB.setHostName(HostName);
    myDB.setUserName(UserName);
    myDB.setPassword(Password);
    myDB.setDatabaseName(DBName);
    if(!myDB.open()){
        conn_status = false;
    }else{
        conn_status = true;
    }
}

void DBConnection::conn_close()
{
    myDB.close();
    myDB.removeDatabase(myDB.databaseName());
}

bool DBConnection::get_conn_status()
{
    return conn_status;
}

QSqlDatabase DBConnection::get_myDB()
{
    return myDB;
}
