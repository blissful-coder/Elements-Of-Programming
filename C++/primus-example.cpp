#include <iostream>
#include <string.h>

using namespace std;

void vulnerableFunction(char* input) {
    char buffer[10];
    strcpy(buffer, input);
    cout << buffer;
}

int main() {
    char largeInput[] = "This string is too long for the buffer";
    vulnerableFunction(largeInput);
    return 0;
}