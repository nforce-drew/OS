#include "ServerFunctions.h"

string fileName(string pathname)
{
    const size_t last_slash_idx = pathname.find_last_of("\\/");
    if (string::npos != last_slash_idx)
    {
        pathname.erase(0, last_slash_idx + 1);
    }
    return (pathname);
}

string currentTimeInfo()
{
    tm*     timeInfo;
    time_t  seconds;
    char timeStr[20];

    seconds = time(NULL);
    timeInfo = localtime(&seconds);
    char* format = (char*)"%Y-%m-%d %H:%M:%S";
    strftime(timeStr, 20, format, timeInfo);
    // std::cout<<"Current Datetime: "<<timeStr<<std::endl;

    return (string(timeStr));
}

unsigned appFileData(string folderAndFileName, const char *data, unsigned len)
{
    ofstream    fout;
    string      filePath = SAVE_PATH + folderAndFileName;

    fout.open(filePath, ios_base::app);
    if (!fout.is_open())
    {
        cerr << "ERROR. Файл " << filePath << " для записи не открыт!\n";
        return (0);
    }
    fout.write(data, len);
    fout.close();
    return (len);
}

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

int recvAll(int sock, char *strData, TYPE &dataType, void* data)
{
    char        buf[BUF_SIZE];
    int         readBytes;
    unsigned    totalBytes;
    unsigned    blockBytes;
    unsigned    curByte;
    unsigned    writeBytes;
    string      filename;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    string      savePath;
    string      folderName; //В эту строку нужно присвоить имя папки для сохранения файлов
                                    //не путь, а имя папки, которое заканчивается слэшем!!!
                                    //сам путь содержится в h-файле в SAVE_PATH
    
    totalBytes = 0;
    while (totalBytes < sizeof(MainHeader))
    {
        readBytes = recv(sock, buf + totalBytes, BUF_SIZE - totalBytes, 0);
        if (readBytes <= 0)
        {
            cerr << "Error: recvAll() readBytes <= 0" << endl;
            return (readBytes);
        }
        totalBytes += (int)readBytes;
    }
    mainHeader.setByteArr(buf);

    curByte = sizeof(MainHeader);
    blockBytes = totalBytes;

    dataType = mainHeader.getType();
    if (mainHeader.getType() == SEND_FILES)
    {
        list<string>*   paths = (list<string>*)data;
        int             taskId;
        // Создание папки для сохранения
        string curTime = currentTimeInfo();
        string userName = getUserName(sock);
        mkdir((char*)SAVE_PATH, S_IRWXU);
        folderName = userName + " " + curTime;
        int i;
        string change = "_";
        for (int j = 0; j < folderName.length() - 1; j++)
        {
            i = folderName.find(" ");
            if(i == j)
                folderName.replace(i, change.length(), change);
        }
        savePath = (char*)SAVE_PATH + folderName;

        mkdir(savePath.c_str(), S_IRWXU);
        folderName += "/";
        taskId = createTask(userName, curTime);
        joinQueue(taskId, userName, curTime);
        
        // sendQueue(6); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            while (blockBytes - curByte < sizeof(FileHeader))
            {
                memcpy(buf, buf + curByte, blockBytes - curByte);
                blockBytes = blockBytes - curByte;
                curByte = 0;
                readBytes = recv(sock, buf + blockBytes, BUF_SIZE - blockBytes, 0);
                if (readBytes <= 0)
                {
                    cerr << "Error: recvAll() readBytes <= 0" << endl;
                    return (readBytes);
                }
                totalBytes += readBytes;
                blockBytes += readBytes;
            }
            fileHeader.setByteArr(buf + curByte);
            paths->push_back(string(SAVE_PATH) + folderName + string(fileHeader.getFileName()));

            ofstream fout;
            fout.open(paths->back(), ios_base::trunc);
            if (!fout.is_open())
            {
                cerr << "ERROR. Файл " << paths->back() << " для очищения не открыт!\n";
                return (0);
            }
            
            fout.close();

            curByte += sizeof(FileHeader);
            writeBytes = 0;
            while (writeBytes != fileHeader.getFileSize())
            {
                if ((curByte == blockBytes))
                {
                    curByte = 0;
                    blockBytes = 0;

                    readBytes = recv(sock, buf, BUF_SIZE, 0);
                    if (readBytes <= 0)
                    {
                        cerr << "Error: recvAll() readBytes <= 0" << endl;
                        return (readBytes);
                    }
                    totalBytes += (int)readBytes;
                    blockBytes = (int)readBytes;
                }
                if ((blockBytes - curByte) <= (fileHeader.getFileSize() - writeBytes))
                {
                    writeBytes += appFileData(folderName + string(fileHeader.getFileName()), 
                                                buf + curByte, blockBytes - curByte);
                    curByte += blockBytes - curByte;
                }
                else
                {
                    int new_writeBytes;
                    new_writeBytes = fileHeader.getFileSize() - writeBytes;
                    writeBytes += appFileData(folderName + string(fileHeader.getFileName()), 
                                                buf + curByte, new_writeBytes);
                    curByte += new_writeBytes;
                }
            }
        }
        data = (void*)paths;
        memcpy(strData, (char*)&taskId, sizeof(int));
        if (mainHeader.getMsgSize() == totalBytes)
            sendData(sock, MainHeader(sizeof(MainHeader), 0, SUCCESS_RECIEVE), NULL, 0);
        return (totalBytes);
    }
    else if (mainHeader.getType() == CHECK_LOGIN)
    {
        blockBytes = totalBytes;
        while (blockBytes - curByte < sizeof(LoginHeader))
        {
            memcpy(buf, buf + curByte, blockBytes - curByte);
            blockBytes = blockBytes - curByte;
            curByte = 0;
            readBytes = recv(sock, buf + blockBytes, BUF_SIZE - blockBytes, 0);
            if (readBytes <= 0)
            {
                cerr << "Error: recvAll() readBytes <= 0" << endl;
                return (readBytes);
            }
            totalBytes += readBytes;
            blockBytes += readBytes;
        }
        data = nullptr;
        memcpy(strData, buf, BUF_SIZE);
        return (totalBytes);
    }

    list<TaskHeader>* queue = (list<TaskHeader>*)data;
    if (mainHeader.getType() == QUEUE_LIST)
    {
        TaskHeader  taskHdr;
        char*       queueData;
        unsigned    msgSize;
        
        msgSize = mainHeader.getCount() * sizeof(TaskHeader);
        queueData = new char[msgSize];
        memcpy(queueData, buf + sizeof(MainHeader), totalBytes - sizeof(MainHeader));
        while (totalBytes < sizeof(MainHeader) + msgSize)
        {
            readBytes = recv(sock, queueData + totalBytes, msgSize - totalBytes, 0);
            if (readBytes <= 0)
            {
                cerr << "Error: recvAll() readBytes <= 0" << endl;
                return (readBytes);
            }
            totalBytes += (int)readBytes;
        }
        std::cout << "===============================" << std::endl;
        // std::cout << bytes(queueData, 62) << std::endl;
        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            taskHdr.setByteArr(queueData + i * sizeof(TaskHeader));
            queue->push_back(taskHdr);
            std::cout << taskHdr.getUserName() << std::endl;
        }
        std::cout << "===============================" << std::endl;
        cout << "2 queue->size(): " << queue->size() << endl;;
        data = (void*)queue;
    }
    if (dataType == RECONNECT || dataType == DELETE_USER
        || dataType == ADD_NEW_USER || dataType == CHANGE_PASSWORD)
    {
        curByte = sizeof(MainHeader);
        memcpy(buf, buf + curByte, totalBytes - sizeof(MainHeader));
        curByte = totalBytes - sizeof(MainHeader);
        while (totalBytes < mainHeader.getMsgSize())
        {
            readBytes = recv(sock, buf + curByte, mainHeader.getMsgSize() - totalBytes, 0);
            if (readBytes <= 0)
            {
                cerr << "Error: recvAll() readBytes <= 0" << endl;
                return (readBytes);
            }
            totalBytes += (int)readBytes;
        }
        memcpy(strData, buf, BUF_SIZE);
        // userName->copy(buf, mainHeader.getMsgSize() - sizeof(MainHeader) - 1);
    }
    if (dataType == GET_SOLUTION || dataType == CANCEL_TASK)
        memcpy(strData, buf, BUF_SIZE);
    return (totalBytes);
}

