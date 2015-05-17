#ifndef FILESYSTEMSMONITORING_H
#define FILESYSTEMSMONITORING_H

#include <QObject>
#include "filesystemsinfo.h"

class FileSystemsMonitoring : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemsMonitoring(QObject *parent = 0);
    ~FileSystemsMonitoring();

signals:
    void stopThread();
    void systemsChanged(struct fileSystem *info, bool);

public slots:
    void monitor();
};

#endif // FILESYSTEMSMONITORING_H
