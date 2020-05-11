#ifndef FILEHEADER_H
#define FILEHEADER_H

#include <string.h>

class FileHeader
{
private:
    unsigned    fileSize;
    char        fileName[64];

public:
    FileHeader();
    FileHeader(unsigned fileSize, char *fileName);
public:
    unsigned    getFileSize();
    char*       getFileName();
    FileHeader  setByteArr(char* byteArr);
    FileHeader  setData(unsigned fileSize, char *fileName);
};

#endif // FILEHEADER_H
