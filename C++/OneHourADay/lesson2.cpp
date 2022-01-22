#include <iostream>
#include <string>
using namespace std;


 // Function declaration and definition
int DemoConsoleOutput()
{
   cout << "This is a simple string literal" << endl;
   cout << "Writing number fiv " << 5 << endl;
   cout << "Performing division 10 / 5 = " << 10 / 5 << endl;
   cout << "Pi is 22 / 7 = " << 22.0 / 7 << endl;

   return 0;
}

void DemoconsoleInput(){
   string name;
   int num;

   cout << "Enter your name: ";
   cin >> name;
   cout << "Enter your favorite number: ";
   cin >> num;

   cout << name << " entered number " << num << "." << endl;
}


#define funx(x) x*x

int fun(int x){
   return (x*x);
}

int main()
{
 // Function call with return used to exit
   DemoConsoleOutput();
   DemoconsoleInput();
   cout << funx(10+2) << endl;
   cout << fun(10+2) << endl;
   return 0;
}