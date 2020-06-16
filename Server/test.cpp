#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <chrono>

using namespace std;

void threadFunction(list<string>* lst)
{
    auto it = lst->begin();
    std::advance(it, 1);
    std::cout << *it << "\t" << std::this_thread::get_id() << std::endl;
}
 
int main()
{
    string str = "hello world and people";

    int i;
    string change = "_";
    for (int j = 0; j < str.length() - 1; j++)
    {
        i = str.find(" ");
        if(i == j)
        str.replace(i, change.length(), change);
    }
    // while (it != str.end())
    // {
    //     auto it = str.find(" ");
    // }
    cout << str;
    
    // str.replace()
    return 0;
}