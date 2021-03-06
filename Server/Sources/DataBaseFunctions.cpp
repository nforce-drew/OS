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
    // else
    //     std::cout << "Opened database successfully" << std::endl;
    return (db);
}

static int callback(void* sock_fd, int argc, char** argv, char** azColName)
{
    MainHeader  mainHdr;

    if (argc == 2)
        mainHdr.setData(sizeof(MainHeader), 0, PERMISSION_LOGIN, 0);
    int sendBytes = sendData(*((int*)sock_fd), mainHdr, NULL, 0);
    *((int*)sock_fd) = -1;
    std::cout << "Bytes sended: " << sendBytes << std::endl;

    return (0);
}

int checkLoginPermission(sqlite3* db, int sock_fd, char* login, char* password)
{
    vector<vector<string>>* res;
    std::string             query;
    MainHeader              mainHdr;
    int                     rc;
    char*                   errMsg;
    void*                   data;

    res = new vector<vector<string>>;
    data = (void*)res;

    query = "SELECT user_name FROM online_users " \
            "WHERE user_name == '" +  std::string(login) + "';";
    // cout << "res.size() = " << res->size() << endl;
    rc = sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
    if (res->size() != 0)
    {
        mainHdr.setData(sizeof(MainHeader), 0, BAN_LOGIN, 0);
        sendData(sock_fd, mainHdr, NULL, 0);
        return (rc);
    }
    res->clear();
    query = "SELECT * FROM users_info " \
        "WHERE user_name == '" + std::string(login)
         + "' AND user_password == '" + std::string(password) + "';";
    
    rc = sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);

    if (res->size() == 0)
        mainHdr.setData(sizeof(MainHeader), 0, BAN_LOGIN, 0);
    else
    {
        mainHdr.setData(sizeof(MainHeader), 0, PERMISSION_LOGIN, 0);
        //Добавление в онлайн
        query = "INSERT INTO online_users (user_name, sock_num) " \
                "VALUES ('" + std::string(login) + "', " + std::to_string(sock_fd) + ");";
        rc = sqlite3_exec(db, query.c_str(), NULL, &sock_fd, &errMsg);
    }
    sendData(sock_fd, mainHdr, NULL, 0);

    std::cerr << errMsg << std::endl;
    errno == 2 ? errno = 0 : errno;

    return (rc);
}

void            addOnlineUser(int sock_fd, string userName)
{
    std::string query;
    sqlite3*    db;
    char*       errMsg;

    query = "INSERT INTO online_users (user_name, sock_num) " \
            "VALUES ('" + std::string(userName) + "', " + std::to_string(sock_fd) + ");";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
}

static int callback_getUserName(void* data, int argc, char** argv, char** azColName)
{
    strcpy((char*)data, argv[0]);
    return (0);
}

string      getUserName(int sock_fd)
{
    string      query;
    void*       data;
    sqlite3*    db;
    char        strData[20];

    strcpy(strData, (char*)&sock_fd);
    data = strData;
    query = "SELECT user_name FROM online_users WHERE sock_num = "
        + std::to_string(sock_fd) + ";";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_getUserName, data, NULL);
    sqlite3_close(db);

    return (string((char*)data));
}

static int callback_result(void* data, int argc, char** argv, char** azColName)
{
    vector<vector<string>>* res;
    vector<string>          row;

    res = (vector<vector<string>>*)data;
    for (int i = 0; i < argc; i++)
        row.push_back(string(argv[i]));
    res->push_back(row);
    return (0);
}

string          getUserNameByTaskId(int taskId)
{
    vector<vector<string>>* res;
    string                  userName;
    string                  query;
    sqlite3*                db;
    void*                   data;
    
    res = new vector<vector<string>>;
    data = (void*)res;
    db = connectDB((char*)DB_PATH);
    query = "SELECT user_name FROM tasks " \
            "WHERE task_id == " + std::to_string(taskId) + ";";
    sqlite3_exec(db, query.c_str(), callback_result, data, NULL);
    sqlite3_close(db);
    userName = (*res)[0][0];
    delete res;
    return (userName);
}

static int callback_createTask(void* data, int argc, char** argv, char** azColName)
{
    strcpy((char*)data, argv[0]);
    return (0);
}

int         createTask(string userName, string time)
{
    sqlite3*    db;
    string      query;
    char        taskId[10];

    query = "INSERT INTO tasks(user_name, time, state) " \
            "VALUES ('" + userName + "', '" + time + "', 'В очереди');";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    query = "SELECT task_id FROM tasks " \
            "WHERE user_name == '" + userName + "' AND time == '" + time + "';";
    sqlite3_exec(db, query.c_str(), callback_createTask, (void*)&taskId, NULL);
    sqlite3_close(db);
    return (atoi(taskId));
}

