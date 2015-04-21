#include "systeminfo.h"

SystemInfo::SystemInfo()
{

}

SystemInfo::~SystemInfo()
{

}

void SystemInfo:: setStructInfo()
{
    char* temp;
  //  temp = setProcInfo();
    info.proc = temp;

  //  temp = setRAMInfo();
    info.RAM = temp;
}

void SystemInfo:: setProcInfo()
{
    char temp[MAX_SIZE];
    char *result;

    file = fopen(CPU_INFO, "r");
    while(fgets(temp, MAX_SIZE, file))
        if(strstr(temp, MODEL_NAME))
        {
            result = strchr(temp, ':');
            info.proc  = result+2;
            break;
        }
    fclose(file);
    return;
}

void SystemInfo:: setRAMInfo()
{
    char *result;
    char temp[MAX_SIZE];
    char *values = "1234567890";

    file = fopen(MEM_INFO, "r");
    fgets(temp, MAX_SIZE, file);
    result = strpbrk(temp, values);
    info.RAM = result;
    return;
}

void SystemInfo:: setOSTypeInfo()
{
    char result[MAX_SIZE];

    file = fopen(OS_TYPE, "r");
    fgets(result, MAX_SIZE, file);
    info.OSType = result;
}

void SystemInfo:: setOSVersionInfo()
{
    char result[MAX_SIZE];

    file = fopen(OS_RELEASE, "r");
    fgets(result, MAX_SIZE, file);
    info.OSVersion = result;
}

struct systemInfo SystemInfo:: getSystemInfoStruct()
{
    return info;
}
