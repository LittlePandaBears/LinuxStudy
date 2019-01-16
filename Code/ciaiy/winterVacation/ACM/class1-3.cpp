#include <iostream>
using namespace std;
long long int  table[100];
int main(void)
{
    int num;
    cin >> num;
    while (num--)
    {
        int a, b;
        cin >> a >> b;
        for (int i = 1; i <= b - a + 1; i++)
        {
            if (table[i] != 0)
            {
                continue;
            }
            else if (i == 0)
            {
                table[i] = 0;
                continue;
            }
            else if (i == 1 || i == 2)
            {
                table[i] = 1;
                continue;
            }
            else
            {
                table[i] = table[i - 1] + table[i - 2];
            }
        }
        cout<<table[b - a + 1]<<endl;
    }
    return 0;
}