void        joinQueue(int taskId, string userName, string time)
{
    sqlite3*    db;
    string      query;

    query = "INSERT INTO task_queue(task_id, user_name, queue_num, time) " \
            "VALUES (" + std::to_string(taskId) + ", '" + userName + "', " \
                        "(SELECT CASE " \
                                    "WHEN (SELECT MAX(queue_num) FROM task_queue) > 0 " \
                                    "THEN (SELECT MAX(queue_num) FROM task_queue) + 1 " \
                                    "ELSE 1 " \
                                "END" \
                        "), '" + time + "'" \
                    ");";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

static int callback_sendQueue(void* data, int argc, char** argv, char** azColName)
{
    list<TaskHeader>*  queue;
    TaskHeader         taskHdr;

    queue = (list<TaskHeader>*)data;
    taskHdr.setData(atoi(argv[0]), argv[1], (unsigned)atoi(argv[2]), argv[3]);
    queue->push_back(taskHdr);
    data = (void*)queue;
    
    return (0);
}

int         sendQueue(int admin_fd)
{
    sqlite3*    db;
    string      query;
    void*       data;
    list<TaskHeader>*  queue;

    queue = new list<TaskHeader>;
    data = (void*)queue;
    query = "SELECT * FROM task_queue ORDER BY queue_num;";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_sendQueue, data, NULL);
    sqlite3_close(db);
    queue = (list<TaskHeader>*)data;
    std::cout << "Размер очереди: " << queue->size() << std::endl;

    char        buf[BUF_SIZE];
    MainHeader  mainHeader;
    int         sendBytes;
    int         totalBytes;  
    unsigned    msgSize;

    msgSize = sizeof(MainHeader) + queue->size() * sizeof(TaskHeader);
    // msgSize = sizeof(MainHeader);
    totalBytes = 0;
    mainHeader.setData(msgSize, queue->size(), QUEUE_LIST, 0);
    sendBytes = sendAll(admin_fd, (char*)&mainHeader, sizeof(MainHeader), 0);
    if (sendBytes <= 0)
    {
        cerr << "Sending error. Position - 1. Last bytes sent: " << sendBytes
                << ". Errno: " << errno << endl;
        return (sendBytes);
    }
    totalBytes += sendBytes;
    for(auto task : *queue)
    {
        sendBytes = sendAll(admin_fd, (char*)&task, sizeof(TaskHeader), 0);
        if (sendBytes <= 0)
        {
            cerr << "Sending error. Position - 2. Last bytes sent: " << sendBytes
                    << ". Errno: " << errno << endl;
            return (sendBytes);
        }
        totalBytes += sendBytes;
    }
    delete queue;

    return (totalBytes);
}

void        clearQueue()
{
    sqlite3*    db;
    string      query;

    query = "DELETE FROM task_query;";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

void        fillQueue(list<TaskHeader>* queue)
{
    sqlite3*    db;
    string      query;
    char*       errmsg;
    
    query = "DELETE FROM task_queue;";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, &errmsg);
    cerr << errmsg << endl;
    for (auto task : *queue)
    {
        query = "INSERT INTO task_queue(task_id, user_name, queue_num, time) " \
                "VALUES (" + std::to_string(task.getTaskId()) + " ,'"
                        + task.getUserName() + "', "
                        + std::to_string(task.getQueueNum()) + ", '"
                        + task.getTime() + "');";
        sqlite3_exec(db, query.c_str(), NULL, NULL, &errmsg);
        cerr << errmsg << endl;
    }

    sqlite3_close(db);
}

static int callback_getOnlineUsers(void* data, int argc, char** argv, char** azColName)
{
    list<string>* lst;
    
    lst = (list<string>*)data;
    lst->push_back(argv[0]);
    data = (void*)lst;
    
    return (0);
}

list<string>*   getOnlineUsers(list<string>* lst)
{
    sqlite3*    db;
    string      query;
    void*       data;

    
    query = "SELECT user_name FROM online_users ORDER BY user_name;";
    data = (void*)lst;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_getOnlineUsers, data, NULL);
    sqlite3_close(db);
    
    return (lst);
}

void            addTaskPathes(int taskId, list<string> pathes)
{
    sqlite3*    db;
    string      query;
    char*       errMsg;

    db = connectDB((char*)DB_PATH);
    for (string path : pathes)
    {
        query = "INSERT INTO task_pathes(task_id, file_path) " \
                "VALUES (" + std::to_string(taskId) + ", '" + path + "');";
        sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    }
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
}

