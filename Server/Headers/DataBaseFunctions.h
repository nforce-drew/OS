#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H

#include "ServerFunctions.h"
#include "MainHeader.h"
#include "QueueHeader.h"
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>

#define DB_PATH     "/home/nforce/OS/tasks_solver.db"

sqlite3*        connectDB(char* db_path);
static int      callback(void* notUsed, int argc, char** argv, char** azColName);
int             checkLoginPermission(sqlite3* db, int sock_fd, char* login, char* password);
string          getUserName(int sock_fd);
void            joinQueue(string userName, string time);
static int      callback_sendQueue(void* data, int argc, char** argv, char** azColName);
int             sendQueue(int admin_fd);
void            clearQueue();
void            fillQueue(list<QueueHeader> &queue);
static int      callback_getOnlineUsers(void* data, int argc, char** argv, char** azColName);
list<string>*   getOnlineUsers(list<string>* lst);


#endif // DATABASEFUNCTIONS_H