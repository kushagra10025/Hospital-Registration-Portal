#include "exportdbdata.h"

ExportDBData::ExportDBData(std::shared_ptr<DBConnection> conn)
{
    this->conn = conn;
}

void ExportDBData::QueryToCSV(QString queryStr, QString headers, QString csvFileName, QString csvFilePath)
{
    QSqlQuery query(conn->get_myDB());
    query.prepare(queryStr);

    QString csvSaveFilePath = "";
    csvSaveFilePath.append(csvFilePath);
    csvSaveFilePath.append(csvFileName);

    QFile csvFile(csvSaveFilePath);
    if(!csvFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Failed to open CSV File!";
        return;
    }
    if(!query.exec()){
        qDebug() << "Failed to run Query";
        return;
    }

    QTextStream outStream(&csvFile);
    outStream.setEncoding(QStringConverter::Utf8);

//    outStream << "sep=;\n";
    outStream << headers;
    outStream << '\n';

    while(query.next()){
        const QSqlRecord record = query.record();
        for(int i = 0,recCount = record.count(); i < recCount; i++){
            if(i>0)
                outStream << ';';
            outStream << record.value(i).toString();
        }
        outStream << '\n';
    }
}
