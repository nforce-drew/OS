#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 1024

//=================================================================================
bool createFile(char *name)
{
    FILE *pFile;
    char path[] = "/home/nforce/CppProjects/";

    pFile = fopen(strcat(path, name), "w+b");
    if (!pFile)
    {
        std:: cout << "Error creating file!" << std::endl;
        return (false);
    }
    fclose(pFile);
    return (true);
}
//=================================================================================
bool appendToFile(char *path, char *buf, int len)
{
    FILE *pFile;

    pFile = fopen(path, "ab");
    if (!pFile)
    {
        std:: cout << "Error opening file!" << std::endl;
        return (false);
    }
    fwrite(buf, 1, len, pFile);
    fclose(pFile);
    return (true);
}
//=================================================================================
int sendAll(int sock, char **buf, int len, int flags)
{
    int total = 0;
    int bytes_read;

    while(total < len)
    {
        bytes_read = recv(sock, *(buf + total), len - total, flags);
        if(bytes_read == -1)
            break;
        total += bytes_read;
    }
    
    return (bytes_read == -1 ? -1 : total);
}
//=================================================================================
int recvAll(int sock, char *buf)
{
    int total = 0;
    int bytes_read;
    char file_name[32];

    char a[] = "testCr.h";
    createFile(a);

    bytes_read = recv(sock, buf, BUF_SIZE, 0);
    total += bytes_read;
    std::cout << "Bytes readed: " << bytes_read << std::endl;
    if (bytes_read < 8)
        return (-1);

    std::cout << "Code: " << ((int*)buf)[0] << std::endl;
    if (((int*)buf)[1] == 1)
    {
        std::cout << "Recv file!\n";
        strncpy(file_name, buf + 12, 32); 
        std::cout << "file_name = " << file_name << std::endl;
        // createFile(file_name);
    }
    else
        std::cout << "Another!\n";


    // while (total < len)
    // {
    //     n = send(s, buf + total, len - total, flags);
    //     if (n == -1)
    //         break;
    //     total += n;
    // }
    std::cout << "Count bytes: " << (bytes_read == -1 ? -1 : total) << std::endl;
    return (bytes_read == -1 ? -1 : total);
}
//=================================================================================
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
     char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(54000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while (1)
    {
        sock = accept(listener, NULL, NULL);
        if (sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while (1)
        {
            // bytes_read = recv(sock, buf, 1024, 0);
            bytes_read = recvAll(sock, buf);
            if (bytes_read <= 0)
                break;
            std::cout << "buf " << bytes_read << std::endl;
            send(sock, buf, bytes_read, 0);
        }
        close(sock);
    }
    
    return 0;
}