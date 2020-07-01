#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <string.h>

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
    RECONNECT,
    TASKS_INFO,
    GET_SOLUTION,
    CANCEL_TASK,
    SUCCESS_RECIEVE,
    SIGN_UP,
    SUCCESS_SIGN_UP,
    LOGIN_ALREADY_EXISTS,
    USERS_INFO,
    DELETE_USER,
    ADD_NEW_USER,
    CHANGE_PASSWORD,
    SEND_BIN,
    BINS_LIST,
    OTHER
};
//=================================================================================
class MainHeader
{
private:
    unsigned    msgSize;
    unsigned    count;
    TYPE        type;
    int         info;

public:
    MainHeader();
    MainHeader(unsigned msgSize, unsigned count, TYPE type, int info);
    MainHeader(char* byteArr);

public:
    MainHeader  setByteArr(char* byteArr);
    MainHeader  setData(unsigned msgSize, unsigned count, TYPE type, int info);
    unsigned    getMsgSize();
    unsigned    getCount();
    TYPE        getType();
    int         getInfo();
};
//=================================================================================

#endif // MAINHEADER_H
