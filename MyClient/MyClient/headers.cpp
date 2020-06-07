#include "Headers.h"

//=================================================================================
LoginHeader::LoginHeader(char* userName, char* userPassword)
{
    strcpy(m_userName, userName);
    strcpy(m_userPassword, userPassword);
}
//=================================================================================
LoginHeader::LoginHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(this));
}
//=================================================================================
LoginHeader &LoginHeader::setData(char* userName, char* userPassword)
{
    strcpy(m_userName, userName);
    strcpy(m_userPassword, userPassword);
    return (*this);
}
//=================================================================================
char*       LoginHeader::getUserName()
{
    return (m_userName);
}
//=================================================================================
char*       LoginHeader::getUserPassword()
{
    return (m_userPassword);
}
//=================================================================================
