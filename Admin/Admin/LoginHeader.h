#ifndef HEADERS_H
#define HEADERS_H

#include <string.h>

class LoginHeader
{
private:
    char m_userName[20];
    char m_userPassword[20];

public:
    LoginHeader();
    LoginHeader(char* userName, char* userPassword);
    LoginHeader(char* byteArr);

    LoginHeader &setData(char* userName, char* userPassword);
    LoginHeader  setByteArr(char* byteArr);
    char*       getUserName();
    char*       getUserPassword();
};

#endif // HEADERS_H
