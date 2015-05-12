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
    //info.RAM = temp;
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
    float ram;

    file = fopen(MEM_INFO, "r");
    fscanf(file, "%*s %f", &ram);
    ram /= DIVIDER;
    info.RAM = ram;
    return;
}

void SystemInfo:: setOSTypeInfo()
{
    char* result = (char*)malloc(sizeof(char) * MAX_SIZE);

    file = fopen(OS_TYPE, "r");
    fscanf(file, "%s", result);
    info.OSType = result;
}

void SystemInfo:: setOSVersionInfo()
{
     char* result = (char*)malloc(sizeof(char) * MAX_SIZE);

    file = fopen(OS_RELEASE, "r");
    fgets(result, MAX_SIZE, file);
    info.OSVersion = result;
}

struct systemInfo SystemInfo:: getSystemInfoStruct()
{
    return info;
}
