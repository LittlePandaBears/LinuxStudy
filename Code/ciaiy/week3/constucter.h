#ifndef CONSTUCTER_H_
#define CONSTUCTER_H_

#include <iostream>

class constucter {
    public:
        constucter();
        constucter(int n = 0) {
            std::cout << "(int n  = " << n << ")构造函数" << std::endl;
        }
        ~constucter();
        void getOtherObjectPrivateValue(const constucter &otherObject) const;

    private:
        int pri_val;
};

#endif
