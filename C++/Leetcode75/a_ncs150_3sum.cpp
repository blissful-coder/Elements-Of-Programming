// Input: nums = [-1,0,1,2,-1,-4]
// Output: [[-1,-1,2],[-1,0,1]]
// Explanation: 
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets does not matter.

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    set<vector<int>> sub;
    sort(nums.begin(),nums.end());
    for(int i=0; i<nums.size(); i++){
        int j=i+1;
        int k=nums.size()-1;
        while(j<k){
            if(nums[i]+nums[j]+nums[k]==0){
                sub.insert({nums[i],nums[j],nums[k]});
                j++;
                k--;
            }
            if(nums[i]+nums[j]+nums[k]<0){
                j++;
            }
            else{
                k--;
            }
        }
    }
    for(vector<int> triplet: sub){
        result.push_back(triplet);
    }
    return result;
}

int main(){
    vector<int> q={-1,0,1,2,-1,-4};
    vector<vector<int>> ans = threeSum(q);
    for (int i = 0; i < ans.size(); i++) {
        cout<<"["<<ans[i][0]<<","<<ans[i][1]<<","<<ans[i][2]<<"]"<<endl;
    }
    return 0;
}