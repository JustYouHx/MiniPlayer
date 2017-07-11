#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "configfile.h"
#include "generalfunction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_last_clicked();

    void on_pushButton_pauseon_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_import_clicked();

    void on_pushButton_volume_clicked();

    void slot_tableWidget_doubleClick();

    void slot_slider_volumeChanged(int value);

    void slot_slider_positionChanged(int position);

    void slot_mediaPlayer_positionChanged(qint64 position);

    void slot_mediaPlayer_durationChanged(qint64 duration);

private:
    Ui::MainWindow *ui;

    void getInfoFromConfig();

    void setInfoToConfig();

    void update_mediaPlayer();

    void view_tableList();

    void view_music();

    void view_volume();

    QMediaPlayer m_mediaPlayer;
    QMediaPlaylist m_mediaPlayList;
    qint64 m_iCurrentMusicPositon = 0;
    qint64 m_iCurrentMusicDuration;
    bool m_bCurrentMusicIsMute = false;
    int m_iCurrentMusicVolume = 60;
    QString m_strMusicFilePath;
    QString m_strCurrentMusicFileName;
    int m_iCurrentIndex = 0;
};

#endif // MAINWINDOW_H
