#ifndef CONFIGSETTINGS_H
#define CONFIGSETTINGS_H

#include <QSettings>

class ConfigSettings
{
private:
    std::shared_ptr<QSettings> settings;
    void SetDeafultValues();
public:
    ConfigSettings();
    std::shared_ptr<QSettings>& AppSettings();
};

#endif // CONFIGSETTINGS_H
