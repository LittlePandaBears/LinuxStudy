#include "sort.h"

int main(void) {
    SORT s;
    cout<<endl;
    bool flag = true;
    // for(int i = 0; i < 10; i++) {

        s.showList();
        s.sort(SORT::FS);
        flag = s.check();
        if(flag == false) {
            cout << "false" << endl;
            s.showList();
        }
        s.showList();//) }
    return 0;
}