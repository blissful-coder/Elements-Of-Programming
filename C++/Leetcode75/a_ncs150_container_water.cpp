// You are given an integer array height of length n. There are n vertical lines drawn such that the two
// endpoints of the ith line are (i, 0) and (i, height[i]).
// Find two lines that together with the x-axis form a container,
// such that the container contains the most water.
// Return the maximum amount of water a container can store.
// Notice that you may not slant the container.
// Input: height = [1,8,6,2,5,4,8,3,7]
// Output: 49

#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) {
    int len = height.size();
    int j = len-1;
    int i = 0;
    int maxArea = 0;
    while(i<j){
        maxArea = max(maxArea, min(height[i],height[j])*(j-i));
        // cout<<i<<","<<j<<":"<<height[i]<<","<<height[j]<<" ["<<maxArea<<"]"<<endl;
        if(height[i]<height[j]){
            i++;
        }
        else{
            j--;
        }
    }

    return maxArea;
}

int main(){
    vector<int> q={1,8,6,2,5,4,8,3,7};
    cout<<maxArea(q);
    return 0;
}
