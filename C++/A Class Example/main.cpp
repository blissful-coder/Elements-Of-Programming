#include "animal.cpp"

int main(){
    Animal obj1;
    obj1.viewMe();
    Animal obj2("Dog");
    obj2.viewMe();
    Animal obj3("Cow","Black",7);
    obj3.viewMe();
    Animal obj4(obj3);
    obj4.viewMe();
}