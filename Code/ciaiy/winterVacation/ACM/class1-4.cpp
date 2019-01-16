#include <iostream>
#include <cstring>
using namespace std;
long long int dp[100][100], table[100][100];
int main(void) {
    int num;
    cin >> num;
    while(num--) {
        bzero(dp, sizeof(dp));
        bzero(table, sizeof(table));
        int level;
        cin >> level;
        for(int i = 1; i <= level; i++) {
            for(int j = 0; j < i; j++) {
                cin >> dp[i][j];
            }
        }

        for(int i = level; i >= 1; i--) {
            for(int j = 0; j < i; j++) {
                // cout<<dp[i][j] << ":";
                table[i][j] = dp[i][j] + (table[i + 1][j] > table[i + 1][j + 1] ? table[i + 1][j] : table[i + 1][j + 1]);
                // cout<<table[i][j]<<" ";
            }
            // cout<<endl;
        }
        cout<<table[1][0]<<endl;
    }
    return 0;
}