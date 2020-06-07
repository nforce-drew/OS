#include <sqlite3.h>
#include <iostream>

sqlite3*    connectDB(char* db_path);

static int  callback(void* notUsed, int argc, char** argv, char** azColName);

int         selectData(sqlite3* db, char* query);