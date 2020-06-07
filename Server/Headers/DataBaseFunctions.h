#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include "ServerFunctions.h"
#include "MainHeader.h"

sqlite3*    connectDB(char* db_path);

static int  callback(void* notUsed, int argc, char** argv, char** azColName);

int         checkLoginPermission(sqlite3* db, int sock_fd, char* login, char* password);

#endif // DATABASEFUNCTIONS_H