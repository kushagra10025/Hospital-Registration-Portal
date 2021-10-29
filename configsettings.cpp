#include "configsettings.h"

#include <QFile>
#include <QUrl>

ConfigSettings::ConfigSettings()
{
    if(QFile("config.ini").exists())
    {
        settings = std::make_shared<QSettings>("config.ini" ,QSettings::IniFormat);
    }
    else
    {
        qDebug() << "not exist";
    }

    // TODO : Call for the first time only
    // Alternative : Ship the config.ini file with deployment
    // SetDeafultValues();

    settings->sync();
}

void ConfigSettings::SetDeafultValues()
{
    settings->beginGroup("db_settings");
    settings->setValue("type","QPSQL");
    settings->setValue("host","localhost");
    settings->setValue("username","postgres");
    settings->setValue("password","");
    settings->setValue("db","hhc_main");
    settings->endGroup();

    settings->beginGroup("paths");
    settings->setValue("csv_export","E:/OtherProjects/hhc_files/");
    settings->endGroup();
}

std::shared_ptr<QSettings> &ConfigSettings::AppSettings()
{
    return settings;
}
