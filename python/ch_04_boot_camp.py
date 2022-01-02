def opt_parity(x):
    result = 0
    while x:
        result ^= 1
        x &= x-1
    
    return result

def parity(x):
    parity = 0
    while x:
        parity ^= x & 1
        x >>= 1
    return parity

def number_to_binary(x):
    b_str = ""
    if(x==0):
        return "0"
    while x:
        b_str += str(x&1)
        x >>= 10
    return b_str[::-1]

def count_bits(x):
    num_bits = 0
    while x:
        num_bits += (x&1)
        x >>= 1
    
    return num_bits

for i in range(20):
    print("Number is {}, binary: {}, bit-count: {},  parity: {}, opt_parity: {}".format(i,number_to_binary(i),count_bits(i),parity(i), opt_parity(i)))


# Fun Shuffle
import random
A = [  "Mickey",
        "John",
        "Mick",
        "Snow",
        "Sheldon",
        "Vijay",
        "Gomba"
]

random.shuffle(A)
print(A)