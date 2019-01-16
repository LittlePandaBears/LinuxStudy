#include <iostream>
using namespace std;
long long int list[100000];
int main(void) {
    int num;
    while(cin >> num) {
        for(int i = 0; i < num; i++) {
            cin >> list[i];
        }
        num = num + 1;
        for(int i = 0;; i++) {
            if((1<<i) == num) {
                cout<<i<<endl;
                break;
            }
            if((1 << i) < num && num < (1 << (i + 1))) {
                cout<<i + 1<<endl;
                break;
            }
        }
    }
    return 0;
}