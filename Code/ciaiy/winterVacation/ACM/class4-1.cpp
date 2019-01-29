#include <iostream>
#include <stack>
using namespace std;
int main(void) {
    int num;
    cin >> num;
    while(num--) {
        string list;
        getline(cin, list);
        stack<char> st;
        bool flag = true;
        for(int i = 0; i < list.size(); i++) {
            if(list[i] == '(' || list[i] == '[') {
                st.push(list[i]);
            }else if(list[i] == ')' || list[i] == ']'){
                if(st.empty()) {
                    flag = false;
                    break;
                }
                if((list[i] == ')' && st.top() == '(') || (list[i] == ']' && st.top() == '[')) {
                    st.pop();
                }else {
                    flag = false;
                    break;
                }
            }
        }
        if(!st.empty()) {
            flag = false;
        }
        if(flag) {
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}