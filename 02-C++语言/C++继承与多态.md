# C++继承与多态


## C++从零入门学习系列_继承

- [一、继承](#一继承)
- [二、访问属性](#二访问属性)
- [三、构造函数的调用顺序](#三构造函数的调用顺序)
- [四、砖石继承](#四砖石继承)
- [五、同名隐藏与赋值兼容规则](#五同名隐藏与赋值兼容规则)
  - [5.1、同名隐藏](#51同名隐藏)
  - [5.2、赋值兼容规则](#52赋值兼容规则)
- [六、说明](#六说明)

## 一、继承

这个机制是面向对象使代码复用的重要手段，在原有类的基础上进行扩展，增加功能；

**继承的出现，应该主要是为了多态性；继承实质是是为了多态做准备。**

## 二、访问属性

1. 有public、protected、private继承，不写的话，默认私有继承；
class d : public B1，B2，B3，在这块，B1是公有继承，B2和B3是默认的，私有继承；

2. class Base{}；sizeof(Base); 空类，计算结果 1 字节；起标识作用

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4RUib0jf0YxbVHlHsf4CEmw55wLCCX4tkxX9XW56m9FobHqicjmTAqicPA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3. 不管什么继承，子类均不会继承父类的构造方法和析构方法，其余的拷贝一份(包括私有，公有，保护)放到子类，只不过更改相应的修饰符权限。
4. 不论什么继承，子类都不能直接访问父类的私有数据。
5. 从对象和子类内看访问属性：

   - 对象角度：永远只能访问公有方法；
   - 子类内角度：子类永不可能直接访问父类的私有-------->安全性；
   - 子类在公有继承(public)中，父类的(除去私有的)都可以访问;其继承下来的修饰符权限不用改；
   - 子类在保护继承(protected)中，除去父类的私有，都可以访问；
   - 子类在私有继承(private)中，；继承下来的属性都变为私有，原因：成员函数可以访问自己的私有数据；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4nTBzWrJI6vrrjBCrl3rVcicbvXlaObAYybMnG8lE7eXD7nlvmQhWnQw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

6. protected----->只在继承中体现，其它的地方用不到这个；

   - protected/private————>不同之处：影响下一层此的继承；private会阻断继承；

## 三、构造函数的调用顺序

1. 当在继承时创建一个对象，其内部隐藏了先调用其父类的构造函数，先创建了父类的对象，其后创建子类对象；析构函数的调用与此相反;

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs41vib5h51W1zlDcdCVX7qXXahAsXkjZQz9iaTeq0SE6UfoBJDXwvJAicTw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2. **按继承顺序，成员对象创建顺序，调用父类的构造函数，创建父类对象，最后创建自己对象；与参数列表的顺序无关；**

3. 看看有没有虚继承(virtual public B1)；有的话，先调用虚继承的构造函数，在调用普通父类的构造函数，最后调用自己的，一切按顺序来；

## 四、砖石继承

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4esibIo3eNnIkgbib1BWkjqbxDnCbKQduKqsHAia5E7LeNYiaYbzljIIF5A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

继承下来时有2个n，在调用时候会产生二义性；其采用虚继承可以解决：

```cpp
#include<iostream>
using namespace std;
 
class Base{
public:
    int n;
};
 
class D1 : virtual public Base{//加上virtual，表示虚继承
public:     //public virtual Base和上面等同
    int x;
};
 
class D2 : virtual public Base{  //加上virtual，表示虚继承
public:
    int y;
};
 
class S : public D1, public D2{  //此时就只有一个n了;
public:
    int z;
};
 
int main(){
    S c;
    c.n = 10;
 
    cout<<&c.D1::n<<endl;  //因为同一个n,所以地址相同；
    cout<<&c.D2::n<<endl;
    return 0;
}
```

虚继承可以解决这类问题，就只有一个n被继承下来，就可以正确访问n了;

## 五、同名隐藏与赋值兼容规则

### 5.1、同名隐藏

```cpp
#include<iostream>
using namespace std;
  
class Base
{
public:
    void fun()  //父类的无参fun()方法
    {
        cout<<"This is Base fun()"<<endl;
    }
    void fun(int a) //父类的一个参数的fun()方法
    {
        cout<<"This is Base fun(int)"<<endl;
    }
};
  
class D : public Base
{
public:
    void fun()   //子类的fun()方法
    {
        cout<<"This is D fun()"<<endl;
    }
};
  
int main()
{
    D d;
    d.fun();   //肯定调用子类的fun()方法
 // d.fun(1);  此时因为函数名相同，隐藏了父类所有的该方法，子类有没有参数，所以报错
    d.Base::fun(1);//此时调用了父类的fun带参数的方法，刚才只是隐藏了，并没有覆盖！
    return 0;
}
```

**子类在继承父类时，父类中与子类中函数名字相同的所有均被隐藏，(父类中同名的函数不能是虚函数)--->同名隐藏**

### 5.2、赋值兼容规则

```cpp
class Base{};
  
void Cloud(Base *pb){
    pb->fun();  //没写虚函数，将访问父类的此方法；
    pb->show();
}
  
int main(){
    Base b;
    D d;
    Cloud(&d);
    b = d;  //(1)、子类对象可以直接给父类对象赋值
  
    Base *pb = &d; //(2)、子类对象的地址可以赋值给父类对象的指针
    
    Base &rb = d; //(3)、子类对象可以让父类对象所引用
    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4yoEnMMRXXaP8b391R3fCosZLPIHMSIAaNdV6coexVFJjpQqOK44Bcw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

以上就是赋值兼容三规则；在多态中将会体现出用处。

## 六、说明

原创文章链接：[C++从零入门学习系列（15）---继承](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483935&idx=1&sn=1fda3f1649a3786654d7394dd54ebdf4&chksm=f94c8822ce3b013416ecb09e7e69e6fc6f1b9d67c354c087512aef1fd842433991b11844167b&scene=21#wechat_redirect)


---


## C++从零入门学习系列_多态

- [一、内存模型](#一内存模型)
- [二、虚函数](#二虚函数)
- [三、多态](#三多态)
- [四、虚函数剖析](#四虚函数剖析)
- [五、多态的原理](#五多态的原理)
- [六、多继承中虚表的画法](#六多继承中虚表的画法)
- [七、纯虚函数与抽象类](#七纯虚函数与抽象类)
- [八、说明](#八说明)

## 一、内存模型

当定义一个子类对象时，该子类就会有相应的内存情况，此时就是内存模型；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4B4u60niaopmL4NxbOrhS0zRQ8UgDJq5TB3Bqwicf5FsfmCnVpTz1V6BA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、虚函数

虚函数是一个类的成员函数，其定义格式如下：virtual 返回值类型 函数名(参数表)；

关键字virtual指明该成员函数为虚函数。

```cpp
class Test{
public：
    virtual void fun(){}   //虚函数
}；
```

## 三、多态

1. **必须在继承体系中；**
2. **父类中存在的成员函数为虚函数的(virtual)；**
3. **子类必须达到三同(返回值 函数名 参数列表)**
4. **必须通过父类型的指针/引用来调用；**
5. **两个类外；**

1、父类的成员函数返回值为 Base*

子类的成员函数返回值为 D* 此时，打破三同，仍为覆盖！！！

2、**父类的析构函数一般都要加上(virtual)，就可以利用多态性级联的调用析构函数，此时先调用子类的，在调用父类的；(以免发生内存泄漏)！！！**

## 四、虚函数剖析

1、当在类中出现一个(virtual)，虚方法时，对象中第一个成员将是：_vptr;

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4h4kDG2rsJriaH6ibgvNKT3k8LibllM9CllesZPHbJTfF5zwEDfdPnf9DA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时只有一个成员，应该为4B，但是其因为**有虚函数的存在，内部的第一个成员就一定为虚表指针；**

指针32位下为4字节，所以此时一共为8字节；**(不管内部有多少个虚函数，但是虚表指针只有一个)；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4cLVYicicyhnrG1Dib6ZpQQGcAdPXhiauwHcdia6R09cI88n1huT4cAAG89w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、虚函数将在继承体系中，一直为虚(覆盖时); 此时的virtual可以省略不写；

3、多态：就是对虚方法的重写；

4、**虚表：装虚函数的表，其本质是地址的覆盖；**

## 五、多态的原理

这是没有覆盖的虚表：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4oib691SVgO5IohqkbH5MH9v3ictC0QO8sngPyCs4djm8OG6KxHSztdicg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

假如子类有一个方法与父类的虚方法三同，此时覆盖；但是通过父类的指针/引用永远只能访问父类对象的部分；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4rYiaAEIgIY82icFfMSUFkwsw4C2dXAIuB9ibLic8SCyHoNxJg8w7eAS4pw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

如何取得虚表中的函数呢？

```cpp
Base b;
cout<<&b<<endl;   //对象的地址
printf("%p\n", *(int *)(&b));  //虚表中虚表指针的值(指针4字节)，所以转换×××指针，也就是虚表指针的地址；
((Fun)*((int*)*(int*)(&b) + 0))();  //Fun是函数指针，将获得虚表中的第一个函数;
((Fun)*((int*)*(int*)(&b) + 1))();  //Fun是函数指针，将获得虚表中的第二个函数;
((Fun)*((int*)*(int*)(&b) + 2))();  //Fun是函数指针，将获得虚表中的第三个函数;
```

## 六、多继承中虚表的画法

父类均为虚函数，子类中也有虚函数，且没有进行覆盖，**则将子类的放到第一个虚表的最后，其余的父类虚表就不用放了；**

因为就是放了，通过父类的指针/引用也访问不了，浪费内存空间；要是有覆盖的，则每个虚表都得画出；其余情况类似分析就行。

## 七、纯虚函数与抽象类

```cpp
#include<iostream>
using namespace std;

class Test{
public:
    virtual void fun() = 0;  //这种形式就是存虚函数，赋值为0；
    virtual void fun1() = 0;
    virtual void fun2() = 0;
    virtual void fun3() = 0;
};

int main(void){
    return 0;
}
```

以上的类中都为纯虚函数的类叫做抽象类; 抽象类不能实例化；也就是不能定义对象；

**继承抽象类的，必须实现其所有方法，不然自己继承下来依旧是抽象类，不能实例化对象。**

## 八、说明

原创文章链接：[C++从零入门学习系列（16）---多态](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483939&idx=1&sn=5ecc943e9d7abe424d87ecaac5af783e&chksm=f94c881ece3b010819958f429a43a22335185e680a61fd66c0df593643addcce1a6b2352f127&scene=21#wechat_redirect)


---
