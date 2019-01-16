#include <iostream>
using namespace std;
int main(void) {
    int len;
    while(cin >> len) {
        int list[len] = {0};
        int num;
        cin >> num;
        for(int i = 0; i < len; i++) {
            cin >> list[i];
        }
        while(num--) {
            bool flag = true;
            int left, right;
            cin >> left >> right;
            int sum = list[left - 1];
            for(int i = left; i < right; i++) {
                if(sum % 2 == 1) {
                    flag = false;
                    break;
                }
                sum += list[i];
            }           
            if(flag) {
                cout << "Sim"<<endl;
            }else {
                cout<< "Nao"<<endl;
            }
        }
    }
}