#include "MainHeader.h"
#include "FileHeader.h"
#include "Headers.h"
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
#include <sys/stat.h>
#include <ctime>

using namespace std;

#define     SAVE_PATH   "/home/nspace/OS/Server/Tasks/" // в конце должен быть слэш!!!
#define     BUF_SIZE    1024

string      fileName(string pathname); //(Вспомогательная) Вырезает имя файла из пути

string      currentTimeInfo();
unsigned    appFileData(string folderAndFileName, const char *data, unsigned len); //(Вспомогательная) Добавляет данные в файл
unsigned    appBinData(string folderAndFileName, const char *data, unsigned len);
//recvAll ПРИНИМАЕТ данные в buf, если пришли не файлы.
//в переменную TYPE &dataType возвращает тип данных
//если dataType == SEND_FILES, то в list присвоятся пути к файлам:
int         recvAll(int sock, char *buf, TYPE &dataType, void* data); 
unsigned    getFileSize(string path); //(Вспомогательная) Определяет размер файла
unsigned    getMessageSize(list<string> &paths); //(Вспомогательная) Определяет размер сообщения для заданных файлов
int         sendAll(int sock_fd, char *buf, int len, int flags); //(Вспомогательная) Отправляет файлы из буфера длиной len(flags = 0)
int         sendData(int sock, const MainHeader &mainHdr, char* data, unsigned len); // ОТПРАВЛЯЕТ ЛЮБЫЕ ДАННЫЕ преобразованные к char* с заголовоком 
int         sendFiles(int sock, list<string> &paths); //ОТПРАВЛЯЕТ ФАЙЛЫ, пути к которым передаются в список
char*       onlineUsersToChar(list<string>* lst);
int         sendOnlineUsers(int admin_fd);
int         sendTasksInfo(int sock_fd, string userName);
int         sendUsersInfo(int admin_fd);
int         sendBinsNames(int admin_fd);