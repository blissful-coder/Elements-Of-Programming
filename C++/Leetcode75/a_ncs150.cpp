#include <iostream>
#include <unordered_set>

using namespace std;

int find_max_series(vector<int> nums){
        unordered_set<int> s;
        
         //dump all elements into set
        for(int num : nums){
            s.insert(num);
        }
        
        
        int ans = 0;
        for(int num : nums){
            //check if previous_element is not in set
            //then current number is the beginning
            if(s.find(num-1) == s.end()){
                int currentElement = num;
                int count = 1;
                
                //start a chain from current element
                while(s.find(currentElement+1) != s.end()){
                    currentElement++;
                    count++;
                }
                ans = max(ans, count);
            }
        }
        return ans;
}

int main(){
    vector<int> a{1,2,3,0,4,5,6,7,8,9,0,3,4,5,6,7,8,9};
    cout<<find_max_series(a);
    return 0;
}