// Given an integer array nums and an integer k, return true
// if there are two distinct indices i and j in the array such
// that nums[i] == nums[j] and abs(i - j) <= k.



#include <iostream>
#include <vector>
using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    for(int i=0; i<nums.size(); i++){
        for(int j=1; (j<=k && (i+j)<nums.size()); j++){
            if(nums[i]==nums[i+j]){
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<int> nums = {1,2,3,1};
    int k = 3;
    cout<<containsNearbyDuplicate(nums,k);
    return 0;
}
