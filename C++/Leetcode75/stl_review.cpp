#include <iostream>
#include <vector>
#include <set>

using namespace std;
int main(){
    vector<int> a = {1,2,3,4,5}; //--std=c++11
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    cout<<"\n";
    for(int i=0; i<a.size();i++){
        cout<<a[i];
    }

    set<int> st = {1,2,3,4,5}; //--std=c++11
    st.insert(6);
    st.insert(6);
    st.insert(8);
    st.insert(9);
    cout<<"\n";
    for(int elem: st){
        cout<<elem;
    }

    return 0;
}