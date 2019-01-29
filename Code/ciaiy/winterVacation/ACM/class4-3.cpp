#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    string str;
    while(cin >> str) {
        vector<int> vec;
        int data = 0;
        str += "5";
        for(int i = 0; i < str.size(); i++) {
            if(str[i] != '5') {
                data = data * 10 + (str[i] - '0');
            }else if(str[i - 1] != '5'){
                cout << "*" << data<<endl;
                vec.push_back(data);
                data = 0;
            }
        }
        sort(vec.begin(), vec.end());
        for(vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter ++) {
            if(iter != vec.begin()) {
                cout<<" ";
            }
            cout<<*iter;
        }
        cout<<endl;
    }
    return 0;
}