#include <iostream>
#include <string>
#include <list>
#include <ctime>
// #include "TaskHeader.h"
using namespace std;
// std::string bytes(const char *buf, int size)
// {
//     std::string message;
//     for (int i = 0; i < size; i++)
//     {
//         message += std::to_string((int)buf[i]) + " ";
//         if ((i + 1) % 4 == 0)
//             message += "| ";
//     }
//     return (message);
// }

// void func(void* data)
// {
//     list<TaskHeader>* lst = (list<TaskHeader>*)data;
//     TaskHeader taskHeader;

//     taskHeader.setData(1, (char*)"ivan", 1, (char*)"time1");
//     lst->push_back(taskHeader);
//     taskHeader.setData(2, (char*)"peter", 2, (char*)"time2");
//     lst->push_back(taskHeader);
//     data = (void*)lst;
//     cout << lst->size() << endl;
// }


int main()
{
    // void* data;
    // list<string>* lst = new list<string>;
    // data = (void*)lst;
    // func(data);


    // list<TaskHeader>* lst2;
    
    // lst2 = (list<TaskHeader>*)data;
    // std::cout << lst2->size() << std::endl;
    // for(auto el : *lst2)
    // {
    //     cout << el.getUserName() << endl;
    // }
    std::cout << (int)((unsigned char)(-100)) << std::endl;
    // int a;

    // a = 2*2;

    // char str[a];


    // list<string>* lst = new list<string>;
    

    // lst->push_back("first");
    // lst->push_back("second");
    // lst->push_back("third");

    // auto it = lst->begin();
    // advance(it, 2);
    // cout << *it;


    // vd = i;
    // int x = 10;
    // void *pointer = &x;


    // int y = *((int *) pointer);
    // std::cout << y << std::endl;

    // std::cout << bytes((char*)vd, sizeof(void*)) << std::endl;

    return (0);
}