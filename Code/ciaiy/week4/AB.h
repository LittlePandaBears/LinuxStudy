#ifndef AB_H_
#define AB_H_

class A {
    public :
        A() {}
        ~A() {}
        A(int a, int b);

    private :
        int a;
        int b;
};

class B : public A {
    public :
        B() {}
        ~B() {}
        B(int a, int b);


};

#endif // !AB_H_