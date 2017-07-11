#ifndef GENERALFUNCTION_H
#define GENERALFUNCTION_H

#include <QObject>

class GeneralFunction : public QObject
{
    Q_OBJECT
public:
    explicit GeneralFunction(QObject *parent = 0);

    static QStringList getMp3FileList(const QString &path);

    static QString getNameFromPath(const QString &path);

    static bool pathDirHasMp3File(const QString &path, const QString &fileName);

signals:

public slots:
};

#endif // GENERALFUNCTION_H
