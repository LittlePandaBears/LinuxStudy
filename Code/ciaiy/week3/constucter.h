#ifndef CONSTUCTER_H_
#define CONSTUCTER_H_

#include <iostream>

class constucter {
    public:
        constucter();
        constucter(std::string name);
        ~constucter();
        void getOtherObjectPrivateValue(const constucter &otherObject) const;
        constucter returnType1();
        std::string name;

    private:
        int pri_val;
};

#endif
