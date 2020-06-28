#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <errno.h>

std::string fileName(std::string pathname);
std::string pathWithoutName(std::string pathname);

int main(int argc, char *argv[])
{
    std::list<std::string>  pathesLst;
    std::ifstream           fin_taskInfo;
    std::ifstream           fin_solInfo;
    std::ofstream           fout_solInfo;
    std::string             filePath;
    std::string             solFolderPath;
    std::string             command;
    std::string             solFilePath;

    if (argc != 3)
        return (0);
    fin_taskInfo.open(std::string(argv[1]));
    if (!fin_taskInfo.is_open())
    {
        std::cerr << "File opening error: " << std::string(argv[1])
                    << ". Errno: " << errno << std::endl;
        return (0);
    }
    while (!fin_taskInfo.eof())
    {
        std::getline(fin_taskInfo, filePath);
        std::cout << filePath << std::endl;
        pathesLst.push_back(filePath);
    }
    fin_taskInfo.close();
    fin_solInfo.open(std::string(argv[2]));
    if (!fin_solInfo.is_open())
    {
        std::cerr << "File opening error: " << std::string(argv[2])
                    << ". Errno: " << errno << std::endl;
        return (0);
    }
    std::getline(fin_solInfo, solFolderPath);
    fin_solInfo.close();
    for (auto path : pathesLst)
    {
        solFilePath = std::string(solFolderPath) + "/" 
            + fileName(std::string(solFolderPath)) + ".zip";
        command = "cd " + pathWithoutName(std::string(path))
            + "; zip -r " + solFilePath + " " + fileName(std::string(path));
        std::cout << command << std::endl;
        system(command.c_str());
    }
    fout_solInfo.open(std::string(argv[2]));
    if (!fout_solInfo.is_open())
    {
        std::cerr << "File opening error: " << std::string(argv[2])
                    << ". Errno: " << errno << std::endl;
        return (0);
    }
    fout_solInfo.write(solFilePath.c_str(), solFilePath.size());
    fout_solInfo.close();
    return (0);
}

std::string pathWithoutName(std::string pathname)
{
    const size_t last_slash_idx = pathname.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        pathname.erase(last_slash_idx, pathname.size() - last_slash_idx + 1);
    }
    return (pathname);
}

std::string fileName(std::string pathname)
{
    const size_t last_slash_idx = pathname.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        pathname.erase(0, last_slash_idx + 1);
    }
    return (pathname);
}