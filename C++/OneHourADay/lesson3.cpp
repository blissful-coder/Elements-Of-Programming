#include <iostream>
 2: using namespace std;
 3:
4: void MultiplyNumbers ()
 5: {
 6:    cout << “Enter the first number: “;
 7:    int firstNumber = 0;
 8:    cin >> firstNumber;
9:
10:    cout << “Enter the second number: “;
11:    int secondNumber = 0;
12:    cin >> secondNumber;
13:
14:    // Multiply two numbers, store result in a variable
15:    int multiplicationResult = firstNumber * secondNumber;
16:
17:    // Display result
18:    cout << firstNumber << “ x “ << secondNumber;
19:    cout << “ = “ << multiplicationResult << endl;
20: }
21: int main ()
22: {
23:    cout << “This program multiplies two numbers” << endl;
24:
25:    // Call the function that does all the work
26:    MultiplyNumbers();
27:
28:    // cout << firstNumber << “ x “ << secondNumber;
29:    // cout << “ = “ << multiplicationResult << endl;
30:
31:    return 0;
32: }