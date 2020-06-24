#ifndef TASKSTATEHEADER_H
#define TASKSTATEHEADER_H

#include <string.h>
#include <string>

//=================================================================================
enum STATE
{
    SOLVING,
    CANCEL,
    DONE,
    IN_QUEUE
};
//=================================================================================

class TaskStateHeader
{
private:
    STATE       m_state;
    char        m_time[20];
    unsigned    m_taskId;
        
public:
    TaskStateHeader();
    TaskStateHeader(STATE state, char* time, unsigned taskId);
    TaskStateHeader(char* byteArr);

    TaskStateHeader &setData(STATE state, char* time, unsigned taskId);
    TaskStateHeader setByteArr(char* byteArr);
    STATE           getState();
    char*           getTime();
    int             getTaskId();

};

#endif // TASKSTATEHEADER_H