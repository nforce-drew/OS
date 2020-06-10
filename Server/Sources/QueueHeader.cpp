#include "QueueHeader.h"

QueueHeader::QueueHeader()
{


}

QueueHeader::QueueHeader(char* userName, unsigned queueNum, char* time)
{
    strcpy(m_userName, userName);
    m_queueNum = queueNum;
    strcpy(m_time, time);
}

QueueHeader::QueueHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(QueueHeader));
}

QueueHeader &QueueHeader::setData(char* userName, unsigned queueNum, char* time)
{
    strcpy(m_userName, userName);
    m_queueNum = queueNum;
    strcpy(m_time, time);
}

QueueHeader QueueHeader::setByteArr(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(QueueHeader));
    return (*this);
}

char*       QueueHeader::getUserName()
{
    return (m_userName);
}

unsigned    QueueHeader::getQueueNum()
{
    
    return (m_queueNum);
}

char*       QueueHeader::getTime()
{
    return (m_time);
}