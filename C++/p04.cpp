#include <iostream>

using namespace std;

void fun_swap(int a, int b){
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
}

void fun_swap_without_var(int a, int b){
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
    a = a^b;
    b = a^b;
    a = a^b;
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
}

void fun_swap_without_var_tersely(int a, int b){
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
    a ^= b ^= a ^= b;
    cout<<"Numbers are: "<<a<<" and "<<b<< endl;
}

int main(){
    cout<<"---With variables---"<<endl;
    fun_swap(4,3);
    cout<<"\n---Without variables---"<<endl;
    fun_swap_without_var(56,43);
    cout<<"\n---Without variables Tersely---"<<endl;
    fun_swap_without_var_tersely(232,123);
}