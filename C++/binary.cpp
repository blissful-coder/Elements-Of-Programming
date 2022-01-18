#include <iostream>
#include <vector>

using namespace std;

int BinSearchRec(vector<int> arr, int l, int r, int target);
int BinSearchIte(vector<int> arr, int l, int r, int target);

int main(){
    vector<int> test = {1,2,3,4,5,6,7,8,9};
    for(int i=-8; i<=13; i++){
        cout<<"Searching: " << i << " Result: ";
        if(BinSearchRec(test,0,9,i)!=-1)
            cout<<"Found"<<endl;
        else
            cout<<"Not Found"<<endl;
    }
    return 0;
}

int BinSearchRec(vector<int> arr, int l, int r, int target){
    if(r<l){
        return -1;
    }
    int mid = l + (r - l)/2;
    if(arr[mid]>target)
        return BinSearchRec(arr, l, mid-1, target);
    else if (arr[mid]<target)
        return BinSearchRec(arr, mid+1, r, target);
    
    return mid;
}


int BinSearchIte(vector<int> arr, int l, int r, int target){
    if(r<l){
        return -1;
    }
    int mid = l + (r - l)/2;
    if(arr[mid]>target)
        return BinSearchRec(arr, l, mid-1, target);
    else if (arr[mid]<target)
        return BinSearchRec(arr, mid+1, r, target);
    
    return mid;
}