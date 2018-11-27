
# 胖迪的C++学习笔记

## 说明

``本笔记记录的知识点并不局限于C++语法知识``

---

## 初识类和对象

### 为什么有些地方的函数声明加着const

首先这个函数一定是一个``成员方法``， 其次``这个函数一定不会修改调用对象``。 这种方法我们称之为*const成员方法*。 只要类方法不修改调用对象， 就应该将其定义为const成员方法， 这是一个良好的变成习惯。

### 函数参数的 & 有什么用处

这个代表了参数是以引用的方式来传参的， 这种传参方式有些类似于指针， ``在方法里修改值等同于修改作为参数传递的变量的值``。

### cout<<timeSum<<endl 为什么会报错

虽然我们使用 frined void operator<<(std::ostream &os, t_time &time) 这个友元函数了， 但是值得注意的是， 在此函数的实现中， 我们使用的是``os<<time.hours<<time.minutes``。因此``cout<<timeSum;``这句话是没有问题的， 但是加上endl就有问题了， 我们并``没有定义t_time和endl之间的<< 重载``。

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

### 为什么一个类的方法中， 可以访问参数(数据类型为该类)的私有变量

因为C++的``访问控制是class-level``， 而不是object-level
对于同一个类， 他们的访问控制权限是一样的， 只要是成员方法， 且有同类的参数， 都可以访问其私有变量

### C++虚函数介绍

#### 举个小栗子

现在我们假设有两个类: **class A**, **class B : public A**. 
给出两个类的定义：

```

class A {
    public :
        A();
        ~A();
        void Fun() {
            std::cout << "这是A类" << std::endl;
        }
};

class B : public A {
    public :
        B();
        ~B();
        void Fun() {
            std::cout << "这是B类" << std::endl;
        }
};

```

下面的代码会发生什么？

```

int main(void) {
    A *p = new B();
    p->Fun();   // 输出的是A类还是B类？
}

```

``输出结果： 这是A类``

输出的结果令人意外， 如果想要让它执行B类的Fun()， 只需要在A类的Fun函数声明前面加入virtual(**``这并不是一个好习惯``**).
这个virtual的功能是让这个函数变成``虚函数``.

#### 虚函数的简介

 虚函数： 是C++多态性的一种实现， 它可以通过指向``派生类``的``基类指针``或``引用``访问被派生类覆盖的同名函数

#### 虚函数的实现

由于这两个类中有虚函数的存在， 因此编译器就会为这两个类插入一段数据， 并分别他们创建一个表， 数据叫做vptr指针, vptr指向的表叫做vtbl. vtbl里面存放的是所在类的虚函数的地址

Fun函数的调用并不会像普通的函数一样跳转到函数的代码处，而是先取出vptr的值， 在vtbl中找到Fun的地址， 然后在进行调用. 因此你甚至可以将B类里vtbl里关于Fun的地址替换成A类的, 这样p->Fun() 就重新显示为“这是A类”.

#### 总结

可以讲虚函数是函数的``纵向重载``, 让基类指针指向的同名函数能在派生类群中选择执行哪个， 而通常意义的重载则是横向重载即在不同参数的同名函数中选择.