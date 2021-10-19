#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>
#include <QtDebug>
class DBConnection
{
public:
    DBConnection();
    ~DBConnection();
    void conn_open();
    void conn_close();

    bool get_conn_status();
    QSqlDatabase get_myDB();
private:
    bool conn_status;
    QSqlDatabase myDB;
};

#endif // DBCONNECTION_H
