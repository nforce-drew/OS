#ifndef QUEUEHEADER_H
#define QUEUEHEADER_H

#include <string.h>
#include <string>

class QueueHeader
{
private:
    char        m_userName[20];
    unsigned    m_queueNum;
    char        m_time[20];
        
public:
    QueueHeader();
    QueueHeader(char* userName, unsigned queueNum, char* time);
    QueueHeader(char* byteArr);
    QueueHeader &setData(char* userName, unsigned queueNum, char* time);
    QueueHeader setByteArr(char* byteArr);
    char*       getUserName();
    unsigned    getQueueNum();
    char*       getTime();
};

#endif // QUEUEHEADER_H