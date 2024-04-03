#include <iostream>
#include <unordered_set>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int max = 0;
    int len = s.size();
    int i=0;
    while(i<len){
        unordered_set <char> temp;
        int count=0;
        int j=i;
        while(j<len){
            if(temp.find(s[j])==temp.end()){
                temp.insert(s[j]);
                // cout<<s[j];
                count++;
            }
            else{
                break;
            }
            if(count>max){
                max = count;
            }
            j++;
        }
        // cout<<"\n";
        i++;
    }
    return max;
}

int main(){
    cout<<lengthOfLongestSubstring("abcabcbb");
    cout<<lengthOfLongestSubstring("bbbbb");
    cout<<lengthOfLongestSubstring("pwwkew");
    return 0;
}