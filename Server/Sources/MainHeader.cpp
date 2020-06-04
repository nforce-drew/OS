#include "MainHeader.h"

MainHeader::MainHeader(){}

MainHeader::MainHeader(unsigned msgSize, unsigned count, TYPE type)
{
    this->msgSize = msgSize;
    this->count   = count;
    this->type    = type;
}

MainHeader::MainHeader(char* byteArr)
{
    for (int i = 0; i < 12; i++)
        ((char*)this)[i] = byteArr[i];
}

MainHeader MainHeader::setByteArr(char* byteArr)
{
    for (int i = 0; i < sizeof(*this); i++)
        ((char*)this)[i] = byteArr[i];
    return (*this);
}

MainHeader MainHeader::setData(unsigned msgSize, unsigned count, TYPE type)
{
    this->msgSize = msgSize;
    this->count   = count;
    this->type    = type;
    return (*this);
}

unsigned MainHeader::getMsgSize()
{
    return (msgSize);
}

unsigned MainHeader::getCount()
{
    return (count);
}

TYPE MainHeader::getType()
{
    return (type);
}

char* MainHeader::toBytes(char* byteArr)
{

    for (int i = 0; i < 12; i++)
        byteArr[i] = ((char*)this)[i];
    byteArr[12] = '\0';
    return (byteArr);
}