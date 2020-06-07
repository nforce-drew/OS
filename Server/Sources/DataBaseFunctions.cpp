#include "DataBaseFunctions.h"

sqlite3* connectDB(char* db_path)
{
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(db_path, &db);
   
    if (rc)
    {
        std::cerr << "Can't open database: " << std::endl
            << sqlite3_errmsg(db);
        return (nullptr);
    }
    else
        std::cout << "Opened database successfully" << std::endl;
    return (db);
}

static int callback(void* notUsed, int argc, char** argv, char** azColName)
{
    std::cout << argv[0] << " " << argv[1];

    return (0);
}

int         selectData(sqlite3* db, char* query)
{
    int rc;

    rc = sqlite3_exec(db, query, callback, NULL, NULL);

    return (rc);
}