#include <iostream> 
#include <map>
using namespace std;
int main(void) {
    int la, lb;
    while(cin >> la >> lb) {
        map<int, int> mp;
        for(int i = 0; i < la + lb; i++) {
            int data;
            cin >> data;
            mp[data] = 0;
        }
        for(map<int, int>::iterator iter = mp.begin(); iter != mp.end(); iter++) {
            if(iter != mp.begin()) {
                cout<<" ";
            }
            cout<< iter->first;
        }   
        cout<<endl;
        
    }
    return 0;
}