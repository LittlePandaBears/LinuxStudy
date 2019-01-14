#include <iostream>
using namespace std;
long long V, n, p[1000], v[1000], dp[1000][1000];
int main(void)
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >>n;
        cin>>V;
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i];//权值
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];//重量
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= V; j++)
            {
                if (j >= v[i])
                {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + p[i]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }

            }
        }
        cout<<dp[n][V]<<endl;
    }
}