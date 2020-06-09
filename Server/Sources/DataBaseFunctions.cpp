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

static int callback(void* sock_fd, int argc, char** argv, char** azColName)
{
    MainHeader  mainHdr;
    

    std::cout << "!!!!!!!callback()" << std::endl;
    std::cout << argv[0] << " " << argv[1] << " argc = " << argc << std::endl;

    

    if (argc == 2)
        mainHdr.setData(sizeof(MainHeader), 0, PERMISSION_LOGIN);
    // long long sig1 = reinterpret_cast<long long>(sock_fd);
    // int sig = static_cast<int>(sig1);
    cout << "Callback sock_fd = " << *((int*)sock_fd) << endl;
    int sendBytes = sendData(*((int*)sock_fd), mainHdr, NULL, 0);
    *((int*)sock_fd) = -1;
    std::cout << "Bytes sended: " << sendBytes << std::endl;

    return (0);
}

int checkLoginPermission(sqlite3* db, int sock_fd, char* login, char* password)
{
    std::string query;
    int         rc;
    char*       errMsg;
    int         trueSock_fd;

    trueSock_fd = sock_fd;
    std::cout << "checkLoginPermission()" << std::endl;
    query = "SELECT * FROM users_info " \
        "WHERE user_name == '" + std::string(login)
         + "' AND user_password == '" + std::string(password) + "';";
    
    rc = sqlite3_exec(db, query.c_str(), callback, &sock_fd, &errMsg);

    if (sock_fd != -1)
    {
        MainHeader mainHdr(sizeof(MainHeader), 0, BAN_LOGIN);
        int sendBytes = sendData(sock_fd, mainHdr, NULL, 0);
    }
    if (sock_fd == -1)
    {
        //Добавление в онлайн
        std::cout << "INSERT\n";
        query = "INSERT INTO online_users (user_name, sock_num) " \
            "VALUES ('" + std::string(login) + "', " + std::to_string(trueSock_fd) + ");";
        rc = sqlite3_exec(db, query.c_str(), NULL, &sock_fd, &errMsg);
    }

    std::cerr << errMsg << std::endl;
    errno == 2 ? errno = 0 : errno;

    return (rc);
}