#include "generalfunction.h"

#include <QDir>
#include <QDirIterator>

GeneralFunction::GeneralFunction(QObject *parent) : QObject(parent)
{

}

QStringList GeneralFunction::getMp3FileList(const QString &path)
{
    QStringList mp3List;
    QDir dir;
    if (dir.exists(path))
    {
        // 文件类型过滤器
        QStringList filters;
        filters << "*.mp3";
        // 定义迭代器并设置过滤器
        QDirIterator dir_iterator(path, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dir_iterator.hasNext())
        {
            dir_iterator.next();
            mp3List.append(dir_iterator.fileInfo().fileName());
        }
        return mp3List;
    }
    return mp3List;
}

QString GeneralFunction::getNameFromPath(const QString &path)
{
    QString fileName = "";
    QStringList nameList = path.split("/");
    fileName = nameList.at(nameList.count() - 1);
    return fileName;
}

bool GeneralFunction::pathDirHasMp3File(const QString &path, const QString &fileName)
{
    bool pass = false;
    QDir dir;
    if (dir.exists(path))
    {
        // 文件类型过滤器
        QStringList filters;
        filters << "*.mp3";
        // 定义迭代器并设置过滤器
        QDirIterator dir_iterator(path, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dir_iterator.hasNext())
        {
            dir_iterator.next();
            if (dir_iterator.fileInfo().fileName() == fileName)
            {
                return true;
            }
        }
    }
    return pass;
}
