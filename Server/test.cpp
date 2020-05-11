#include "MainHeader.h"
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

//=================================================================================
string bytes(const char *buf, int size)
{
    string message;
    for (int i = 0; i < size; i++)
    {
        message += to_string((int)buf[i]) + " ";
        if ((i + 1) % 4 == 0)
            message += "| ";
    }
    return (message);
}
//=================================================================================
char* mainHeader_to_bytes(MainHeader mainHeader, char* byteArr)
{
    for (int i = 0; i < 12; i++)
        byteArr[i] = ((char*)&mainHeader)[i];
    byteArr[12] = '\0';
    return (byteArr);
}
//=================================================================================
MainHeader bytes_to_mainHeader(char* byteArr, MainHeader& mainHeader)
{
    for (int i = 0; i < 12; i++)
        ((char*)&mainHeader)[i] = byteArr[i];
    return (mainHeader);
}
//=================================================================================
int main()
{
    MainHeader mh(24365, 32465, OTHER);
    // MainHeader mh2;
    char      copy[13];

    cout << mh.getMsgSize() << " " << mh.getCount() << " " << mh.getType() << endl;

    cout << "Msg:  " << bytes(mh.toBytes(copy), 16) << endl;
    cout << "Copy: " << bytes(mainHeader_to_bytes(mh, copy), 16) << endl;

    MainHeader mh2(copy);
    cout << mh2.getMsgSize() << " " << mh2.getCount() << " "  << mh2.getType() << endl;


    return (0);
}