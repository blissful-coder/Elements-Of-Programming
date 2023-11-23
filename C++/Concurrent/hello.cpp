#include <iostream>
#include <thread>

void dot()
{
    for (int i=1; i<500; i++)
        std::cout << ".";
}

void dash()
{
    for (int i=1; i<500; i++)
        std::cout << "-";
}

void symbol(char sym)
{
    for (int i=1; i<500; i++)
        std::cout << sym;
}

int main()
{
    std::thread hello_t(dot);
    std::thread world_t(dash);
    std::thread hash_t(symbol,'#');
    std::thread plus_t(symbol,'+');

    hello_t.join();
    world_t.join();
    hash_t.join();
    plus_t.join();

    return 0;
}