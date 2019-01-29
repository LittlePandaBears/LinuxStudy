#include <iostream>
#include <queue>
int map[10000][10000];
int now = 0;
class node {
    public:
    int x, y, num;
    node(int x, int y, int num) {
        this->x = x;
        this->y = y;
        this->num = num;
    }
};
int main(void) {
    int h, l, in;
    while(cin >> h >> l>>in) {
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < l; j++) {
                cin>>map[i][j];
            }
        }
        queue<node> que;
        que.push(node(0, in - 1, 1));
        while(!que.empty() && flag) {
            node now = que.front();
            que.pop();
            switch (map[now.x][now.y]) {
                case 'N' : 
                que.push(node(now.x, now.y - 1, now.data + 1));
                break;
                case 'S' :
                que.push(node(now.x, now.y + 1, now.data + 1));
                break;
                case 'W' :
                que.push(node(now.x - 1, now.y, now.data + 1));
                break;
                case 'E' :
                que.push(node(now.x + 1, now.y, now.data + 1));
                break;
                default :
                que.push(node(now.x, now.y, now.data));
                flag = false;
            }
                map[now.x][now.y] = now.data;
            }
        }

    }
    return 0;
}