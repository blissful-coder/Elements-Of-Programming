#include <iostream>

using namespace std;

void pdt_size(){
    cout << "Size of char : " << sizeof(char)<< " byte" << endl;
    cout << "Size of int : " << sizeof(int)<< " bytes" << endl;
    cout << "Size of short int : " << sizeof(short int)<< " bytes" << endl;
    cout << "Size of long int : " << sizeof(long int) << " bytes" << endl;
    cout << "Size of signed long int : " << sizeof(signed long int) << " bytes" << endl;
    cout << "Size of unsigned long int : " << sizeof(unsigned long int) << " bytes" << endl;
    cout << "Size of long long : " << sizeof(long long) << " bytes" <<endl;
    cout << "Size of float : " << sizeof(float) << " bytes" <<endl;
    cout << "Size of double : " << sizeof(double) << " bytes" << endl;
    cout << "Size of wchar_t : " << sizeof(wchar_t) << " bytes" <<endl;

}

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
    cout<<"\n---Data Type size---"<<endl;
    pdt_size();
}