int             getFirstTask()
{
    vector<vector<string>>* res;
    sqlite3*                db;
    string                  query;
    char*                   errMsg;
    void*                   data;
    int                     taskId;

    res = new vector<vector<string>>;
    data = (void*)res;
    db = connectDB((char*)DB_PATH);
    query = "SELECT task_id FROM task_queue WHERE queue_num == 1;";
    sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
    res->size() == 0 ? taskId = -1 : taskId = std::stoi((*res)[0][0]);
    delete res;

    return (taskId);
}

list<string>    getTaskPathes(int taskId)
{
    vector<vector<string>>* res;
    list<string>            pathes;
    sqlite3*                db;
    string                  query;
    char*                   errMsg;
    void*                   data;

    res = new vector<vector<string>>;
    data = (void*)res;
    db = connectDB((char*)DB_PATH);
    query = "SELECT file_path FROM task_pathes " \
            "WHERE task_id == " + std::to_string(taskId) + ";";
    std::cout << query << std::endl;
    sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
    for (auto path : *res)
        pathes.push_back(path[0]);
    delete res;

    return (pathes);
}

void            setTaskState(int taskId, string state)
{
    sqlite3*                db;
    string                  query;
    char*                   errMsg;

    db = connectDB((char*)DB_PATH);
    query = "UPDATE tasks SET state = '" + state + "' " \
            "WHERE task_id == " + std::to_string(taskId) + ";";
    std::cout << query << std::endl;
    sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    std::cerr << errMsg << std::endl;
    if (state == "Готово")
    {
        query = "DELETE FROM task_queue " \
                "WHERE task_id = " + std::to_string(taskId) + ";";
        cout << query << endl;
        sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
        std::cerr << errMsg << std::endl;
    }
    sqlite3_close(db);
}

list<TaskStateHeader> &getTasksInfo(string userName, list<TaskStateHeader>& tasksList)
{
    vector<vector<string>>* res;
    TaskStateHeader         task;
    sqlite3*                db;
    string                  query;
    char*                   errMsg;
    void*                   data;

    tasksList.clear();
    res = new vector<vector<string>>;
    data = (void*)res;
    db = connectDB((char*)DB_PATH);
    query = "SELECT state, time, task_id FROM tasks " \
            "WHERE user_name == '" + userName + "';";
    sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
    for (int i = 0; i < res->size(); i++)
    {
        STATE state;
        if ((*res)[i][0] == "Готово")       state = DONE;
        if ((*res)[i][0] == "В очереди")    state = IN_QUEUE;
        if ((*res)[i][0] == "Отменено")     state = CANCEL;
        if ((*res)[i][0] == "Решается")     state = SOLVING;
        char* time = (char*)((*res)[i][1]).c_str();
        int test = std::stoi("45");
        unsigned taskId = (unsigned)(std::stoi((*res)[i][2]));
        task.setData(state, time, taskId);
        tasksList.push_back(task);
        // std::cout << task.getState() << " " << task.getTime() << " " << task.getTaskId() << std::endl;
    }
    delete (res);

    return (tasksList);
}

list<string>    getSolutionPathes(int taskId, list<string> &files)
{
    vector<vector<string>>* res;
    sqlite3*                db;
    string                  query;
    char*                   errMsg;
    void*                   data;

    files.clear();
    res = new vector<vector<string>>;
    data = (void*)res;
    db = connectDB((char*)DB_PATH);
    query = "SELECT file_path FROM solution_pathes " \
            "WHERE task_id == " + std::to_string(taskId) + ";";
    sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
    for (int i = 0; i < res->size(); i++)
        files.push_back((*res)[i][0]);
    std::cerr << errMsg << std::endl;
    sqlite3_close(db);
    delete (res);

    return (files);
}

void            setSolutionPathes(int taskId, list<string> &files)
{
    sqlite3*                db;
    string                  query;
    char*                   errMsg;

    db = connectDB((char*)DB_PATH);
    for (string path : files)
    {
        query = "INSERT INTO solution_pathes(task_id, file_path) " \
                "VALUES (" + std::to_string(taskId) + ", '" + path + "');";
        sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
        std::cerr << errMsg << std::endl;
    }
    sqlite3_close(db);
}

int             getSockFd(string userName)
{
    vector<vector<string>>* res;
    string                  query;
    sqlite3*                db;
    void*                   data;
    int                     sock_fd;

    res = new vector<vector<string>>;
    data = (void*)res;
    query = "SELECT sock_num FROM online_users " \
            "WHERE user_name = '" + userName + "';";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_result, data, NULL);
    if (res->size() == 0)
        sock_fd = -1;
    else
        sock_fd = std::stoi((*res)[0][0]);
    sqlite3_close(db);
    delete (res);
    return (sock_fd);
}

