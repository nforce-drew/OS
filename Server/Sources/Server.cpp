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
using namespace std;

#define BUF_SIZE    1024
#define PORT_NUMBER 5307

int admin_fd;

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
//=================================================================================
int main(const int argc, const char** argv)
{
    int     listener;
    struct  sockaddr_in addr;
    char    buf[BUF_SIZE];
    int     bytes_read;
    string  query;

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
    cout << currentTimeInfo() << endl;

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
                        break;
                    }
                    case SEND_FILES:
                    {
                        cout << "\t-> SEND_FILES - count files: " << lst->size() << endl;
                        if (admin_fd != -1)
                            sendQueue(admin_fd);
                        // cout << "Отправляемые файлы(" << lst->size() << ")" << endl;
                        for (auto el : *lst)
                            cout << "\t\t" << el << endl;
                        delete lst;
                        break;        
                    }
                    case QUEUE_LIST:
                    {
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
                        break;
                    }
                    case RECONNECT:
                    {
                        std::cout << "\t-> RECONNECT - user name: \"" 
                                    << buf << "\"" << std::endl;
                        std::cout << bytes(buf, 20) << std::endl;
                        addOnlineUser(*it, std::string(buf));
                        break;
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