#include "filesystemsinfo.h"
#include "structures.h"
FileSystemsInfo::FileSystemsInfo()
{
}

FileSystemsInfo::~FileSystemsInfo()
{
}

void FileSystemsInfo :: setSystemInfoList()
{
    file = setmntent(MTAB, "r");
    while(mountFileSystem = getmntent(file))
    {
        if(strstr(mountFileSystem->mnt_fsname, SUB_STRING))
            systems.push_back(setParams(mountFileSystem));
    }
    endmntent(file);
    return;
}

struct fileSystem FileSystemsInfo :: setParams(struct mntent *system)
{
    struct fileSystem info;
    info.fsname = system->mnt_fsname;
    info.dir = system->mnt_dir;
    info.type = system->mnt_type;
    return info;
}

QList<struct fileSystem> FileSystemsInfo :: getSystemInfoList()
{
    return systems;
}
