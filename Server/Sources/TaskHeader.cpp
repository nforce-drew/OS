#include "TaskHeader.h"

TaskHeader::TaskHeader()
{


}

TaskHeader::TaskHeader(unsigned taskId, char* userName, unsigned queueNum, char* time)
{
    m_taskId = taskId;
    strcpy(m_userName, userName);
    m_queueNum = queueNum;
    strcpy(m_time, time);
}

TaskHeader::TaskHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(TaskHeader));
}

TaskHeader &TaskHeader::setData(unsigned taskId, char* userName, unsigned queueNum, char* time)
{
    m_taskId = taskId;
    strcpy(m_userName, userName);
    m_queueNum = queueNum;
    strcpy(m_time, time);
}

TaskHeader TaskHeader::setByteArr(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(TaskHeader));
    return (*this);
}

unsigned TaskHeader::getTaskId()
{
    return (m_taskId);
}

char*       TaskHeader::getUserName()
{
    return (m_userName);
}

unsigned    TaskHeader::getQueueNum()
{
    
    return (m_queueNum);
}

char*       TaskHeader::getTime()
{
    return (m_time);
}