#include <iostream>
using namespace std;
long long int list[1000], table[1000];
int main(void)
{
    int num;
    cin >> num;
    int max = 0;
    for (int i = 1; i <= num; i++)
    {
        cin >> list[i];
    }
    for (int i = 1; i <= num; i++)
    {
        max = 0;
        for (int j = 1; j <= i; j++)
        {
            if (i == j)
            {
                table[i]++;
            }
            if (list[i] > list[j])
            {
                table[i] = (table[i] > table[j]) ? table[i] : table[j];
            }
        }
    }
    for(int i = 1; i <= num; i++) {
        if(max < table[i]) {
            max = table[i];
        }
    }
    cout << max << endl;
    return 0;
}