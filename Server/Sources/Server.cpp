#include "MainHeader.h"
#include "FileHeader.h"
#include "Headers.h"
#include "ServerFunctions.h"
#include "DataBaseFunctions.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <list>
#include <thread>
#include <chrono>
#include <sys/stat.h>
using namespace std;

#define BUF_SIZE    1024
#define PORT_NUMBER 5308
#define SOLUTIONS_PATH "/home/nspace/OS/Server/Solutions/" // в конце должен быть слэш!!!

int     admin_fd;
bool    isSolverFree;
string  binPath;

void solver()
{
    ofstream fout_task;
    ofstream fout_solution;
    ifstream fin_binInfo;
    ifstream fin_solInfo;
    string taskInfoPath = "/home/nspace/OS/Server/TaskInfo.txt";
    string solutionInfoPath = "/home/nspace/OS/Server/SolutionInfo.txt";
    string binInfoPath = "/home/nspace/OS/Server/BinInfo.txt";

    isSolverFree = false;
    std::cout << "===SOLVER STARTED===" << std::endl;
    
    int taskId = getFirstTask();
    if (taskId == -1)
    {

        std::cout << "===SOLVER END===" << std::endl;
        isSolverFree = true;
        return;
    }
    string userName = getUserNameByTaskId(taskId);
    setTaskState(taskId, "Решается");
    int sock_fd = getSockFd(userName);
    sendTasksInfo(sock_fd, userName);
    this_thread::sleep_for(chrono::milliseconds(10000));
    list<string> pathes = getTaskPathes(taskId);

    
    string curTime = currentTimeInfo();
    string folderName;
    string savePath;
    string shellCommand;

    // // this_thread::sleep_for(chrono::milliseconds(10000));

    mkdir((char*)SOLUTIONS_PATH, S_IRWXU);
    folderName = userName + " " + curTime;
    int i;
    string change = "_";
    for (int j = 0; j < folderName.length() - 1; j++)
    {
        i = folderName.find(" ");
        if(i == j)
            folderName.replace(i, change.length(), change);
    }
    savePath = (char*)SOLUTIONS_PATH + folderName;
    mkdir(savePath.c_str(), S_IRWXU);
    list<string> solutionPathes;
    fout_task.open(taskInfoPath, std::ios_base::trunc);
    if (!fout_task.is_open())
        cerr << "File TaskInfo.txt opening error." << endl;
    else
    {
        for (auto el : pathes)
        {
            if (el != *(pathes.begin()))
                fout_task.write("\n", 1);
            fout_task.write(el.c_str(), el.size());
            // fout.write("\n", 1);
            // shellCommand = "cp " + el + " " + savePath;
            // system(shellCommand.c_str());
            // solutionPathes.push_back(savePath + '/' + fileName(el));
        }
        fout_task.close();
        fout_solution.open(solutionInfoPath, std::ios_base::trunc);
        if (!fout_solution.is_open())
            cerr << "File SolutionInfo.txt opening error." << endl;
        else
        {
            fout_solution.write(savePath.c_str(), savePath.size());
            fout_solution.close();
        }
        string binName = fileName(binPath);
        string command = "cd " + binPath + "; ./" + binName + " " 
                            + taskInfoPath + " " + solutionInfoPath;
        system(command.c_str());
        std::cout << "????????" << std::endl;
        fin_binInfo.open(binInfoPath);
        if (!fin_binInfo.is_open())
            cout << "File BinInfo.txt opening error. Errno: " << errno << endl;
        else
        {
            string res = "1";
            while (res != "")
            {
                command = "ps | grep \" " + binName + "$\" > " + "BinInfoPath.txt";
                system(command.c_str());
                std::getline(fin_binInfo, res);
                fin_binInfo.seekg(0);
            }

            fin_binInfo.close();
        }
    }
    fin_solInfo.open(solutionInfoPath);
    if (!fin_solInfo.is_open())
        cerr << "File SolutionInfo.txt opening error." << endl;
    else
    {
        string solutionPath;
        while(!fin_solInfo.eof())
        {
            solutionPath.clear();
            std::getline(fin_solInfo, solutionPath);
            if (solutionPath != "")
                solutionPathes.push_back(solutionPath);
        }
        fin_solInfo.close();
    }
    setSolutionPathes(taskId, solutionPathes);
    setTaskState(taskId, "Готово");
    
    std::cout << "sock_fd = " << sock_fd << std::endl;
    if (sock_fd != -1)
        sendTasksInfo(sock_fd, userName);
    sendQueue(admin_fd);
    std::cout << "===SOLVER END===" << std::endl;
    if (getFirstTask() != -1)
        solver();
    isSolverFree = true;
    return;
}

