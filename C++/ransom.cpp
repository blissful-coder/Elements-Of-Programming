// Given two strings ransomNote and magazine, 
// return true if ransomNote can be constructed by using 
// the letters from magazine and false otherwise.
// Each letter in magazine can only be used once in ransomNote.
// Example 1:

// Input: ransomNote = "a", magazine = "b"
// Output: false
// Example 2:

// Input: ransomNote = "aa", magazine = "ab"
// Output: false
// Example 3:

// Input: ransomNote = "aa", magazine = "aab"
// Output: true


#include <iostream>
#include <map>
using namespace std;

bool canConstruct(string ransomNote, string magazine) {
    map<char,int> mag;
    for(int i=0; i<magazine.size(); i++){
        if(mag.find(magazine[i])!=mag.end()){
            mag[magazine[i]] = mag[magazine[i]] + 1;
        }
        else{
            mag[magazine[i]] = 1;
        }
    }
    map<char,int> ran;
    for(int i=0; i<ransomNote.size(); i++){
        if(ran.find(ransomNote[i])!=ran.end()){
            ran[ransomNote[i]] = ran[ransomNote[i]] + 1;
        }
        else{
            ran[ransomNote[i]] = 1;
        }
    }

    for(int i=0; i<ransomNote.size(); i++){
        if(ran[ransomNote[i]]>mag[ransomNote[i]]){
            return false;
        }
    }

    return true;
}

int main() {
    cout<<canConstruct("a","b")<<endl;
    cout<<canConstruct("aa","ab")<<endl;
    cout<<canConstruct("aa","aab")<<endl;
    return 0;
}
