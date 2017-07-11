#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QObject>

#define CONFIG_SEPARATOR                ";"

#define CONFIG_SECTION_UI               "UI"
#define CONFIG_KEY_WINDOWPOSX           "windowPosX"
#define CONFIG_KEY_WINDOWPOSY           "windowPosY"
#define CONFIG_SECTION_CONFIG           "CONFIG"
#define CONFIG_KEY_MUSICFILEPATH        "musicFilePath"
#define CONFIG_KEY_MUSICFILENAME        "musicFileName"
#define CONFIG_KEY_MUSICPOSITION        "musicPosition"
#define CONFIG_KEY_MUSICDURATION        "musicDuration"
#define CONFIG_KEY_MUSICISMUTE          "musicIsMute"
#define CONFIG_KEY_MUSICVOLUME          "musicVolume"

class ConfigFile : public QObject
{
    Q_OBJECT
public:
    explicit ConfigFile(QObject *parent = 0);

    static QString getConfigFilePath();

    static void setWindowPos(QPoint pos);

    static void getWindowPos(QPoint *pos);

    static void setMusicFilePath(QString filePaths);

    static void getMusicFilePath(QString *filePaths);

    static void setMusicFileName(QString fileName);

    static void getMusicFileName(QString *fileName);

    static void setMusicPosition(qint64 position);

    static void getMusicPosition(qint64 *position);

    static void setMusicDuration(qint64 duration);

    static void getMusicDuration(qint64 *position);

    static void setMusicIsMute(bool isMute);

    static void getMusicIsMute(bool *isMute);

    static void setMusicVolume(int volume);

    static void getMusicVolume(int *volume);


signals:

public slots:
};

#endif // CONFIGFILE_H
