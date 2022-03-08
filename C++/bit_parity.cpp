#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
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

// short Parity3(unsigned long x){
//     const int kWordSize = 16;
//     const int kBitMask = 0xFFFF;
//     return  precomputed_parity[x >> (3* kWordSize) ] ^
//             precomputed_parity[(x >> (2* kWordSize)) & kBitMask] ^
//             precomputed_parity[(x >> kWordSize) & kBitMask] ^
//             precomputed_parity[x & kBitMask];
// }

short Parity4(unsigned long x){
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;

    return x&0x1;
}

void SwapBits(long x, int i, int j){
    cout << "\nNumber is: " << bitset<16>(x) << endl;
    if (((x>>i)&1) != ((x>>j)&1)){
        unsigned long bit_mask = (1L<<i) | (1L<<j);
        cout << "\nBitmask  : " << bitset<16>(bit_mask) << endl;
        x ^= bit_mask;
    }
    cout << "\nNumber is: " << bitset<16>(x) << endl;
}

/* TODO
find MSB and LSB and use SwapBits to swap indexes. (remember reversing array)
void ReverseBits(long x){
    cout << "\nNumber is: " << bitset<16>(x) << endl;
    int numLSB = x & ~(x-1);
    cout << "\nNumber is: " << bitset<16>(numLSB) << endl;
    int BITS = sizeof(long);
    cout<< "\n BITS is: " << BITS << endl;
    int numMSB = 1<< (BITS-1);
    cout << "\nNumber is: " << bitset<16>(numMSB) << endl;
    

}
*/

void ClosestIntSameBitCount (unsigned long x){
    const int kNumUnsignBits = 64;
    cout << "\nNumber is: " << bitset<16>(x) << endl;
    for (int i =0; i<kNumUnsignBits -1 ; i++){
        if (((x>>i)&1) != ((x>>(i+1))&1)){
            x ^= (1UL << i) | (1UL<<(i+1) );
        }
    }
    cout << "\nNumber is: " << bitset<16>(x) << endl;
}

void schoolDivision(string dividend, string divisor){
    cout<<"\n"<<dividend<<" divided by "<< divisor << " is: "<<endl;
}

int main(){
    unsigned long val = 8;
    cout<< "Parity of number: " << bitset<16>(63) << " is " << Parity1(63) << endl;
    cout<< "Parity of number: " << bitset<16>(0xFFFF) << " is " << Parity2(0xFFFF) << endl;
    cout<< "Parity of number: " << bitset<64>(0xFFFE) << " is " << Parity4(0xFFFE) << endl;
    cout<< "Parity of number: " << bitset<64>(0xFFFE) << " is " << Parity4(0xFFFE) << endl;
    SwapBits(367, 7, 5);
    // ReverseBits(366);
    ClosestIntSameBitCount(366);
    schoolDivision("63812638","6372");
}