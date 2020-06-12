#ifndef MAINHEADER_H
#define MAINHEADER_H

//=================================================================================
enum TYPE
{
    SEND_FILES,
    PERMISSION_LOGIN,
    BAN_LOGIN,
    CHECK_LOGIN,
    QUEUE_LIST,
    ADMIN_LOGGED,
    ONLINE_USERS,
    OTHER
};
//=================================================================================
class MainHeader
{
private:
    unsigned    msgSize;
    unsigned    count;
    TYPE        type;

public:
    MainHeader();
    MainHeader(unsigned msgSize, unsigned count, TYPE type);
    MainHeader(char* byteArr);

public:
    MainHeader  setByteArr(char* byteArr);
    MainHeader  setData(unsigned msgSize, unsigned count, TYPE type);
    unsigned    getMsgSize();
    unsigned    getCount();
    TYPE        getType();
    char*       toBytes(char* byteArr);

};
//=================================================================================

#endif // MAINHEADER_H