unsigned getFileSize(string path)
{
    ifstream    fin;
    streampos   begin, end;

    fin.open(path, ios_base::binary);
    if (!fin.is_open())
    {
        cout << "fileSize: file " << path << " wasn't open. Errno: " << errno << endl;
        return (0);
    }
    begin = fin.tellg();
    fin.seekg(0, ios::end);
    end = fin.tellg();
    return ((unsigned)(end - begin));
}

unsigned getMessageSize(list<string> &paths)
{
    unsigned msgSize;
    unsigned fileSize;

    msgSize = sizeof(MainHeader);
    for(string filePath : paths)
    {
        msgSize += (unsigned)sizeof(FileHeader);
        fileSize = getFileSize(filePath);
        if (fileSize == 0)
            return (0);
        msgSize += fileSize;
    }
    return (msgSize);
}

int sendAll(int sock_fd, char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while(total < len)
    {
        n = send(sock_fd, buf+total, len-total, flags);
        if(n == -1) { break; }
        total += n;
    }
    return (n == -1 ? -1 : total);
}

int sendData(int sock, const MainHeader &mainHdr, char* data, unsigned len)
{
    int totalBytes;
    int sendBytes;

    totalBytes = 0;
    sendBytes = sendAll(sock, (char*)&mainHdr, sizeof(MainHeader), 0);
    if (sendBytes <= 0)
        return (sendBytes);
    totalBytes += sendBytes;
    
    if (len == 0 || data == NULL)
        return (totalBytes);
    sendBytes = sendAll(sock, data, len, 0);
    if (sendBytes <= 0)
        return (sendBytes);
    totalBytes += sendBytes;
    return (totalBytes);
}

