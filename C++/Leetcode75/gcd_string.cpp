#include <iostream>
#include <string>

using namespace std;

string gcdOfStrings(string str1, string str2) {
    int len1 = str1.length();
    int len2 = str2.length();

    // Check if str1 + str2 is equal to str2 + str1
    if (str1 + str2 != str2 + str1) {
        return "";
    }

    // Find the greatest common divisor (substring)
    for (int i = min(len1, len2); i > 0; i--) {
        if (len1 % i == 0 && len2 % i == 0) {
            string divisor = str1.substr(0, i);

            // Check if divisor divides both strings
            bool isDivisor = true;
            for (int j = 0; j < len1; j += i) {
                if (str1.substr(j, i) != divisor) {
                    isDivisor = false;
                    break;
                }
            }
            for (int k = 0; k < len2; k += i) {
                if (str2.substr(k, i) != divisor) {
                    isDivisor = false;
                    break;
                }
            }

            if (isDivisor) {
                return divisor;
            }
        }
    }

    return "";
}

int main() {
    // Example usage:
    string str1_example1 = "ABCABC";
    string str2_example1 = "ABC";
    cout << gcdOfStrings(str1_example1, str2_example1) << endl;  // Output: "ABC"

    string str1_example2 = "ABABAB";
    string str2_example2 = "ABAB";
    cout << gcdOfStrings(str1_example2, str2_example2) << endl;  // Output: "AB"

    string str1_example3 = "LEET";
    string str2_example3 = "CODE";
    cout << gcdOfStrings(str1_example3, str2_example3) << endl;  // Output: ""

    std::cout<<gcdOfStrings("ABCDEF","ABC")<<std::endl;
    return 0;
}
