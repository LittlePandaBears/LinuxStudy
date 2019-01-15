#include <iostream>
#include <cstring>

using namespace std;

long long int dp[100][100];
char lista[100], listb[100];

int main(void) {
    while(cin>>lista>>listb) {
        for(int i = 0; i < strlen(lista); i++) {
            for(int j = i; j < strlen(listb); j++) {
                if(lista[i] == listb[j]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
                }else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<dp[strlen(lista) - 1][strlen(listb) - 1]<<endl;
    }
    return 0;
}