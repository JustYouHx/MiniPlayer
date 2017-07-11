#include "configfile.h"

#include <QDir>
#include <QPoint>
#include <QCoreApplication>
#include <QSettings>

ConfigFile::ConfigFile(QObject *parent) : QObject(parent)
{

}

QString ConfigFile::getConfigFilePath()
{
    QDir temp = QCoreApplication::applicationDirPath();
    QString exePath = temp.path();
    QString configFilePath = exePath + "/config/config.ini";
    QFile cfgFile(configFilePath);
    if (!cfgFile.exists())
    {
        // 若不存在配置文件，则新建文件
        cfgFile.open(QIODevice::WriteOnly);
        cfgFile.close();
    }
    return configFilePath;
}

void ConfigFile::setWindowPos(QPoint pos)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString keyX = QString("%1/%2").arg(CONFIG_SECTION_UI).arg(CONFIG_KEY_WINDOWPOSX);
    QString keyY = QString("%1/%2").arg(CONFIG_SECTION_UI).arg(CONFIG_KEY_WINDOWPOSY);
    cfgSetting.setValue(keyX, pos.x());
    cfgSetting.setValue(keyY, pos.y());
}

void ConfigFile::getWindowPos(QPoint *pos)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString valueX = cfgSetting.value(CONFIG_KEY_WINDOWPOSX).toString();
    QString valueY = cfgSetting.value(CONFIG_KEY_WINDOWPOSY).toString();
    pos->setX(valueX.toInt());
    pos->setY(valueY.toInt());
}

void ConfigFile::setMusicFilePath(QString filePaths)
{
    //QString musicFilePath = filePaths.join(CONFIG_SEPARATOR);
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICFILEPATH);
    cfgSetting.setValue(key, filePaths);
}

void ConfigFile::getMusicFilePath(QString *filePaths)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICFILEPATH);
    *filePaths = cfgSetting.value(key).toString();
    //QString musicFilePath = cfgSetting.value(CONFIG_KEY_MUSICFILEPATH).toString();
    //*filePaths = musicFilePath.split(CONFIG_SEPARATOR);
}

void ConfigFile::setMusicFileName(QString fileName)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICFILENAME);
    cfgSetting.setValue(key, fileName);
}

void ConfigFile::getMusicFileName(QString *fileName)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICFILENAME);
    *fileName = cfgSetting.value(key).toString();
}

void ConfigFile::setMusicPosition(qint64 position)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICPOSITION);
    cfgSetting.setValue(key, position);
}

void ConfigFile::getMusicPosition(qint64 *position)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICPOSITION);
    *position = cfgSetting.value(key).toInt();
}

void ConfigFile::setMusicDuration(qint64 duration)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICDURATION);
    cfgSetting.setValue(key, duration);
}

void ConfigFile::getMusicDuration(qint64 *duration)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICDURATION);
    *duration = cfgSetting.value(key).toInt();
}

void ConfigFile::setMusicIsMute(bool isMute)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICISMUTE);
    cfgSetting.setValue(key, isMute);
}

void ConfigFile::getMusicIsMute(bool *isMute)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICISMUTE);
    *isMute = cfgSetting.value(key).toBool();
}

void ConfigFile::setMusicVolume(int volume)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICVOLUME);
    cfgSetting.setValue(key, volume);
}

void ConfigFile::getMusicVolume(int *volume)
{
    QSettings cfgSetting(getConfigFilePath(), QSettings::IniFormat);
    QString key = QString("%1/%2").arg(CONFIG_SECTION_CONFIG).arg(CONFIG_KEY_MUSICVOLUME);
    *volume = cfgSetting.value(key).toInt();
}
