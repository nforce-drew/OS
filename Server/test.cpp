#include <iostream>
#include <string>

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

int main()
{
    // void* vd;
    //     vd = 0;
    // int *i;
    // int a = 12;
    // i = &a;

    // vd = i;
    int x = 10;
    void *pointer = &x;


    int y = *((int *) pointer);
    std::cout << y << std::endl;

    // std::cout << bytes((char*)vd, sizeof(void*)) << std::endl;

    return (0);
}