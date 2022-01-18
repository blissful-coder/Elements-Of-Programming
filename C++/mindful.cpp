#include <iostream>

using namespace std;


void printline(int n){
    int i=1;
    for(i=1; i<=n; i++){
        cout<<"* ";
    }
}

void printgap(int n){
    int i=1;
    for(i=1; i<=n; i++){
        cout<<" ";
    }
}

void fun1(int a){
    cout<<"\n\n Pattern1\n";
    for(int i=1; i<=a; i++){
        printline(i);
        cout<<"\n";
    }
}

void fun2(int a){
    cout<<"\n\n Pattern2\n";
    for(int i=1; i<=a; i++){
      for(int j=1; j<a; j++){
            if(j==1 || j==a || j==i || j==(a-i+1))
                cout<<"*";
            else if(i==1 || i==a)
                cout<<"*";
            else
                cout<<".";
      }
      cout<<"*\n";
    }
}

void fun3(int a){
    cout<<"\n\n Pattern3\n";
    for(int i=1; i<=a; i++){
        printgap(i);
        printline(a);
        cout<<"\n";
    }
}


int main(){
    fun1(9);
    fun2(16);
    fun3(10);
    return 0;
}