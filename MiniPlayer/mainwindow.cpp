#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableWidget>
#include <QtWinExtras>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    getInfoFromConfig();
    view_tableList();
    view_music();
    view_volume();
    update_mediaPlayer();

    connect(ui->tableWidget_musiclist, &QTableWidget::doubleClicked, this, &slot_tableWidget_doubleClick);
    connect(ui->horizontalSlider_volume, &QSlider::valueChanged, this, &slot_slider_volumeChanged);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &slot_slider_positionChanged);
    connect(&m_mediaPlayer, &QMediaPlayer::positionChanged, this, &slot_mediaPlayer_positionChanged);
    connect(&m_mediaPlayer, &QMediaPlayer::durationChanged, this, &slot_mediaPlayer_durationChanged);
}

MainWindow::~MainWindow()
{
    ConfigFile::setMusicPosition(m_iCurrentMusicPositon);
    delete ui;
}


void MainWindow::getInfoFromConfig()
{
    ConfigFile::getMusicFilePath(&m_strMusicFilePath);
    ConfigFile::getMusicFileName(&m_strCurrentMusicFileName);
    ConfigFile::getMusicPosition(&m_iCurrentMusicPositon);
    ConfigFile::getMusicDuration(&m_iCurrentMusicDuration);
    ConfigFile::getMusicIsMute(&m_bCurrentMusicIsMute);
    ConfigFile::getMusicVolume(&m_iCurrentMusicVolume);
}

void MainWindow::setInfoToConfig()
{

}

void MainWindow::update_mediaPlayer()
{
    if (m_strCurrentMusicFileName != "" && GeneralFunction::pathDirHasMp3File(m_strMusicFilePath, m_strCurrentMusicFileName))
    {
//        QString musicPath = m_strMusicFilePath + "/" + m_strCurrentMusicFileName;
//        m_mediaPlayer.setMedia(QUrl::fromLocalFile(musicPath));
        m_mediaPlayList.setCurrentIndex(m_iCurrentIndex);
        m_mediaPlayer.setPlaylist(&m_mediaPlayList);
        m_mediaPlayer.setPosition(m_iCurrentMusicPositon);
    }
    if (m_bCurrentMusicIsMute == true)
    {
        m_mediaPlayer.setVolume(0);
    }
    else
    {
        m_mediaPlayer.setVolume(m_iCurrentMusicVolume);
    }
}

void MainWindow::on_pushButton_last_clicked()
{

}

void MainWindow::on_pushButton_pauseon_clicked()
{
    if (m_mediaPlayer.state() == QMediaPlayer::PlayingState)
    {
        ui->pushButton_pauseon->setIcon(QIcon(":/resource/play.png"));
        ui->pushButton_pauseon->setIconSize(QSize(28,28));
        m_mediaPlayer.pause();
        m_iCurrentMusicPositon =  m_mediaPlayer.position();
        ConfigFile::setMusicPosition(m_iCurrentMusicPositon);
        return;
    }
    else
    {
        ui->pushButton_pauseon->setIcon(QIcon(":/resource/pause.png"));
        ui->pushButton_pauseon->setIconSize(QSize(28,28));
        m_mediaPlayer.setPosition(m_iCurrentMusicPositon);
        m_mediaPlayer.play();
        return;
    }
}

void MainWindow::on_pushButton_next_clicked()
{

}

void MainWindow::on_pushButton_import_clicked()
{
    QString newFilePath = QFileDialog::getExistingDirectory(this, "请选择音乐文件夹", "./");
    m_strMusicFilePath = newFilePath;
    ConfigFile::setMusicFilePath(newFilePath);
    view_tableList();
}

void MainWindow::on_pushButton_volume_clicked()
{
    if (m_bCurrentMusicIsMute == true)
    {
        m_mediaPlayer.setVolume(m_iCurrentMusicVolume);
        ui->pushButton_volume->setIcon(QIcon(":/resource/volume.png"));
        m_bCurrentMusicIsMute = false;
    }
    else
    {
        m_mediaPlayer.setVolume(0);
        ui->pushButton_volume->setIcon(QIcon(":/resource/mute.png"));
        m_bCurrentMusicIsMute = true;
    }
    ConfigFile::setMusicIsMute(m_bCurrentMusicIsMute);
}

