#ifndef TASKHEADER_H
#define TASKHEADER_H

#include <string.h>
#include <string>

class TaskHeader
{
private:
    unsigned    m_taskId;
    char        m_userName[20];
    unsigned    m_queueNum;
    char        m_time[20];
        
public:
    TaskHeader();
    TaskHeader(unsigned taskId, char* userName, unsigned queueNum, char* time);
    TaskHeader(char* byteArr);
    TaskHeader &setData(unsigned taskId, char* userName, unsigned queueNum, char* time);
    TaskHeader setByteArr(char* byteArr);
    unsigned    getTaskId();
    char*       getUserName();
    unsigned    getQueueNum();
    char*       getTime();
};

#endif // TASKHEADER_H
