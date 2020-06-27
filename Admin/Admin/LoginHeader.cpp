#include "LoginHeader.h"

//=================================================================================
LoginHeader::LoginHeader() {}
//=================================================================================
LoginHeader::LoginHeader(char* userName, char* userPassword)
{
    strcpy(m_userName, userName);
    strcpy(m_userPassword, userPassword);
}
//=================================================================================
LoginHeader::LoginHeader(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(LoginHeader));
}
//=================================================================================
LoginHeader &LoginHeader::setData(char* userName, char* userPassword)
{
    strcpy(m_userName, userName);
    strcpy(m_userPassword, userPassword);
    return (*this);
}
//=================================================================================
LoginHeader LoginHeader::setByteArr(char* byteArr)
{
    memcpy((char*)this, byteArr, sizeof(LoginHeader));
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
