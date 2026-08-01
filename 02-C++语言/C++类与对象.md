# C++类与对象


## C++从零入门学习系列_类与对象

- [一、C++面向对象](#一c面向对象)
- [二、C++中的类](#二c中的类)
- [三、创建对象](#三创建对象)
- [四、访问限定符](#四访问限定符)
- [五、类与对象](#五类与对象)
- [六、成员方法](#六成员方法)
- [七、C++重载](#七c重载)
- [八、说明](#八说明)

学习过 C 语言的，再学习 C++ 相对比较友好一点，对于 C 是基础，C++ 算是方向上的抉择了。

## 一、C++面向对象

C++语言是基于面向对象的，所以尤其四大特性：抽象、封装、继承、多态。

- 抽象：对客观世界，现实实体的一类定义，找到共性；
- 封装：将数据及对数据上的操作捆绑起来；
- 继承：子子孙孙无穷匮也；
- 多态：主要体现在继承，同一事物的不同表现形式。

## 二、C++中的类

C++中的类，与C语言中的结构体类似：

```cpp
struct STU{
  char name[15];
  char id[9];
  double score;
};
```

以上就可以体现封装，将不同的数据类型封装起来，只是没有方法而已；

新的数据类型为：struct STU  a(结构体变量)。

通过类比，可以知道，在C++中通过class定义新的数据类型。

```cpp
class Test{
public:
  void setData(int x){
   data;
   }
private:  
  int data;
};
```

通过类将其封装起来，新的数据类型为Test  a(对象)。

只不过在C语言中叫做结构体，在C++中叫就做类，是一种对事物共性的抽象，比C多了对数据上的操作。

## 三、创建对象

对象：在C中将结构体定义的叫做，结构体变量，在C++中将类定义的叫做对象。

创建对象两种方式：

- 静态创建：Test a; 创建后将对象压栈；
- 动态创建：Test *a = new Test;  其申请的空间在堆上，必须通过delete释放。

## 四、访问限定符

public：公有，protected，保护 private：私有；

C++中，通过对象只能访问一个类的public,   对protected和private修饰的通过对象不能调用。

## 五、类与对象

**深入理解类与对象：当我们定义一个类的时候，相当于规划了一幅蓝图，没有实例化时，是没有空间的，通过类名.data是错误的。**

实例化：Test t1(); 错 这个不会实例化对象t1,因为这是函数声明，t1是函数名称，无参，返回值为Test类型。

- Test t2; 对 无参的初始化；
- Test t3(10); 对 含有一个参数的初始化。

## 六、成员方法

成员方法的实现：可以在类内直接定义；也可以在类内声明，类外定义，加上作用域限定符。

```cpp
int Test::getData(){
  return data; 
}
```

加上::这个之后表明getData是Test的成员函数。

## 七、C++重载

C++重载：C语言为什么不能重载呢？  从汇编层面可以知道。

```cpp
void fun();                          
int fun(int a);
double fun(double a, double b)
```

以上三个函数在C角度看汇编都是fun;名字都相同；

从C++的角度看，其汇编层面的函数名字为：fun funi fundd,是不一样的，所以C++有函数的重载。

重载：函数名字相同，只与参数列表有关，与返回值无关。

**在C++中对重载函数使用extern "C"就可以理解了，extern "C"：将当前函数(C++写的)，当做C编译，而C编译只看函数名称，所以多个重载函数只能出现一次extern “C”！要是出现两个，就会造成函数名相同，错误。**

## 八、说明

原创文章链接：[C++从零入门学习系列（1）---类与对象](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483846&idx=1&sn=0b39bd33f11231a48524c4184cac0afc&chksm=f94c8bfbce3b02ed1dd04285c89fd8fcffd86bd073dbb5611d87247cce139826065ff6baf044&scene=21#wechat_redirect)


---


## C++从零入门学习系列_构造函数与析构函数

- [一、构造函数](#一构造函数)
- [二、构造函数的3个作用](#二构造函数的3个作用)
- [三、析构函数](#三析构函数)
- [四、说明](#四说明)

对于 C++ 的学习，先把基础概念弄明白，理解熟悉常见语法。

## 一、构造函数

在我们定义一个类后，对其实例化，值都是随机的，然后我们自己在写函数对其赋值，感觉是多余的，Ｃ++就提供了在实例化时就初始化的过程，就叫做构造函数。

构造函数是特殊的公有成员函数，有一下特点:

1. 构造函数与类名相同；
2. 构造函数不写返回值；
3. 在实例化对象时，自动 必须 一次调用；
4. 可以重载(人生而不平等，这样理解)；
5. 构造函数可以在类内定义，也可以在类外定义(通过作用域限定符::)
6. C++会自动的给出默认的构造函数，要是自己写了，就不会再提供默认的构造函数了；

```cpp
class Test{
public:
  Test(int d = 0) : data(d){}
```

这就是一个缺省的构造函数，存在时，不能再有无参的构造函数(不然是初始化为随机值还是默认值0)。

## 二、构造函数的3个作用

1. 构造对象，自动调用构造函数；
2. 初始化对象；
3. **类型转换。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIm1QWGicNtdl2jD3DwufxSuoT7C6ZpVxFZ3MVYLvBajx6iaTlk0ZwV3AQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

分析:t1是Test类型的，100是×××的；不同类型怎么能赋值呢?

**C C++都是强类型语言，如果类型不一样，从某种角度上说不许赋值；**

```cpp
int a;
double d = 12.34;

a = d;
```

**类型不一样，不可能直接赋值，的借助中间临时变量来赋值；**

现在来看 t = 100;

**100 必须的找到中间桥梁Test类型的，才能给Test类型的t赋值，里面是对应成员一一赋值；刚好有个构造函数，并且有一个参数，通过构造函数，把×××100转化为Test类型，此时实例化了一个对象，刚好转换为类型一致，可以赋值。**

此时还存在一个这样的问题：关键字 explicit  显示的，作用:

1. **预防构造函数被隐式调用；**
2. **只能在构造函数前使用此关键字；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFI6MWLLw0vUe8MnWxElmDLf0ftz2Hj2x2vmEf1QYaiauRoTdwP6LMoHPw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时隐式赋值，不能调用显示构造函数，所以出错；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIpI9ryctBbRKja2TQ7ALgXjY60XxiayBcwQib5PEdQKibhkCjJkxNt682Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

Test t = (Test)100;强制类型转换就是显示调用，explicit修饰的构造函数方可被调用！

现在看下面的问题：Test类型能否给int类型赋值？

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIpI9ryctBbRKja2TQ7ALgXjY60XxiayBcwQib5PEdQKibhkCjJkxNt682Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

两边类型不一致，并且在类的内部没有找到转换相同类型Test->int类型的函数(也就是说没有找到中间桥梁)；所以出错！

必须的用到运算符重载(添加方法)，下面这个叫做类型转换，————>不能有返回值；

添加在类内一个方法：

```cpp
public:
    operator int(){
        return data;
    }
```

将Test类型转换为int，(有了这个方法就可以实现)，从而找到桥梁，类型一致便可赋值；**原理: 借助了中间的无名变量空间(充当桥梁)。**

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIEVvupvz5QVVaFmWlWkYp6ibVIu0HBv6hNZ8fYtGB6lIUTCPiaZmEZOIQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、析构函数

```cpp
~Test(){}
```

析构函数就是释放对象占用的空间，对任何函数死亡都是一样的，所以任何对象的析构只能用相同的方式进行。

**析构函数无重载，无参，无返回，只有一个(死是平等的)。**

特点：

1. 析构函数与类名相同，但在前面加上'~'，如：~Test(){}
2. **对象释放时，系统自动调用析构函数(可以是默认的)。**

## 四、说明

原创文章链接：[C++从零入门学习系列（3）---构造函数与析构函数](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483868&idx=1&sn=4e755a6a7bf9afc6590fcc49e8016c00&chksm=f94c8be1ce3b02f7bc0a9e599ce51996608d245f59bc9e9383fa9ac92ceecdb4fc681e3617f0&scene=21#wechat_redirect)


---


## C++从零入门学习系列_this指针

- [一、C++实例化对象](#一c实例化对象)
- [二、this指针使用时机](#二this指针使用时机)
- [三、this指向当前对象的本质](#三this指向当前对象的本质)
- [四、说明](#四说明)

this 指针可以看出 C++ 底层的特性。

## 一、C++实例化对象

C++中在实例化对象之后

```cpp
class Test{};
```

用sizeof(Test)计算类的大小，可以知道只有数据成员的大小，并没有方法的大小，因为其数据各自保存，而成员方法共用一份。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtEtnf3S39BaUE4mT673tuEPlCdgVN7R3wXf8tZdCQB0dWrFExSlaVEuU9SibTWqPIh9dkZ0MKHriaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

那么每个对象在调用方法是怎么会知道是自己的数据成员呢？

## 二、this指针使用时机

this指针是由编译器所造，真实的隐藏在内部。

```cpp
#include<iostream>
using namespace std;

class Test{
public:
    void setData(int x){
        data = x;
    }
    int getData(){
        return data;
    }
private:
    int data;
};
int main(void){
    Test t1;
    int value;
    
    t1.setData(3);
    value = t1.getData();
    cout<<value<<endl;
    
    return 0;
}
```

以上的这个程序，其实内部就隐藏了this指针，万一函数如下呢：

```cpp
void setData(int data){
    data = data;
}
```

解决方案：

```cpp
void setData(int data){
    this->data = data;
}
```

此时this->data指的就是当前对象的data。

**this的使用时机：当参数名字和要赋值的数据成员同名时；使用this。**

## 三、this指向当前对象的本质

Ｃ++中编译器对类的编译顺序：

- 先识别类名；
- 在识别所有的数据成员(包括私有、公有、保护)；
- 识别方法，并且重写方法。

```cpp
void setData(int data){
    this->data = data;
}
...........

t1.setData(3);
```

上面的代码本质，有个隐藏的参数传递，其编译器改写的函数如下：

```cpp
t1.setData(3)---->  setData(&t1, 3);
void setData(Test *this, int data){}
```

相当于函数有一个隐式参数，但是程序不能那样写，必须写其对象调用的形式(知道本质，却不能写本质形式)，否则会报错。

**C++中就是通过这个this指向当前对象，从而区分了不同对象的数据成员；**

但问题远没有这么简单，再看下面的代码：

```cpp
void setData(int data){
  this = NULL;
  this->data = x;
}
```

此时代码将出现问题，万一不小心给this = NULL；此时将会报错，编译根本无法通过，但是，发明Ｃ++的人，不会让你给this赋值，这就的对this本质在此剖析：

怎样才能不更改this的值呢？改写函数：

```cpp
t1.setData(3)---->  setData(&t1, 3);
void setData(Test * const this, int data){}
```

**这才是this的本质，其const修饰，为常量的，不可更改！**

**只要对象调用方法(普通方法)，必然会有隐式的函数改写，其this的本质一目了然！**

## 四、说明

原创文章链接：[C++从零入门学习系列（2）---this指针](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483850&idx=1&sn=bf51741e739b852f46702aa2e0b8079a&chksm=f94c8bf7ce3b02e14e4f5a5999928718d99b6744a982ad9166e15e977726fdfc00280582d380&scene=21#wechat_redirect)


---
