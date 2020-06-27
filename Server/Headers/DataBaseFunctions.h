#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H

#include "ServerFunctions.h"
#include "MainHeader.h"
#include "TaskHeader.h"
#include "TaskStateHeader.h"
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>

#define DB_PATH     "/home/nspace/OS/tasks_solver.db"

sqlite3*        connectDB(char* db_path);
static int      callback(void* notUsed, int argc, char** argv, char** azColName);
int             checkLoginPermission(sqlite3* db, int sock_fd, char* login, char* password);
string          getUserName(int sock_fd);
static int      callback_result(void* data, int argc, char** argv, char** azColName);
string          getUserNameByTaskId(int taskId);
int             createTask(string userName, string time);
void            joinQueue(int taskId, string userName, string time);
static int      callback_sendQueue(void* data, int argc, char** argv, char** azColName);
int             sendQueue(int admin_fd);
void            clearQueue();
void            fillQueue(list<TaskHeader>* queue);
static int      callback_getOnlineUsers(void* data, int argc, char** argv, char** azColName);
list<string>*   getOnlineUsers(list<string>* lst);
void            addOnlineUser(int sock_fd, string userName);
void            addTaskPathes(int taskId, list<string> pathes);
int             getFirstTask();
list<string>    getTaskPathes(int taskId);
void            setTaskState(int taskId, string state);
list<string>    getSolutionPathes(int taskId, list<string>& files);
void            setSolutionPathes(int taskId, list<string>& files);
int             getSockFd(string userName);
void            cancelQueueTask(int taskId);
void            deleteUser(string userName);

list<LoginHeader>       getUsersInfo(list<LoginHeader> &usersInfoList);
list<TaskStateHeader>   &getTasksInfo(string userName, list<TaskStateHeader>& tasksList);
// bool            isSolverFree();
#endif // DATABASEFUNCTIONS_H