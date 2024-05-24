#include <iostream>
#include <vector>
using namespace std;

int equalsum(const vector<int> a){
    int res = -1;
    int j = a.size()-1;
    vector<int> pre(j);
    int presum = 0;
    vector<int> suff(j);
    int sufsum = 0;
    for(int i=0; i<a.size(); i++){
        // cout<<i<<":"<<j-i<<endl;
        presum = presum + a[i];
        sufsum = sufsum + a[j-i];
        // cout<<presum<<":"<<sufsum<<endl;
        pre[i] = presum;
        suff[j-i] = sufsum;
    }

    for(int i=0; i<a.size(); i++){
        // cout<<pre[i]<<":"<<suff[i]<<endl;
        if(pre[i]==suff[i]){
            res = i;
        }
    }
    // cout<<res<<endl;
    return res;
}


int main(){
    vector<int> prob1{2,4,5,6,0};
    int res = equalsum(prob1);
    cout<<prob1[res]<<endl;
    vector<int> prob2{2,3,5,2,4,3,2,1};
    res = equalsum(prob2);
    cout<<prob2[res]<<endl;
    return 0;
}