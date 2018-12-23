#ifndef G_H_
#define G_H_

#include <iostream>

using std::cout;
using std::endl;

class G {
    public :
    G() {}
        G(int str) {
            cout << str << endl;
            this->str = str;
        }
        // G(const G &temp) {
        //     this->data = 222;
        // }
        // // void operator=(int data) {
        //     this->data = data;
        // }
        // void operator=(const G &temp) {
        //     this->data = 111;
        // }
        void show(void) const {
            cout << "data : " << data << endl;
            cout << "str : " << str << endl;
        }
    private :
        int str;
        int data;
};

#endif