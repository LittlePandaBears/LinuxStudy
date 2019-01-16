#include <iostream>
using namespace std;
long long n, m, k, s;                                       // 经验, 耐久度, 怪物数量, 最多杀怪数量
long long N[1000], M[1000], dp[1000][1000], km[1000][1000]; // 经验 耐久度 dp 杀怪数量
int main(void)
{
    while (scanf("%d%d%d%d", &n, &m, &k, &s) != EOF)
    {
        for (int i = 1; i <= k; i++)
        {
            cin >> N[i] >> M[i];
        }
        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                
                km[i][j] = km[i][j - M[i]] + 1;
                if(km[i][j] <= s) {
                    continue;
                }
                if (j >= M[i])
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - M[i]] + N[i]);
                    cout << dp[i][j] << " ";
                    continue;
                }
                dp[i][j] = dp[i - 1][j];

                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        bool flag = true;
        for (int i = 1; i <= m; i++)
        {
            if (dp[k][i] >= n)
            {
                cout << m - i << endl;
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << "-1" << endl;
        }
    }
    return 0;
}