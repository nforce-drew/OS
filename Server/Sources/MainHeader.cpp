#include "MainHeader.h"

MainHeader::MainHeader(){}

MainHeader::MainHeader(unsigned msgSize, unsigned count, TYPE type, int info)
{
    this->msgSize = msgSize;
    this->count   = count;
    this->type    = type;
    this->info    = info;
}

MainHeader::MainHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(MainHeader));
}

MainHeader MainHeader::setByteArr(char* byteArr)
{
    for (int i = 0; i < sizeof(*this); i++)
        ((char*)this)[i] = byteArr[i];
    return (*this);
}

MainHeader MainHeader::setData(unsigned msgSize, unsigned count, TYPE type, int info)
{
    this->msgSize = msgSize;
    this->count   = count;
    this->type    = type;
    this->info    = info;
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

int MainHeader::getInfo()
{
    return (info);
}