void MainWindow::slot_tableWidget_doubleClick()
{
    int row = ui->tableWidget_musiclist->currentRow();
    m_strCurrentMusicFileName = ui->tableWidget_musiclist->item(row, 0)->text();
    ConfigFile::setMusicFileName(m_strCurrentMusicFileName);
    m_iCurrentMusicPositon = 0;
    update_mediaPlayer();
    view_music();
    on_pushButton_pauseon_clicked();
}

void MainWindow::slot_slider_volumeChanged(int value)
{
    m_iCurrentMusicVolume = value;
    ConfigFile::setMusicVolume(value);
    m_mediaPlayer.setVolume(value);
    if (value == 0)
    {
        m_bCurrentMusicIsMute = true;
        ConfigFile::setMusicIsMute(true);
        ui->pushButton_volume->setIcon(QIcon(":/resource/mute.png"));
    }
    else
    {
        ui->pushButton_volume->setIcon(QIcon(":/resource/volume.png"));
    }
    ui->pushButton_volume->setIconSize(QSize(20,20));
}

void MainWindow::slot_slider_positionChanged(int position)
{
    if (qAbs(m_mediaPlayer.position() - position) > 99)
    {
        m_mediaPlayer.setPosition(position);
    }
}

void MainWindow::slot_mediaPlayer_positionChanged(qint64 position)
{
    m_iCurrentMusicPositon = position;
    ui->horizontalSlider->setValue(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->label_time->setText(duration.toString(tr("mm:ss")));
}

void MainWindow::slot_mediaPlayer_durationChanged(qint64 duration)
{
    m_iCurrentMusicDuration = duration;
    ConfigFile::setMusicDuration(duration);
    ui->horizontalSlider->setRange(0, duration);
    ui->horizontalSlider->setEnabled(duration > 0);
    ui->horizontalSlider->setPageStep(duration / 10);
}

void MainWindow::view_tableList()
{
    m_mediaPlayList.clear();

    QStringList musicFiles;
    QStringList columnHeaderName;
    musicFiles = GeneralFunction::getMp3FileList(m_strMusicFilePath);
    if (!musicFiles.empty())
    {
        ui->tableWidget_musiclist->clear();

        ui->tableWidget_musiclist->setColumnCount(1);
        columnHeaderName << "歌曲";
        ui->tableWidget_musiclist->setHorizontalHeaderLabels(columnHeaderName);

        ui->tableWidget_musiclist->setRowCount(musicFiles.count());
        for (int i = 0; i < musicFiles.count(); i++)
        {
            //musicFileName = GeneralFunction::getNameFromPath(musicFiles.at(i));
            QTableWidgetItem *item = new QTableWidgetItem(musicFiles.at(i));
            ui->tableWidget_musiclist->setItem(i, 0, item);
            if (musicFiles.at(i) == m_strCurrentMusicFileName)
            {
                m_iCurrentIndex = i;
            }
            m_mediaPlayList.addMedia(QUrl(m_strMusicFilePath + "/" + musicFiles.at(i)));
        }

        ui->tableWidget_musiclist->resizeColumnToContents(0);
    }
}

void MainWindow::view_music()
{
    if (m_strCurrentMusicFileName != "")
    {
        ui->label_music->setText(m_strCurrentMusicFileName);
    }
    ui->horizontalSlider->setRange(0, m_iCurrentMusicDuration);
    ui->horizontalSlider->setValue(m_iCurrentMusicPositon);
    QTime duration(0, m_iCurrentMusicPositon / 60000, qRound((m_iCurrentMusicPositon % 60000) / 1000.0));
    ui->label_time->setText(duration.toString(tr("mm:ss")));
}

void MainWindow::view_volume()
{
    ui->horizontalSlider_volume->setRange(0, 100);
    ui->horizontalSlider_volume->setValue(m_iCurrentMusicVolume);
    if (m_iCurrentMusicVolume == 0 || m_bCurrentMusicIsMute == true)
    {
        ui->pushButton_volume->setIcon(QIcon(":/resource/mute.png"));
    }
    else
    {
        ui->pushButton_volume->setIcon(QIcon(":/resource/volume.png"));
    }
    ui->pushButton_volume->setIconSize(QSize(20,20));
}
