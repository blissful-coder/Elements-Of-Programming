#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    int i=0 , j=nums.size()-1;
    vector<int> v(2);

    while(i<=j){
        if(nums[i]+nums[j]==target){
            v[0] = i+1;
            v[1] = j+1;
            return v;
        }
        else if(nums[i]+nums[j] > target) j--; 
        else i++;
    }

    return {0 , 0};        
}

int main(){
    vector<int> q={1,2,3,4};
    twoSum(q,6);
    return 0;
}