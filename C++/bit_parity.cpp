#include <iostream>

using namespace std;

short Parity1(unsigned long x){
    short result = 0;
    while(x){
        result ^= (x&1);
        x>>=1;
    }
    return result;
}

int main(){
    unsigned long val = 8;

    cout<< "Parity of number: " << val << " is " << Parity1(val) << endl;
}