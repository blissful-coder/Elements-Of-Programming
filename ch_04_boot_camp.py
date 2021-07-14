def number_to_binary(x):
    b_str = ""
    while x:
        b_str += str(x&1)
        x >>= 1
    return b_str[::-1]

def count_bits(x):
    num_bits = 0
    while x:
        num_bits += (x&1)
        x >>= 1
    
    return num_bits

for i in range(20):
    print("Number is {}, binary is {} and bit-count is {}".format(i,number_to_binary(i),count_bits(i)))