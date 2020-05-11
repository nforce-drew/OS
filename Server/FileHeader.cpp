#include "FileHeader.h"

FileHeader::FileHeader()
{

}

FileHeader::FileHeader(unsigned fileSize, char *fileName)
{
    this->fileSize = fileSize;
    strncpy(this->fileName, fileName, 64);
}

unsigned    FileHeader::getFileSize()
{
    return (this->fileSize);
}

char*       FileHeader::getFileName()
{
    return (this->fileName);
}

FileHeader  FileHeader::setByteArr(char* byteArr)
{
    for (int i = 0; i < sizeof(*this); i++)
        ((char*)this)[i] = byteArr[i];
    return (*this);
}

FileHeader  FileHeader::setData(unsigned fileSize, char *fileName)
{
    this->fileSize = fileSize;
    strncpy(this->fileName, fileName, 64);
}