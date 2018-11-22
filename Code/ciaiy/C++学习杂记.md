
# 胖迪的C++学习笔记

## 说明

``本笔记记录的知识点并不局限于C++语法知识``

---

[toc]

## 初识类和对象

### 为什么有些地方的函数声明加着const

首先这个函数一定是一个``成员方法``， 其次``这个函数一定不会修改调用对象``。 这种方法我们称之为*const成员方法*。 只要类方法不修改调用对象， 就应该将其定义为const成员方法， 这是一个良好的变成习惯。

### 函数参数的 & 有什么用处

这个代表了参数是以引用的方式来传参的， 这种传参方式有些类似于指针， ``在方法里修改值等同于修改作为参数传递的变量的值``。

### cout<<timeSum<<endl 为什么会报错

虽然我们使用 frined void operater<<(std::ostream &os, t_time &time) 这个友元函数了， 但是值得注意的是， 在此函数的实现中， 我们使用的是``os<<time.hours<<time.minutes``。因此``cout<<timeSum;``这句话是没有问题的， 但是加上endl就有问题了， 我们并``没有定义t_time和endl之间的<< 重载``。

**``改进方式 : ``** 我们只需要将返回值改变为``ostream``就可以实现``cout<<timeSum<<endl``

### 类中怎么写函数才能使它变成内联函数

 - 声明的时候添加inline标识符 ``(显式声明)``
    
    ```
     public :
        inline void testFun();
    ```
 - 添加inline的声明加实现 ``(显式声明)``
    
    ```
    public :
        inline void testFun() {
            std::cout << "this is inline Fun" << std::endl;
        }
    ```
 - 函数在声明的同时实现 ``(隐式声明)``
    
    ```
    public :
        void testFun(){
            std::cout << "this is inline Fun" << std::endl;
        }
    ```

**``注意 ：以下方式不能定义为inline函数``**

    ```
    public :
        void testFun();

    inline void testFun() {
        std::cout << "this is not inline Fun" << std::endl;
    }
    ```





