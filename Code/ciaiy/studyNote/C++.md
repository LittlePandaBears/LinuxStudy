#c++ 面试知识点总结
## 11-21
 - 虚函数表

    用于多态， 在每个类的内存最开始地方， 都有一个虚函数表， 存放着虚函数指针，[父类虚函数]，[子类虚函数]
    若子类实现了父类虚函数， 则直接替代掉父类虚函数的数据。
    若没加vitrual， 则要看具体是什么类型进行调用该函数的， 父类指针调用父函数， 子类指针调用子函数
    ```C++
    #include <iostream>

    using namespace std;

    class A {
        public :
            virtual void funA1() {
                cout << "A1" << endl;
            }

            void funA2() {
                cout << "A2" << endl;
            }
    };

    class B : public A{
        public:
            virtual void funA1 () {
                cout << "B1" << endl;
            }
            void funA2() {
                cout << "B2" << endl;
            }
    };

    int main(void) {
        A *a = new B();
        B *b = new B();
        a->funA1();
        a->funA2();
        b->funA1();
        b->funA2();
    }

    /* 
        输出：
        B1
        A2
        B1
        B2
    */ 

    ```

 - 智能指针和普通指针的区别， 以及四个智能指针
    1. 普通指针存在忘记调用析构函数的风险， 会造成内存泄漏。
    智能指针会在作用域结束的时候自动调用析构函数。
    2. 四种智能指针

        1. auto_ptr : 独占， 存在p1 = p2的问题， 如果程序员不加注意就调用复制后的p2， 会出现问题。
        2. unique_ptr: 独占， 不存在p1 = p2的问题， 若要赋值，要写成p1 = move(p2)形式， p2指向为空。 
        3. shared_ptr: 共享， 会维护一个use_count， 当use_count为0时， 进行析构。 存在死锁的问题。 p1和p2互相指向的时候， p1 和 p2 的usec_count都为2。
        4. weak_ptr: 共享， 并且不会让use_count增加。

        在使用智能指针的时候， 推荐使用make_shared< T >(t)来进行赋值。

 - 析构函数
    
    当对象的生存周期结束的时候， 会自动调用该函数进行收尾工作。 一般来说析构函数都是虚函数， 因为防止当有子类继承它， 一个父类指针指向的析构函数只能析构父类的内存空间，从而导致内存泄漏（原因看上个问题）。

 - 四种类型转换
     - static_cast： 一般来说， 用于各种隐式转换， 例如 非const->const, void* -> int*， 也可以向上转型， 但不保证向下转型是否成功。（向上转换：指的是子类向基类的转换；向下转换：指的是基类向子类的转换）
     - dynamic_cast： 用于具有虚函数的类之间的， 向上转换和向下转换。 只能转指针或引用。
     - const_cast： 去掉const
     - reinterpret_cast：啥都能转换， 少用。

 - 内存分布图
    1. 环境变量区
    2. 堆
    3. 栈
    4. 静态变量去
    5. 代码区（包括常量区）

    栈的默认大小可以通过``ulimit``来查看和修改

 - C++中拷贝赋值函数的形参不能进行值传递

    不能。如果是这种情况下，调用拷贝构造函数的时候，首先要将实参传递给形参，这个传递的时候又要调用拷贝构造函数。。如此循环，无法完成拷贝，栈也会满。

## 11-22

 - Linux进程间通讯技术：
    - Unix套接字
    - 信号量
    - 无名管道
    - 文件锁
    - 共享内存

 - 死锁
    1.有序分配锁资源可以预防死锁

    2. 银行家算法是用于``避免``死锁的

- 顺序容器删除元素， 后部元素会向前移动， 因此要注意下标的指向

- 类的大小
    - 空类为1
    - 虚函数为4（有了虚函数， 就不需要1字节了）

    对象大小  =  虚函数指针  +   所有非静态数据成员大小   +   因对齐而多占的字节

 - 若父类析构函数没有加vitrual， 则子类无法析构其父类空间

## 11-24

 - atomic 原子操作 **C11标准**
    在一个一个来, 谁也别抢, 急也没用. 只要用于对内存数据的原子保护.

 - 可变参数模板

    ```C++
    template<typename T, typename Args>
    void fun(T head, Args... args) {
        cout << head << endl;
        fun(args...);
    }

    template<typename T>
    void fun() {
        cout << "end" << endl;
    }
    ```

- RTTI（Run-Time Type Identification)

    通过运行时类型信息程序能够使用基类的指针或引用来检查这些指针或引用所指的对象的实际派生类型。

 - ``右值！！！`` （``**超重要**``）

    右值分为纯右值（也就是临时变量）和将亡值。 
    举个例子： 
    ```C++
        Copyable ReturnRvalue() {
            return Copyable(); 
        }
        void AcceptRef(const Copyable& a) {

        }
    ```
    此时的Copyable()的返回值就是一个右值， 因为如果不加以利用， 它就消失了。 我们可以通过右值引用来让它的生命周期延长。（``左值引用会报错， 但是 常量左值引用 没有问题， 常量左值引用是一个很万能的类型``）。 

    **那为什么不能使用 -> Copyable a <- 来接受参数呢**

    回答： 
    
    当使用Copyable a来接受参数的话， 会执行两次构造函数。 而使用引用类型， 只会执行一次构造函数。 （使用-fno-elide-constructors 来关闭返回值优化）

     - ``移动构造函数``
    
        有时候一些生成的临时字符串，我们可以使用右值引用来提高效率。
         
         - 普通参数

            两次构造函数， 效率最慢
         - 左值引用

            一次构造函数， 但是还是会拷贝， 类似于ctrl+c ctrl+v
         - 右值引用

            一次构造函数， ‘窃取’掉原来的数据， 类似于ctrl+x ctrl+v

    - ``通用引用``

        ```C++
            template<typename T>
            void fun(T&& t) {
                // code
            }
        ```
        
        这里的&&是一个未定义的引用类型，称为universal references，它必须被初始化，它是左值引用还是右值引用却决于它的初始化，如果它被一个左值初始化，它就是一个左值引用；如果被一个右值初始化，它就是一个右值引用。

    - ``完美转发``

        ```C++
        // 一个不完美转发的例子
        void myforward(int&& i){
            cout << "myforward(int&&):" << i << endl;
            process(std::forward<int>(i));
        }

        myforward(2); // process(int&&):2
        ```
        上述代码可以转发右值， 但是不可以转发左值。 可以通过通用引用来解决

        ```C++
        template<typename T>
        void myforward(T &&i) {
            process(std::forward<T> (t))
        }
        ```