int sendFiles(int sock, list<string> &paths)
{
    char        buf[BUF_SIZE];
    ifstream    fin;
    streampos   begin, end;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    unsigned    readBytes;
    int         sendBytes;
    int         totalBytes;  

    totalBytes = 0;
    mainHeader.setData(getMessageSize(paths), paths.size(), SEND_FILES);
    sendBytes = sendAll(sock, (char*)&mainHeader, sizeof(MainHeader), 0);
    if (sendBytes <= 0)
    {
        cerr << "Sending error. Position - 1. Last bytes sent: " << sendBytes
                << ". Errno: " << errno << endl;
        return (sendBytes);
    }
    totalBytes += sendBytes;
    for(string filePath : paths)
    {
        fin.open(filePath);
        if (!fin.is_open())
        {
            cout << "sendSolution: file " << filePath << " wasn't open. Errno: " << errno << endl;
            return (0);
        }
        else
            cout << "File " << filePath << " was opened for sending!" << endl;

        fileHeader.setData(getFileSize(filePath), (char*)fileName(filePath).data());
        sendBytes = sendAll(sock, (char*)&fileHeader, sizeof(FileHeader), 0);
        if (sendBytes <= 0)
        {
            cerr << "Sending error. Position - 2. Last bytes sent: " << sendBytes
                    << ". Errno: " << errno << endl;
            return (sendBytes);
        }
        totalBytes += sendBytes;
        for (;;)
        {
            readBytes = (unsigned)fin.readsome(buf, (unsigned)BUF_SIZE);
            cout << "file bytes: " << readBytes << endl;
            if (!readBytes)
                break;            
            sendBytes = sendAll(sock, buf, readBytes, 0);
            if (sendBytes <= 0)
            {
                cerr << "Sending error. Position - 3. Last bytes sent: " << sendBytes 
                        << ". Errno: " << errno << endl;
                return (sendBytes);
            }
            totalBytes += sendBytes;
        }
        fin.close();
    }
    return (totalBytes);
}

char*       onlineUsersToChar(list<string>* lst)
{
    char* users;
    auto it = lst->begin();

    users = new char[lst->size() * 20];
    for (int i = 0; i < lst->size(); i++)
    {
        it = lst->begin();
        advance(it, i);
        strcpy(users + i * 20, (*it).c_str());
    }
    return (users);
}

int         sendOnlineUsers(int admin_fd)
{
    list<string>*   lst;
    MainHeader      mainHdr;
    char*           users;
    unsigned        msgSize;
    int             sentBytes;

                
    lst = new list<string>;
    lst = getOnlineUsers(lst);
    users = onlineUsersToChar(lst);
    msgSize = sizeof(MainHeader) + lst->size() * 20;
    mainHdr.setData(msgSize, lst->size(), ONLINE_USERS);
    for (int i = 0; i < 9999999; i++) {}
    sentBytes = sendData(admin_fd, mainHdr, users, lst->size() * 20);
    delete users;
    return (sentBytes);
}

int         sendTasksInfo(int sock_fd, string userName)
{
    list<TaskStateHeader>   tasks;
    MainHeader              mainHdr;
    int                     bytesSend;
    unsigned                msgSize;
    char*                   buf;

    tasks = getTasksInfo(userName, tasks);
    msgSize = sizeof(MainHeader) + (unsigned)tasks.size() * sizeof(TaskStateHeader);
    mainHdr.setData(msgSize, (unsigned)tasks.size(), TASKS_INFO);
    buf = new char[msgSize - sizeof(MainHeader)];
    int i = 0;
    for (auto tsk : tasks)
    {
        memcpy(buf + i * sizeof(TaskStateHeader), (char*)&tsk, sizeof(TaskStateHeader));
        i++;
    }
    bytesSend = sendData(sock_fd, mainHdr, buf, msgSize - sizeof(MainHeader));
    
    return (bytesSend);
}

int         sendUsersInfo(int admin_fd)
{
    list<LoginHeader> usersInfoList;
    MainHeader  mainHdr;
    char*       data;
    int         dataSize;
    int         bytesSend;

    usersInfoList = getUsersInfo(usersInfoList);
    for (auto info : usersInfoList)
        cout << info.getUserName() << " " << info.getUserPassword() << endl;
    dataSize = usersInfoList.size() * sizeof(LoginHeader);
    data = new char[dataSize];
    auto it = usersInfoList.begin();
    int i = 0;
    for (auto info : usersInfoList)
    {
        memcpy(data + i * sizeof(LoginHeader), (char*)&(info), sizeof(LoginHeader));
        i++;
    }
    mainHdr.setData(dataSize + sizeof(MainHeader), usersInfoList.size(), USERS_INFO);
    for (i = 0; i < (int)mainHdr.getCount(); i++)
    {
        cout << bytes(data  + i * sizeof(LoginHeader), sizeof(LoginHeader)) << endl;
    }
    bytesSend = sendData(admin_fd, mainHdr, data, dataSize);
    delete data;
    return (bytesSend);
}