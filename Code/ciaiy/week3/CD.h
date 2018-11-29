#ifndef CD_H_
#define CD_H_

class C {
    public :
        C(int a, int b);
        C();
        ~C();
        void showData();
        virtual void Fun() const;
        virtual void Fun(int i) const;
        virtual void Fun(char ch) const;
    private :
        int a;
        int b;
};

class D : public C {
    public :
        D();
        D(int a, int b);
        ~D();
        virtual int Fun(double d) const;
};

#endif