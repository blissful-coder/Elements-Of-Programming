#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std::chrono_literals;

void RefreshForcast(std::map<std::string, int> forcastMap)
{
    while (true)
    {
        std::cout<<"-------------------"<<std::endl;
        for (auto& item : forcastMap)
        {
            item.second++;
            std::cout << std::right << std::setw(10) << std::setfill(' ') << item.first << " : "<< item.second << std::endl;
        }
        std::this_thread::sleep_for(2000ms);
    }
}

int main()
{
    std::map<std::string, int> forcastMap = {
        {"Newyork", 15},
        {"Mumbai", 20},
        {"Dublin", 18},
        {"Berlin", 17}};

    std::thread bg_worker (RefreshForcast,forcastMap);

    bg_worker.join();
    return 0;
}