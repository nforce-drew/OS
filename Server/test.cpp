#include <iostream>
#include <string>
#include <list>
#include <ctime>
using namespace std;
std::string bytes(const char *buf, int size)
{
    std::string message;
    for (int i = 0; i < size; i++)
    {
        message += std::to_string((int)buf[i]) + " ";
        if ((i + 1) % 4 == 0)
            message += "| ";
    }
    return (message);
}

void func(void* data)
{
    list<string>* lst = (list<string>*)data;
    

    lst->push_back("first");
    lst->push_back("second");
    data = (void*)lst;
    cout << lst->size() << endl;
}


int main()
{
    // void* data;
    // list<char*>* lst = new list<char*>;
    // data = (void*)lst;
    // func(data);


    // list<string>* lst2;
    // std::cout << lst->size() << std::endl;
    // lst2 = (list<string>*)data;
    // for(auto el : *lst2)
    // {
    //     cout << el << endl;
    // }
    // int a;

    // a = 2*2;

    // char str[a];


    list<string>* lst = new list<string>;
    

    lst->push_back("first");
    lst->push_back("second");
    lst->push_back("third");

    auto it = lst->begin();
    advance(it, 2);
    cout << *it;


    // vd = i;
    // int x = 10;
    // void *pointer = &x;


    // int y = *((int *) pointer);
    // std::cout << y << std::endl;

    // std::cout << bytes((char*)vd, sizeof(void*)) << std::endl;

    return (0);
}