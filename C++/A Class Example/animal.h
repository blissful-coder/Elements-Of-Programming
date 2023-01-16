#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include <inttypes.h>

class Animal{
    private:
        std::string name;
        std::string color;
        uint8_t age; 

    public:
        Animal();
        Animal(std::string name);
        Animal(std::string name, std::string color, uint8_t age);
        Animal(Animal &obj);
        ~Animal();
        void viewMe();
};

#endif