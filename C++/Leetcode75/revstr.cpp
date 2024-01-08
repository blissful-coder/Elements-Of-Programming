#include <iostream>

std::string sanitizeString(std::string s){
    std::string sanitized = "";
    std::string final = "";

    int start_index=0;
    int end_index=0;

    //remove all spaces from beginning
    int i=0;
    while(i<s.size() && s[i]==' '){
        i++;
    }
    start_index=i;
    //remove all spaces from beginning
    int j=s.size()-1;
    while(j>=0 && s[j]==' '){
        j--;
    }
    end_index = j;

    sanitized = s.substr(i,j-i+1);
    //change all multiple spaces to single space in sanitized string
    i=0; j=0;
    while(i<sanitized.size()){
        if(sanitized[i]==' '){
            final += sanitized[i];
            j=i+1;
            while(sanitized[j]==' ' && j<sanitized.size()){
                j++;
            }
            i = j;
        }
        else{
            final += sanitized[i];
            i++;
        }
    }

    return final;
}

std::vector<std::string> tokenizeString(std::string s, char delimiter){
    std::vector<std::string> res;
    std::string temp;

    int i=0; 
    while(i<s.size()){
        if(s[i]!=delimiter){
            temp+=s[i];
        }
        else{
            res.push_back(temp);
            temp="";
            res.push_back(" ");
        }

        i++;
    }

    if(temp!="" && temp!=" "){
        res.push_back(temp);
    }

    return res;
}

std::string mergeTokens(std::vector <std::string> listoftokens){
    std::string res;
    std::cout<<"\n";
    for(int i=listoftokens.size()-1; i>=0; i--){
        std::cout<<"|"<<listoftokens[i]<<"|";
        res += listoftokens[i];
    }
    return res;
}

std::string reverseWords(std::string s) {
    return mergeTokens(tokenizeString(sanitizeString(s),' '));
}

int main(){
    reverseWords("         the sky is blue        ");
    reverseWords("  hello world  ");
    reverseWords("a good   example        ");
    reverseWords("   Another      sample String");
    return 0;
}