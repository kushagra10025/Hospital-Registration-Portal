#ifndef EXPORTDBDATA_H
#define EXPORTDBDATA_H

#include "dbconnection.h"

class ExportDBData
{
public:
    ExportDBData(std::shared_ptr<DBConnection> conn);

    void QueryToCSV(QString queryStr,QString headers, QString csvFileName, QString csvFilePath);
private:
    std::shared_ptr<DBConnection> conn;
};

#endif // EXPORTDBDATA_H
