#include <iostream>

int main()
{
    std::cout << "Начал" << std::endl;
    for (int i = 0; i < 1999999; i++);
    std::cout << "Закончил" << std::endl;
    return (0);
}