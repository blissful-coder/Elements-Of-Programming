// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
// determine if the input string is valid.
// An input string is valid if:

// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.

// Example 1:

// Input: s = "()"
// Output: true
// Example 2:

// Input: s = "()[]{}"
// Output: true
// Example 3:

// Input: s = "(]"
// Output: false

#include <iostream>
#include <stack>
#include <map>
using namespace std;

bool isValid(string s) {
    stack<char> test;
    map<char,char> corr;
    corr[')'] = '(';
    corr[']'] = '[';
    corr['}'] = '{';

    for(int i=0; i<s.size(); i++){
        if(s[i]=='(' || s[i]=='[' || s[i]=='{'){
            // cout<<"char: "<<s[i]<<endl;
            test.push(s[i]);
            // cout<<"Pushed to STACK TOP: "<<test.top()<<endl;
        }
        else{
            // cout<<"char: "<<s[i]<<endl;
            if(!test.empty()){
                // cout<<"Trying POP"<<test.top()<<":"<<corr[s[i]]<<endl;
                if(test.top()==corr[s[i]]){
                    test.pop();
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
            // cout<<"Do Something"<<endl;
        }
    }

    return test.empty();
}

int main(){
    cout<<isValid("{}[]");
    cout<<isValid("()[]{}");
    cout<<isValid("(]]");
    cout<<isValid("(]");
    cout<<isValid("({{{}");
    return 0;
}
