#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <errno.h>

std::string fileName(std::string pathname);
std::string pathWithoutName(std::string pathname);
std::string fileExtension(std::string pathname);
std::string fileNameWithoutExtension(std::string pathname);

int main(int argc, char *argv[])
{
    std::cout << "===ZIP STARTED===" << std::endl;
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
        std::cout << "===ZIP ENDED===" << std::endl;
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
        std::cout << "===ZIP ENDED===" << std::endl;
        return (0);
    }
    std::getline(fin_solInfo, solFolderPath);
    fin_solInfo.close();
    std::list<std::string> solutions;
    for (auto path : pathesLst)
    {
        command = "cp " + path + " " + solFolderPath;
        
        // solFilePath = std::string(solFolderPath) + "/" 
        //     + fileName(std::string(solFolderPath)) + ".zip";
        // command = "cd " + pathWithoutName(std::string(path))
        //     + "; zip -r " + solFilePath + " " + fileName(std::string(path));
        std::cout << command << std::endl;
        system(command.c_str());
        command = "cd " + solFolderPath + ";";
        std::string newName = fileNameWithoutExtension(fileName(path)) + "\\(ПЕРЕИМЕНОВАН\\)"
                + "." + fileExtension(fileName(path)); 
        command += "mv " + fileName(path) + " "
                + newName;
        std::cout << command << std::endl;
        system(command.c_str());
        solutions.push_back(solFolderPath + "/" + fileNameWithoutExtension(fileName(path)) + "(ПЕРЕИМЕНОВАН)"
                + "." + fileExtension(fileName(path)));
    }
    fout_solInfo.open(std::string(argv[2]), std::ios_base::trunc);
    if (!fout_solInfo.is_open())
    {
        std::cerr << "File opening error: " << std::string(argv[2])
                    << ". Errno: " << errno << std::endl;
        std::cout << "===ZIP ENDED===" << std::endl;
        return (0);
    }
    int i = 0;
    for (auto file : solutions)
    {
        fout_solInfo.write(file.c_str(), file.size());
        if (solutions.size() - 1 != i)
            fout_solInfo.write("\n", 1);
        i++;
    }
    fout_solInfo.close();
    std::cout << "===ZIP ENDED===" << std::endl;
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

std::string fileExtension(std::string pathname)
{
    int dotPos = pathname.find('.');
    std::string extension(pathname, dotPos + 1, pathname.size() - dotPos);

    return (extension);
}

std::string fileNameWithoutExtension(std::string pathname)
{
    int dotPos = pathname.find('.');
    std::string name(pathname, 0, dotPos);

    return (name);
}