void            cancelQueueTask(int taskId)
{
    sqlite3*                db;
    string                  query;
    char*                   errMsg;

    db = connectDB((char*)DB_PATH);
    query = "DELETE FROM task_queue " \
            "WHERE task_id = " + std::to_string(taskId) + ";";
    cout << query << endl;
    sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    std::cerr << errMsg << std::endl;
    setTaskState(taskId, "Отменено");
    sqlite3_close(db);
}

list<LoginHeader>       getUsersInfo(list<LoginHeader> &usersInfoList)
{
    vector<vector<string>>* res;
    LoginHeader             loginHdr;
    string                  query;
    sqlite3*                db;
    void*                   data;
    int                     sock_fd;

    usersInfoList.clear();
    res = new vector<vector<string>>;
    data = (void*)res;
    query = "SELECT user_name, user_password FROM users_info " \
            "ORDER BY user_name;";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_result, data, NULL);
    sqlite3_close(db);
    for (auto userInfo : *res)
    {
        loginHdr.setData((char*)userInfo[0].c_str(), (char*)userInfo[1].c_str());
        usersInfoList.push_back(loginHdr);
    }
    delete (res);
    return (usersInfoList);
}

void            deleteUser(string userName)
{
    string      query;
    sqlite3*    db;

    query = "DELETE FROM users_info " \
            "WHERE user_name == '" + userName + "';";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

void            addNewUser(LoginHeader userInfo)
{
    string      query;
    sqlite3*    db;

    query = "INSERT INTO users_info(user_name, user_password) " \
            "VALUES('" + std::string(userInfo.getUserName()) + "', '"
                + std::string(userInfo.getUserPassword()) + "');";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

void            changePassword(LoginHeader userInfo)
{
    string      query;
    sqlite3*    db;

    query = "UPDATE users_info " \
            "SET user_password = '" + std::string(userInfo.getUserName()) + "' " \
            "WHERE user_name == '" + std::string(userInfo.getUserPassword()) + "';";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

list<FileHeader>    getBinsPathes(list<FileHeader> &binsPathes)
{
    vector<vector<string>>* res;
    FileHeader              fileHdr;
    string                  query;
    sqlite3*                db;
    void*                   data;

    binsPathes.clear();
    res = new vector<vector<string>>;
    data = (void*)res;
    query = "SELECT bin_id, bin_path FROM bins ORDER BY bin_path;";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_result, data, NULL);
    sqlite3_close(db);
    for (auto binInfo : *res)
    {
        fileHdr.setData(std::stoi(binInfo[0]), (char*)binInfo[1].c_str());
        binsPathes.push_back(fileHdr);
    }
    delete (res);

    return (binsPathes);
}

void            addNewBin(string binPath)
{
    string      query;
    sqlite3*    db;

    query = "INSERT INTO bins(bin_path) VALUES('" + binPath + "');";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}

string          getBinPath(int binId)
{
    vector<vector<string>>* res;
    string                  query;
    sqlite3*                db;
    void*                   data;
    string                  binPath;

    res = new vector<vector<string>>;
    data = (void*)res;
    query = "SELECT bin_path FROM bins " \
            "WHERE bin_id == " + std::to_string(binId) + ";";
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), callback_result, data, NULL);
    sqlite3_close(db);
    binPath = (*res)[0][0];
    delete (res);

    return (binPath);

}

void            setBinId(int taskId, int binId)
{
    string      query;
    sqlite3*    db;

    query = "UPDATE tasks SET bin_id = " + std::to_string(binId) + " " \
            "WHERE task_id == " + std::to_string(taskId) + ";";
    std::cout << query << std::endl;
    db = connectDB((char*)DB_PATH);
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
}
// bool            isSolverFree()
// {
//     vector<vector<string>>* res;
//     sqlite3*                db;
//     string                  query;
//     char*                   errMsg;
//     void*                   data;
//     bool                    isFree;
    
//     res = new vector<vector<string>>;
//     data = (void*)res;
//     db = connectDB((char*)DB_PATH);
//     query = "SELECT * FROM tasks WHERE state == 'Решается';";
//     sqlite3_exec(db, query.c_str(), callback_result, data, &errMsg);
//     std::cerr << errMsg << std::endl;
//     sqlite3_close(db);
//     res->size() == 0 ? isFree = true : isFree = false;
//     delete res;
//     return (isFree);
// }