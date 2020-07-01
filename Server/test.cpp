#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <chrono>
#include <fstream>
#include <unistd.h>



using namespace std;

void threadFunction(list<string>* lst)
{
    auto it = lst->begin();
    std::advance(it, 1);
    std::cout << *it << "\t" << std::this_thread::get_id() << std::endl;
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

int main()
{
    // string str = "hello world and people";

    // int i;
    // string change = "_";
    // for (int j = 0; j < str.length() - 1; j++)
    // {
    //     i = str.find(" ");
    //     if(i == j)
    //     str.replace(i, change.length(), change);
    // }
    // // while (it != str.end())
    // // {
    // //     auto it = str.find(" ");
    // // }
    // cout << str;
    // std::string filePath = "/home/nspace/OS/Server/Solutions/who_2020-06-30_17:25:51/who_2020-06-30_17:25:51.zarp";
    // std::cout << fileExtension(filePath) << std::endl;
    // std::cout << fileNameWithoutExtension(filePath) << std::endl;
    
    // char* args[] = {"./b.out", "", "", NULL};
    // std::cout << "Вызывает" << std::endl;
    // execvp("./b.out", args);
    // std::cout << "Продолжил" << std::endl;
    // str.replace()
    ofstream fout;
    fout.open("./myfile.txt");
    if (fout.is_open())
    {
        std::cout << "Файл открыт!" << std::endl;
    }
    else
        std::cout << "Error!" << std::endl;
    return 0;
}