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
    myDB = QSqlDatabase::addDatabase("QPSQL");
    myDB.setHostName("localhost");
    myDB.setUserName("postgres");
    myDB.setPassword("");
    myDB.setDatabaseName("hhc_main");
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
