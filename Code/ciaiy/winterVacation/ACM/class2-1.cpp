#include <iostream>
using namespace std;

int main(void) {
    int num;
    cin >> num;
    while(num--) {
        long long int a, b;
        bool flag = false;
        cin >>a >> b;
        long long int  r = 1;
        if(a < b) {
            long long int temp = b;
            b = a;
            a = temp;
        }
        // cout << a << " " << b<<endl; 
        while(r!=0)
        {
            r=a%b;
            a=b;
            b=r;
        }
        if(a != 1) {
            cout<<"Sim"<<endl;
        }else {
            cout << "Nao"<<endl;
        }
    }
}