#ifndef EF_H_
#define EF_H_

#include <iostream>

using std::cout;
using std::endl;

class E
{

  public:
    int data;
    E()
    {
        data = 123;
        cout << "new object" << endl;
    }

    E(int data)
    {
        this->data = data;
        cout << "new object data : " << data << endl;
    }

    E& operator+(const E e)
    {
        this->data = this->data + e.data;
        return *this;
    }

    void show() const {
        cout << "data : " << data << endl;
    }

    void modify(int data) {
        this->data = data;
    }
};

#endif // !EF_H_
