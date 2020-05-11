#include "MainHeader.h"
#include "FileHeader.h"
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

#define SAVE_PATH   "/home/nforce/Desktop/Server/"
#define BUF_SIZE    1024

//=================================================================================
void create_file(string name)
{
    fstream fout;

    fout.open(SAVE_PATH + name, ios_base::app | ios_base::trunc);
    if (fout.is_open())
        cout << "File is open." << endl;
    else
        cout << "File is not open." << endl;
    fout.close();
}
//=================================================================================
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
unsigned app_file_data(string name, const char *data, unsigned len)
{
    ofstream    Err; //

    Err.open("/home/nforce/Desktop/Server/err.txt", ios_base::app); //
    if (!Err.is_open()) //
        cout << "Файл для ошибок не открыт!\n"; //
    ofstream fout;

    fout.open(SAVE_PATH + name, ios_base::app);
    if (fout.is_open())
        Err << "File is open.\n";
    else
    {
        Err << "ERROR. Файл для записи не открыт!\n";
        return (0);
    }
    fout.write(data, len);
    fout.close();
    Err << "В ФАЙЛ БЫЛО ДОПИСАН: " << len << " БАЙТ!" << endl;;
    return (len);
}
//=================================================================================
char* byte_n_cpy(char* dist, char* src, unsigned n)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = src[i];
    }
    return (dist);
}
//=================================================================================
int recvAll(int sock, char *buf)
{
    int         bytes_read;
    unsigned    total_bytes;
    unsigned    block_bytes;
    unsigned    cur_bytes;
    unsigned    bytes_write;
    string      filename;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    ofstream    Err; //

    Err.open("/home/nforce/Desktop/Server/err.txt", ios_base::app); //
    if (!Err.is_open()) //
        cout << "Файл для ошибок не открыт!" << endl; //
    total_bytes = 0;
    Err << "RECVALL" << endl;
    while (total_bytes < sizeof(MainHeader))
    {
        bytes_read = recv(sock, buf + total_bytes, BUF_SIZE - total_bytes, 0);
        if (bytes_read <= 0)
        {
            Err << "Error: recvAll() bytes_read <= 0" << endl;
            return (bytes_read);
        }
        total_bytes += (int)bytes_read;
        Err << "bytes_read 0: " << bytes_read << endl;
    }
    
    mainHeader.setByteArr(buf);

    cur_bytes = sizeof(MainHeader);
    block_bytes = total_bytes;
    Err << "0 block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
    Err << mainHeader.getType() << "==" << SEND_FILES << endl;
    if (mainHeader.getType() == SEND_FILES)
    {
        Err << "k block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
        for (int i = 0; i < mainHeader.getCount(); i++)
        {
            while (block_bytes - cur_bytes < sizeof(FileHeader))
            {
                Err << "1 block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
                memcpy(buf, buf + cur_bytes, block_bytes - cur_bytes);
                block_bytes = block_bytes - cur_bytes;
                cur_bytes = 0;
                bytes_read = recv(sock, buf + block_bytes, BUF_SIZE - block_bytes, 0);
                if (bytes_read <= 0)
                {
                    Err << "Error: recvAll() bytes_read <= 0" << endl;
                    return (bytes_read);
                }
                total_bytes += bytes_read;
                block_bytes += bytes_read;
                Err << "bytes_read 1: " << bytes_read << endl;
            }
            Err << "3 block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
            fileHeader.setByteArr(buf + cur_bytes);
            Err << "FILEHEADER: " <<fileHeader.getFileSize() << " " << fileHeader.getFileName()<<endl;
            cur_bytes += sizeof(FileHeader);
            bytes_write = 0;
            Err << "4 block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
            while (bytes_write != fileHeader.getFileSize())
            {
                if ((cur_bytes == block_bytes))
                {
                    cur_bytes = 0;
                    block_bytes = 0;

                    bytes_read = recv(sock, buf, BUF_SIZE, 0);
                    if (bytes_read <= 0)
                    {
                        Err << "Error: recvAll() bytes_read <= 0" << endl;
                        return (bytes_read);
                    }
                    total_bytes += (int)bytes_read;
                    block_bytes = (int)bytes_read;
                    Err << "bytes_read 2: " << bytes_read << endl;
                }
                Err << bytes(buf, 140) << endl;
                Err << "5 block: " << block_bytes << " cur: " << cur_bytes << " write: " << bytes_write << endl;
                if ((block_bytes - cur_bytes) <= (fileHeader.getFileSize() - bytes_write))
                {
                    Err << "www" << endl;
                    bytes_write += app_file_data(fileHeader.getFileName(), 
                                                buf + cur_bytes, block_bytes - cur_bytes
                                                );
                    cur_bytes += block_bytes - cur_bytes;
                }
                else
                {
                    int new_bytes_write;

                    Err << "www222" << endl;
                    new_bytes_write = fileHeader.getFileSize() - bytes_write;
                    bytes_write += app_file_data(fileHeader.getFileName(), 
                                                buf + cur_bytes, new_bytes_write
                                                );
                    cur_bytes += new_bytes_write;
                }
                
            }
        }
    }
    return (total_bytes);
}
//=================================================================================
unsigned file_size(string path)
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
//=================================================================================
unsigned message_size(list<string> &paths)
{
    unsigned msgSize;
    unsigned fileSize;

    msgSize = sizeof(MainHeader);
    for(string filePath : paths)
    {
        msgSize += (unsigned)sizeof(FileHeader);
        fileSize = file_size(filePath);
        if (fileSize == 0)
            return (0);
        msgSize += fileSize;
    }
    return (msgSize);
}
//=================================================================================
int send_files(int sock, list<string> &paths)
{
    char        buf[BUF_SIZE];
    ifstream    fin;
    streampos   begin, end;
    MainHeader  mainHeader;
    FileHeader  fileHeader;
    unsigned    freeBytes;
    unsigned    curByte;
    unsigned    readBytes;
    int         sendBytes;
    int         totalBytes;   

    paths.push_back("/home/nforce/Desktop/scrn14.png");
    paths.push_back("/home/nforce/Desktop/scrn15.png");
    paths.push_back("/home/nforce/Desktop/scrn16.png");
    paths.push_back("/home/nforce/Desktop/scrn17.png");
    paths.push_back("/home/nforce/Desktop/scrn18.png");

    totalBytes = 0;
    mainHeader.setData(message_size(paths), paths.size(), SEND_FILES);
    memcpy(buf, (char*)&mainHeader, sizeof(MainHeader));
    curByte = (unsigned)sizeof(MainHeader);
    freeBytes = (unsigned)BUF_SIZE - (unsigned)sizeof(MainHeader);
    for(string filePath : paths)
    {
        fin.open(filePath);
        if (!fin.is_open())
        {
            cout << "sendSolution: file " << filePath << " wasn't open. Errno: " << errno << endl;
            return (0);
        }
        else
        {
            cout << "File " << filePath << " was opened for sending!" << endl;
        }
        memcpy(buf + curByte, (char*)&fileHeader, sizeof(FileHeader));
        curByte += sizeof(FileHeader);
        freeBytes -= (unsigned)sizeof(fileHeader);
        readBytes = 1; //чтобы зайти в цикл
        while (readBytes)
        {
            readBytes = (unsigned)fin.readsome(buf + curByte, freeBytes);
            freeBytes -= readBytes;
            cout << "bytes read: " << readBytes << " free bytes: " << freeBytes << endl;
            if (freeBytes == 0)
            {
                sendBytes = send(sock, buf, (unsigned)BUF_SIZE - freeBytes, 0);
                totalBytes += sendBytes;
                cout << "SEND BYTES: " << sendBytes << endl;
                freeBytes = (unsigned)BUF_SIZE;
                curByte = 0;
            }
        }
        fin.close();
    }
    if (freeBytes != 0)
    {
        sendBytes = send(sock, buf, (unsigned)BUF_SIZE - freeBytes, 0);
        totalBytes += sendBytes;
        cout << "SEND BYTES: " << sendBytes << endl;
        freeBytes = (unsigned)BUF_SIZE;
        curByte = 0;
    }
    cout << "msg info:" << mainHeader.getMsgSize() << " " << mainHeader.getCount() << " " << mainHeader.getType() << endl;
    return (totalBytes);
}
//=================================================================================
int main()
{
    int listener;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    fcntl(listener, F_SETFL, O_NONBLOCK);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 2);
    
    set<int> clients;
    clients.clear();

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
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        // Ждём события в одном из сокетов
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if(select(mx + 1, &readset, NULL, NULL, &timeout) <= 0)
        {
            perror("select");
            cerr << "Errno: " << errno << endl;
            exit(3);
        }
        
        // Определяем тип события и выполняем соответствующие действия
        if(FD_ISSET(listener, &readset))
        {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
                exit(3);
            }
            cout << "New client connected." << endl;
            fcntl(sock, F_SETFL, O_NONBLOCK);

            clients.insert(sock);
        }

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if (FD_ISSET(*it, &readset))
            {
                // Поступили данные от клиента, читаем их
                bytes_read = recvAll(*it, buf);
                if (bytes_read <= 0)
                {
                    // Соединение разорвано, удаляем сокет из множества
                    close(*it);
                    clients.erase(*it);
                    cout << "Connection refused with client." << endl;
                    continue;
                }
                // Отправляем данные обратно клиенту
                // send(*it, buf, bytes_read, 0);
                list<string> list;
                cout << send_files(*it, list) << "TOTAL BYTES: " << endl;
                cout << "The server sent a message to the client." << endl;
            }
        }
    }
    
    return 0;
}