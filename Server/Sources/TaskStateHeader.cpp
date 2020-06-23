#include "TaskStateHeader.h"

TaskStateHeader::TaskStateHeader() {}

TaskStateHeader::TaskStateHeader(STATE state, char* time, unsigned taskId)
{
    m_state = state;
    strcpy(m_time, time);
    m_taskId = taskId;
}

TaskStateHeader::TaskStateHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(TaskStateHeader));
}

TaskStateHeader &TaskStateHeader::setData(STATE state, char* time, unsigned taskId)
{
    m_state = state;
    strcpy(m_time, time);
    m_taskId = taskId;
    return (*this);
}

TaskStateHeader TaskStateHeader::setByteArr(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(TaskStateHeader));
    return (*this);
}

STATE           TaskStateHeader::getState()
{
    return (m_state);
}

char*           TaskStateHeader::getTime()
{
    return (m_time);
}

int             TaskStateHeader::getTaskId()
{
    return (m_taskId);
}
