#include <iostream>

std::string mergeAlternately(std::string word1, std::string word2) {
    std::string answer = "";
    for (size_t i = 0, j = 0; i < word1.size() || j < word2.size(); i++, j++) {
        if (i < word1.size())
            answer += word1[i];
        if (j < word2.size())
            answer += word2[j];
    }
    return answer;
}

int main(){
    std::cout<<mergeAlternately("Anurag","negi")<<std::endl;
    std::cout<<mergeAlternately("abc","pqr")<<std::endl;
    std::cout<<mergeAlternately("abccdef","pq")<<std::endl;
    std::cout<<mergeAlternately("a","negi")<<std::endl;
    return 0;
}