//=================================================================================
int main(const int argc, const char** argv)
{
    int     listener;
    struct  sockaddr_in addr;
    char    buf[BUF_SIZE];
    int     bytes_read;
    string  query;
    thread  solverTh;

    solverTh = thread(solver);
    solverTh.detach();
    if (argc > 2)
        return (-1);
    if (argc == 2 && atoi(argv[1]) == 0)
        return (-1);
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        cerr << "Error: socket. Errno: " << errno << endl;
        exit(1);
    }

    admin_fd = -1;
    isSolverFree = true;
    cout << currentTimeInfo() << endl;
    std::cout << "First task id: " << getFirstTask() << std::endl;
    fcntl(listener, F_SETFL, O_NONBLOCK);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)PORT_NUMBER);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        cerr << "Error: bind. Errno: " << errno << endl;
        exit(2);
    }

    listen(listener, 2);
    
    set<int> clients;
    // clients.clear(); !!!!!!!!!!!!

    cout << "The server is running..." << endl;

    // Очищаем онлайн юзеров в БД
    sqlite3* db = connectDB((char*)DB_PATH);
    query = "DELETE FROM online_users;";
    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    sqlite3_close(db);

    while(1)
    {
        // Заполняем множество сокетов
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
            FD_SET(*it, &readset);

        // Задаём таймаут
        timeval timeout;
        if (argc == 2)
            timeout.tv_sec = atoi(argv[1]);
        else
            timeout.tv_sec = 15; //Время работы сервера
        timeout.tv_usec = 0;

        // Ждём события в одном из сокетов
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if (argc == 2)
        {
            if(select(mx + 1, &readset, NULL, NULL, &timeout) <= 0) //!!! Еcли поставить <= 0 сервер будет работать
                                                                    // отведенное время, заданное выше
                                                                    //Еcли поставить < 0 сервер будет работать постоянно
            {
                cerr << "Error: select. Errno: " << errno << endl;
                close(listener);
                exit(3);
            }
        }
        else
        {
            if(select(mx + 1, &readset, NULL, NULL, &timeout) < 0) //!!! Еcли поставить <= 0 сервер будет работать
                                                        // отведенное время, заданное выше
                                                        //Еcли поставить < 0 сервер будет работать постоянно
            {
                cerr << "Error: select. Errno: " << errno << endl;
                close(listener);
                exit(3);
            }
        }
        

        // Определяем тип события и выполняем соответствующие действия
        if(FD_ISSET(listener, &readset))
        {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                cerr << "Error: accept. Errno: " << errno << endl;
                exit(3);
            }
            cout << "New client connected. Socket number: " << sock << endl;
            fcntl(sock, F_SETFL, O_NONBLOCK);

            clients.insert(sock);
        }


        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if (FD_ISSET(*it, &readset))
            {
                list<string>*       paths;
                list<TaskHeader>*   queue;
                TYPE                dataType;
                void*               data;

                // Поступили данные от клиента, читаем их
                list<string>* lst = new list<string>;
                data = (void*)lst;
                std::cout << "ДАННЫЕ" << std::endl;
                bytes_read = recvAll(*it, buf, dataType, data);
                // cout << "main" << data << endl;
                cout << "Bytes read: " << bytes_read << endl;
                if (bytes_read <= 0)
                {
                    // Соединение разорвано, удаляем сокет из множества, удаляем из online в БД
                    sqlite3* db = connectDB((char*)DB_PATH);
                    query = "DELETE FROM online_users WHERE sock_num = "
                        + std::to_string(*it) + ";";
                    sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
                    sqlite3_close(db);
                    sendOnlineUsers(admin_fd);
                    if (*it == admin_fd)
                        admin_fd = -1;
                    close(*it);
                    clients.erase(*it);
                    cout << "Connection refused with client." << endl;
                    continue;
                }
                else
                {
                    // ОБРАБОТКА ДАННЫХ
                    switch (dataType)
                    {
                        case CHECK_LOGIN:
                        {
                            MainHeader  mainHdr(buf);
                            LoginHeader loginHdr(buf + sizeof(MainHeader));

                            std::cout << "\t-> CHECK_LOGIN - username: \"" << loginHdr.getUserName()  
                                    << "\" password: " << loginHdr.getUserPassword() << "\"" << std::endl;
                            sqlite3* db = connectDB((char*)DB_PATH);
                            checkLoginPermission(db, *it, loginHdr.getUserName(), loginHdr.getUserPassword());
                            sqlite3_close(db);
                            sendOnlineUsers(admin_fd);
                            sendTasksInfo(*it, loginHdr.getUserName());
                            sendBinsInfo(*it);
                            break;
                        }
                        case SEND_FILES:
                        {
                            int taskId;
                            MainHeader mainHdr;

                            cout << "\t-> SEND_FILES - count files: " << lst->size() << endl;
                            if (admin_fd != -1)
                                sendQueue(admin_fd);
                            mainHdr.setByteArr(buf);
                            taskId = mainHdr.getCount();
                            std::cout << "\t\t tsk id: " << taskId << std::endl;
                            setBinId(taskId, mainHdr.getInfo());
                            addTaskPathes(taskId, *lst);
                            sendTasksInfo(*it, getUserName(*it));
                            binPath = getBinPath(mainHdr.getInfo());
                            // std::cout << "BIN ID = " << mainHdr.getInfo() << std::endl;
                            // binPath = "/home/nspace/OS/Server/filesToZip.out";
                            if (isSolverFree)
                            {
                                this_thread::sleep_for(chrono::milliseconds(100));
                                solverTh = thread(solver);
                                solverTh.detach();
                            }
                            delete lst;
                            break;        
                        }
                        case SEND_BIN:
                        {
                            cout << "\t-> SEND_BIN - count files: " << lst->size() << endl;
                            binPath = "/home/nspace/OS/Server/filesToZip.out";
                            addNewBin(*(lst->begin()));
                            sendBinsInfo(admin_fd);
                            for(set<int>::iterator us_it = clients.begin(); us_it != clients.end(); us_it++)
                            {
                                if (*us_it != admin_fd)
                                    sendBinsInfo(*us_it);
                            }
                            delete lst;
                            break;        
                        }
                        case QUEUE_LIST:
                        {
                            cout << "=== Queue sended ===" << endl;
                            queue = (list<TaskHeader>*)data;
                            clearQueue();
                            fillQueue(queue);                        
                            delete queue;
                            break;
                        }
                        case ADMIN_LOGGED:
                        {
                            list<string>*   lst;
                            MainHeader      mainHdr;
                            char*           users;
                            unsigned        msgSize;

                            admin_fd = *it;
                            cout << "\t-> ADMIN_LOGGED. Socket: " << *it << endl;
                            sendQueue(admin_fd);                      
                            sendOnlineUsers(admin_fd);
                            sendUsersInfo(admin_fd);
                            sendBinsInfo(admin_fd);
                            break;
                        }
                        case RECONNECT:
                        {
                            std::cout << "\t-> RECONNECT - user name: \"" 
                                        << buf << "\"" << std::endl;
                            // std::cout << bytes(buf, 20) << std::endl;
                            addOnlineUser(*it, std::string(buf));
                            if (admin_fd != -1)
                            {
                                sendQueue(admin_fd);                      
                                sendOnlineUsers(admin_fd);
                            }
                            sendTasksInfo(*it, getUserName(*it));
                            sendBinsInfo(*it);
                            break;
                        }
                        case GET_SOLUTION:
                        {
                            MainHeader      mainHdr;
                            list<string>    files;

                            std::cout << "GET_SOLUTION" << std::endl;
                            mainHdr.setByteArr(buf);
                            std::cout << "send taskId = " << mainHdr.getCount() << std::endl;
                            files = getSolutionPathes(mainHdr.getCount(), files);
                            sendFiles(*it, files);
                            break;
                        }
                        case CANCEL_TASK:
                        {
                            MainHeader      mainHdr;
                            string          userName;
                            int             userSock_fd;

                            mainHdr.setByteArr(buf);
                            std::cout << "CANCEL_TASK" << std::endl;
                            std::cout << "canceled = " << mainHdr.getCount() << std::endl;
                            mainHdr.setByteArr(buf);
                            cancelQueueTask(mainHdr.getCount());
                            this_thread::sleep_for(std::chrono::milliseconds(500));
                            if (*it != admin_fd)
                            {
                                sendTasksInfo(*it, getUserName(*it));
                                sendQueue(admin_fd);
                            }
                            else
                            {
                                userName = getUserNameByTaskId(mainHdr.getCount());
                                userSock_fd = getSockFd(userName);
                                sendTasksInfo(userSock_fd, userName);
                            }
                            
                            break;
                        }
                        case DELETE_USER:
                        {
                            std::cout << "\t-> DELETE_USER - user name: \"" 
                                        << string(buf) << "\"" << std::endl;
                            deleteUser(string(buf));
                            break;
                        }
                        case ADD_NEW_USER:
                        {
                            std::cout << "\t-> ADD_NEW_USER - user name: \"" 
                                        << LoginHeader(buf).getUserName() << "\"" << std::endl;
                            addNewUser(LoginHeader(buf));
                            sendUsersInfo(admin_fd);
                            break;
                        }
                        case CHANGE_PASSWORD:
                        {
                            std::cout << "\t-> CHANGE_PASSWORD - user name: \"" 
                                        << LoginHeader(buf).getUserName() << "\"" << std::endl;
                            changePassword(LoginHeader(buf));
                            sendUsersInfo(admin_fd);
                            break;
                        }
                        
                    }
                }
                //ОТПРАВЛЯЕМ ФАЙЛЫ
                // cout << "Отправляемые файлы(" << paths.size() << ")" << endl;
                // for (auto el : paths)
                //     cout << "\t" << el << endl;

                // int bytesSent = sendFiles(*it, paths);
                // cout << "Bytes sent: " << bytesSent << endl;
                // cout << "Total bytes sent: " << bytesSent << endl;
            }
        }
    }
    return 0;
}