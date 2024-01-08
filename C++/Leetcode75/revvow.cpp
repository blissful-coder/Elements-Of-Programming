#include <iostream>


bool check(char c){
    c = tolower(c);
    return (c=='a'|| c=='e'|| c=='i'|| c=='o'|| c=='u');
}

std::string reverseVowels(std::string s) {
    const int VLIST_SZ = 10;
    std::vector <char> v;
    std::vector <int> vi;

    for(int i=0; i<s.size(); i++){
        if(check(s[i])){
            // std::cout<<s[i];
            v.push_back(s[i]);
            vi.push_back(i);
        }
    }

    reverse(v.begin(),v.end());
    for(int i=0; i<v.size(); i++){
        s[vi[i]] = v[i];
    }

    return s;
}

int main(){
    std::cout<<reverseVowels("hello")<<std::endl;
    std::cout<<reverseVowels("leetcode")<<std::endl;
    std::cout<<reverseVowels("anurag")<<std::endl;
    std::cout<<reverseVowels("vijay")<<std::endl;
    return 0;
}