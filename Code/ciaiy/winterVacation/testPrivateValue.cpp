#include <iostream> 
class test {
    public:
        test(int x) : a(x) {}
    private:
        int a;
};

int main(void) {
    test a = test(12);
    return 0;
}