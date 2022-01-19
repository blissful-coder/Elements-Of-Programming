#include <iostream>
#include <bitset>
using namespace std;

short Parity1(unsigned long x){
    short result = 0;
    while(x){
        result ^= (x&1);
        x>>=1;
    }
    return result;
}

short Parity2(unsigned long x){
    short result = 0;
    while(x){
        result ^= 1;
        x= x&(x-1);
        //cout<<"\nx: "<<x<<" result: "<<result;
    }
    return result;
}

int main(){
    unsigned long val = 8;
    cout<< "Parity of number: " << bitset<16>(21) << " is " << Parity1(21) << endl;
    cout<< "Parity of number: " << bitset<16>(21) << " is " << Parity2(21) << endl;
}