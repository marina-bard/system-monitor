#include "filesystemsmonitoring.h"
#include <unistd.h>

FileSystemsMonitoring::FileSystemsMonitoring(QObject *parent) : QObject(parent)
{

}

FileSystemsMonitoring::~FileSystemsMonitoring()
{
    emit stopThread();
}

void FileSystemsMonitoring::monitor()
{
    FileSystemsInfo *fs = new FileSystemsInfo;
    QList<struct fileSystem> fsInfoOld;

    fs->setSystemInfoList();
    fsInfoOld = fs->getSystemInfoList();

    while(true)
    {
        FileSystemsInfo *fs = new FileSystemsInfo;
        QList<struct fileSystem> fsInfo;
        struct fileSystem info, oldInfo;

        fs->setSystemInfoList();
        fsInfo = fs->getSystemInfoList();

        QListIterator<struct fileSystem> iter(fsInfo), iterOld(fsInfoOld);
        iter.toFront();

        if(fsInfo.size() > fsInfoOld.size())
        {
            while(iter.hasNext())
            {
                bool noMatches = true;
                info = iter.next();
                iterOld.toFront();
                while(iterOld.hasNext())
                {
                    oldInfo = iterOld.next();
                    if(info.dir == oldInfo.dir)
                    {
                        noMatches = false;
                        break;
                    }
                }

                if(noMatches)
                {
                    struct fileSystem temp;
                    temp = info;
                    emit systemsChanged(&info, false);
                }
            }
        }
        else if(fsInfo.size() < fsInfoOld.size())
        {
            while(iterOld.hasNext())
            {
                bool noMatches = true;
                info = iterOld.next();
                iter.toFront();
                while(iter.hasNext())
                {
                    oldInfo = iter.next();
                    if(info.dir == oldInfo.dir)
                    {
                        noMatches = false;
                        break;
                    }
                }

                if(noMatches)
                {
                    struct fileSystem temp;
                    temp = info;
                    emit systemsChanged(&temp, true);
                }
            }
        }
        fsInfoOld = fsInfo;
        sleep(1);
    }
}
