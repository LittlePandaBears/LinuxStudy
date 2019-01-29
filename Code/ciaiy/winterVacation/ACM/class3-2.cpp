#include <iostream>
#include <queue>
using namespace std;
class node {
    public:
    int data, num;
    node(int data, int num) {
        this->data = data;
        this->num = num;
    }
};
int main(void) {
    int indexl, target;
    while(cin >> indexl >> target) {
        int list[1000000] = {0};
        queue<node> que;
        que.push(node(indexl, 0));
        while(!que.empty()) {
            node index = que.front();
            que.pop();
            // cout<<index.data<<endl;
            if(index.data < 0 || index.data > 1000000 || list[index.data] == 1) {
                continue;
            }else {
                list[index.data] = 1;
            }
            if(index.data != target) {
                que.push(node(index.data + 1, index.num + 1));
                que.push(node(index.data - 1, index.num + 1));
                que.push(node(index.data * 2, index.num + 1));
            }else {
                cout<<index.num<<endl;
                break;
            }
        }
    }   

    return 0;
}