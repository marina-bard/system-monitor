#ifndef FILESYSTEMS_H
#define FILESYSTEMS_H

#include <stdio.h>
#include <mntent.h>
#include <string.h>
#include <dirent.h>
#include <QList>
#include <QListIterator>
#include <QString>
//#include <filesystemstruct.h>


#define MTAB   "/etc/mtab"
//#define FILE_NAME   "/proc/mounts"
#define SUB_STRING  "/dev/sd"

class FileSystemsInfo
{
private:
    FILE *file;
    struct mntent *mountFileSystem;
    QList<struct fileSystem> systems;
public:
    FileSystemsInfo();
    ~FileSystemsInfo();

    void setSystemInfoList();
    struct fileSystem setParams(struct mntent*);
    QList<struct fileSystem> getSystemInfoList();
};

#endif // FILESYSTEMS_H
