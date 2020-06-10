#include <iostream>
#include <string>
#include <ctime>

std::string bytes(const char *buf, int size)
{
    std::string message;
    for (int i = 0; i < size; i++)
    {
        message += std::to_string((int)buf[i]) + " ";
        if ((i + 1) % 4 == 0)
            message += "| ";
    }
    return (message);
}

int main()
{
    // void* vd;
    //     vd = 0;
    // int *i;
    // int a = 12;
    // i = &a;
    // time_t      rawTime;
    // struct tm*  tm_timeInfo;
    // std::string timeStr;

    // time(&rawTime);
    // tm_timeInfo = localtime(&rawTime);

    // timeStr = std::to_string(tm_timeInfo->tm_year) + '-'
    //             + std::to_string(tm_timeInfo->tm_mon) + '-'
    //             + std::to_string(tm_timeInfo->tm_mday) + ' '
    //             + std::to_string(tm_timeInfo->tm_hour) + ':'
    //             + std::to_string(tm_timeInfo->tm_min) + ':'
    //             + std::to_string(tm_timeInfo->tm_sec);
    tm*     timeInfo;
    time_t  seconds;
    char timeStr[20];
    char format[18];

    seconds = time(NULL);
    timeInfo = localtime(&seconds);
    format = (char*)"%Y-%m-%d %H:%M:%S";
    strftime(timeStr, 20, format, timeInfo);
    std::cout<<"Current Datetime: "<<timeStr<<std::endl;

    // tm_timeInfo->tm_hour;

    // std::string timeInfo = asctime(tm_timeInfo);
// YYYY-MM-DD HH:MM:SS.SSS
    std::cout << timeStr << std::endl;
    // std::cout << tm_timeInfo->tm_ << std::endl;

    



    // vd = i;
    // int x = 10;
    // void *pointer = &x;


    // int y = *((int *) pointer);
    // std::cout << y << std::endl;

    // std::cout << bytes((char*)vd, sizeof(void*)) << std::endl;

    return (0);
}