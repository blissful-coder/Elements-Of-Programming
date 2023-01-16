#include "animal.h"

Animal::Animal(){
    name = "Demo";
    color = "NoColor";
    age = 0;
}

Animal::Animal(std::string name){
    this->name = name;
}

Animal::Animal(std::string name, std::string color, uint8_t age){
    this->name = name;
    this->color = color;
    this->age = age;
}

Animal::Animal(Animal &obj){
    this->name = obj.name;
    this->color = obj.color;
    this->age = obj.age;
}

Animal::~Animal(){
    std::cout<<"Deleting Object\n";
}

void Animal::viewMe(){
    std::cout<<"Name:"<<this->name<<"\n";
    std::cout<<"Age:"<<(unsigned)this->age<<"\n";
    std::cout<<"Color:"<<this->color<<"\n";
}