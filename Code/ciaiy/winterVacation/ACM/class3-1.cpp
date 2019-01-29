#include <iostream>
#include <cstring>
using namespace std;
int sum = 0;
int h, l;
char map[10000][10000] = {0};
char table[10000][10000] = {0};
void dfs(int indexi, int indexj)
{
    if (indexi < 0 || indexi >= h)
    {
        return;
    }
    if (indexj < 0 || indexj >= l)
    {
        return;
    }
    if (map[indexi][indexj] != '#'  && map[indexi][indexj] != '*')
    {
        map[indexi][indexj] = '*';
        sum++;
        // cout<<endl;
        // for(int i = 0; i < h; i++) {
        //     for(int j = 0; j < l; j++) {
        //         cout<<map[i][j];
        //     }
        //     cout<<endl;
        // }
        dfs(indexi - 1, indexj);
        dfs(indexi + 1, indexj);
        dfs(indexi, indexj + 1);
        dfs(indexi, indexj - 1);
    }
}
int main(void)
{
    while (cin >> l >> h)
    {
        memset(map, 0, h * l * sizeof(char));
        memset(table, 0, h * l * sizeof(char));
        if(h == 0 && l == 0) {
            break;
        }
        sum = 0;
        int indexi ;
        int indexj ;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < l; j++)
            {
                cin >> map[i][j];
                if(map[i][j] == '@') {
                    indexi = i;
                    indexj = j;
                }
            }
        }
        dfs(indexi, indexj);
        cout << sum<<endl;
    }
    return 0;
}