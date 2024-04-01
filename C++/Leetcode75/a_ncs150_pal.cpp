#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPal(string str){
    vector<char> sanit;
    for(char ch:str){
        if(ch!=' '){
            if((ch >='a' && ch<='z')||(ch >='0' && ch<='9')){
                sanit.push_back(ch);
            }
            else if(ch >='A' && ch<='Z'){
                sanit.push_back(ch-'A'+'a');
            }
        }
    }
    int len = sanit.size();
    int count = 0;

    for(char ch : sanit){
        cout<<"["<<ch<<"]";
    }

    for(int i=0; i<len;i++){
        if(sanit[i]==sanit[len-1-i]){
            count++;
        }
        else{
            return false;
        }
    }

    // cout<<count<<len;
    return (count==len);
}

int main(){
    // cout<<isPal("A man, a plan, a canal: Panama");
    cout<<isPal("0P");
    return 0;
}