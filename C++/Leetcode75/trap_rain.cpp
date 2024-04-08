// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// Explanation: The above elevation map (black section) is represented by array
// [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
// are being trapped.
// Input: height = [4,2,0,3,2,5]
// Output: 9

#include <iostream>
#include <vector>

using namespace std;

int brut(vector<int> &height){
    int count =0;
    for(int i=0; i<height.size(); i++){
        int maxL=0;
        int maxR=0;
        for(int li=i; li>=0; li--){
            if(height[li]>maxL)    maxL = height[li];
        }
        for(int ri=i; ri<height.size(); ri++){
            if(height[ri]>maxR)    maxR = height[ri];
        }

        if((min(maxL,maxR) - height[i]) > 0)
            count = count + min(maxL,maxR) - height[i];
    }
    return count;
}

int brutxfixsum(vector<int> &height){
    int count =0;
    vector<int> prefixsum;
    vector<int> suffixsum;
    int premax = 0;
    for(int i=0; i<height.size(); i++){
        if(height[i]>premax){
            premax = height[i];
        }
        prefixsum.push_back(premax);
    }
    int suffmax = 0;
    for(int i=height.size()-1; i>=0; i--){
        if(height[i]>suffmax){
            suffmax = height[i];
        }
        suffixsum.push_back(suffmax);
    }
    reverse(suffixsum.begin(),suffixsum.end());
    // cout<<"\nPREFIXSUM:"<<endl;
    // for(int elem:prefixsum){
    //     cout<<elem<<" ";
    // }
    // cout<<"\nSUFFIXSUM:"<<endl;
    // for(int elem:suffixsum){
    //     cout<<elem<<" ";
    // }
    // cout<<"\n--------------"<<endl;
    for(int i=0; i<height.size(); i++){
        if((min(prefixsum[i],suffixsum[i]) - height[i]) > 0)
            count = count + min(prefixsum[i],suffixsum[i]) - height[i];
    }
    return count;
}

int myWay(vector<int> &height){
    int done=0;
    int count=0;
    int i=0;
    int len=height.size();
    int j = len;

    while(i<j){
        if(height[i]>0 && height[j]>0){
            int reducer = min(height[i],height[j]);
            for(int k=i+1; k<j;k++){
                if(height[k]<reducer){
                    count = count + (reducer - height[k]);
                }
            }
            for(int k=0; k<len; k++){
                height[k] = height[k] - reducer;
                cout<<height[k]<<",";
            }
            cout<<"\n";
            i=0;
            j=len;
        }
        for(int k=0; k<len; k++){
            if(height[k]<=0){
                done++;
            }
        }
        if(done>=len)
            break;
        
        if(height[i]<height[j] || height[i]<=0){
            i++;
        }
        else{
            j--;
        }
        cout<<i<<":"<<j<<endl;
    }

    return count;
}

int main(){
    vector<int> q1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> q2 = {4,2,0,3,2,5};
    // cout << myWay(q1);
    cout << brut(q1)<<endl;
    cout << brut(q2)<<endl;
    cout << brutxfixsum(q1)<<endl;
    cout << brutxfixsum(q2)<<endl;
    return 0;
}
