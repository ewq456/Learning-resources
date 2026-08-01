# shared_ptr 共享指针详解


## C++进阶系列之Boost库智能指针_shared_ptr_上

- [一、共享性智能指针(shared_ptr)](#一共享性智能指针shared_ptr)
- [二、怎么使用shared_ptr](#二怎么使用shared_ptr)
- [三、框架的搭建](#三框架的搭建)
- [四、说明](#四说明)

## 一、共享性智能指针(shared_ptr)

引用计数型指针：shared_ptr是一个最像指针的“智能指针”，是boost.smart_ptr库中最有价值，最重要，也是最有用的。

**shared_ptr实现的是引用技术型的智能指针，可以被拷贝和赋值，在任意地方共享它，当没有代码使用(此时引用计数为0)它才删除被动态分配的对象。shared_ptr也可以被安全的放到标准容器中；**

## 二、怎么使用shared_ptr

举一个操作的例子：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);
//    cout<<*ps<<endl;

    cout<<ps.unique()<<endl; //判断对空间是否唯一，
    cout<<ps.use_count()<<endl;
    shared_ptr<int> ps1 = ps;
    cout<<ps.unique()<<endl; //此时有两个对空间有共享，所以不唯一，是0
    cout<<ps.use_count()<<endl;
    shared_ptr<int> ps2;
    ps2 = ps1;
    cout<<ps.use_count()<<endl;
}
```

关键在shared_ptr中存在共享引用计数。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcjZWU5kP4ricts1BxZPq1eGSZDC4KtONqx88czpaoI5RuicsFIM1G0BIA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、框架的搭建

阅读源代码：

shared_ptr 中的私有数据成员：

```cpp
private:
    T *px;
    shared_count pn; //对象成员，肯定先调这个对象的构造函数；
```

**之前的引用计数通过一个指针，现在的引用计数通过一个对象，pn
构造函数的调用顺序：先虚基类，父类，对象成员，最后构造自己；**

此时的模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcv343JN8D8xibrfYOQ8dfwqicjZINXtJkdHPSly9zPGmejRaKYuwj7Llw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

其后调用对象成员的构造函数：

shared_counted中的私有数据成员：

```cpp
private:
    sp_counted_base *pi; //有一个指向引用计数器父类的指针；
```

此时就得先写：sp_counted_base类了；

sp_counted_base类中的私有数据成员：

```cpp
private:
    long use_count_;
```

然后看到在shared_counted的构造函数：

```cpp
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx(p)){ //特别重要，这个构造函数
```

此时就得写sp_counted_impl_xx类了：这是继承sp_counted_base类

其内部数据时成员：

```cpp
private:
    T *px_;
```

此时整体的建构体系就已经形成：

我认为是这样的：

1. 先实现了shared_ptr类，因为有对象成员，其后调用构造函数；
2. 实现了shared_count; 其数据成员有sp_counted_base；
3. 因为编译器的顺序，先类名，在数据成员，最后函数，所以此时先实现sp_counted_base;
4. 因为shared_counted中的构造函数要在堆上开辟sp_counted_impl_xx空间，最后实现是sp_counted_impl_xx，它有继承sp_counted_base,所以构造函数的调用顺序就很清楚了。

构造函数的调用顺序：sp_counted_base、sp_counted_impl_xx、shared_count、shared_ptr。

此时的具体实现代码如下：

```cpp
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include<iostream>
using namespace std;

#endif
////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include"shared_count.h"

template<class T>
class shared_ptr{
public:
    shared_ptr(T *p = 0) : px(p), pn(p){
        cout<<"Create shared_ptr object!"<<endl;
    }
    ~shared_ptr(){
        cout<<"Free shared_ptr object"<<endl;
    }
private:
    T *px;
    shared_count pn;
};

#endif
///////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_COUNT_H_
#define _SHARED_COUNT_H_

#include"config.h"
#include"sp_counted_base.h"
#include"sp_counted_impl_xx.h"

class shared_count{
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx<T>(p)){
        cout<<"Create shared_cout object!"<<endl;
    }
    ~shared_count(){
        cout<<"Free shared_count object"<<endl;
    }
private:
    sp_counted_base *pi;
};


#endif
///////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_BASE_H_
#define SP_COUNTED_BASE_H_

#include"config.h"

class sp_counted_base{
public:
    sp_counted_base() : use_count_(1){
        cout<<"Create sp_counted_base object"<<endl;
    }
    ~sp_counted_base(){
        cout<<"Free sp_counted_base object"<<endl;
    }
private:
    long use_count_;
};

#endif
//////////////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_IMPL_XX_H_
#define SP_COUNTED_IMPL_XX_H_

#include"sp_counted_base.h"

template<class T>
class sp_counted_impl_xx : public sp_counted_base{
public:
    sp_counted_impl_xx(T *p) : px_(p){
        cout<<"Create sp_counted_impl_xx object"<<endl;
    }
    ~sp_counted_impl_xx(){
        cout<<"Free sp_counted_impl_xx object"<<endl;
    }
private:
    T *px_;
};

#endif
//////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);   
}

```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTc8UtrIjpUZvia97YdBpZJBKhmVU6yRrt4Ix8nzib7xYvPgnuzIVFsBD9A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

以上就是只搭好了大致的框架，并没有考虑内存泄漏、析构的具体写法和其它函数的实现；

那么整个模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcaR9HiabG7Tic28LsPbJbmH7a2UQY2DRsFCxiaaqC5ibxTia2BOics35gtqiaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、说明

原创文章链接：[C++进阶系列之Boost库智能指针（5）---shared_ptr(上)](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483974&idx=1&sn=5ad0fa72c605e2c48511008bda167972&chksm=f94c887bce3b016da4a02880f3e28f31d0f0f23bc3869e5ed5a64c41ac4b2e410bd634759065&scene=21#wechat_redirect)


---


## C++进阶系列之Boost库智能指针_shared_ptr

- [一、shared_ptr中的px出现原因](#一shared_ptr中的px出现原因)
- [二、解决析构函数](#二解决析构函数)
- [三、拷贝构造和赋值语句](#三拷贝构造和赋值语句)
- [四、shared_ptr的模拟部分](#四shared_ptr的模拟部分)
- [五、删除器](#五删除器)
- [六、说明](#六说明)

## 一、shared_ptr中的px出现原因

方便对其数据空间的管理，取值和获取地址将极大的方便我们的操作。

## 二、解决析构函数

避免内存空间的泄漏。new出来的空间都没有释放掉！

释放拥有全靠的是引用计数。

```cpp
~shared_count(){ 
    if(pi){  //判断所指父类是否为空
        pi->release(); //释放new出来的对象和外部new出来的空间
    }
}
////////////////////////////////////////////////////////////////////////
public:
    virtual void dispose() = 0; //纯虚函数
    void release(){  //在sp_counted_base中
        if(--use_count_ == 0){ //判断use_count是否为0
            dispose();  //因为虚函数，所以子类中实现
            delete this; //先调用析构函数，在释放this指向的空间
        }    
    }
///////////////////////////////////////////////////////////////////////
public:
    void dispose(){
        delete px_; //释放外部new出来的空间
    }
```

因为要级联释放空间，所以sp_counted_base的析构函数必须是虚函数，才能先调用子类的析构，最后调用自己的析构函数。

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcysyY6BMerY1v7ia1p7ODgzGIJ7rOFOUX02oK2zB4to1rlV8S0brK8PA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

use_count和unique函数的实现比较简单

## 三、拷贝构造和赋值语句

此时应当相当于浅拷贝，use_count加1即可！模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcgmML8oGib6Ria4GUN5fZibhHic7DqZzsicRekqztRUibm3rZe8obKn6keicbQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时应在shared_ptr和shared_count进行浅拷贝，并在shared_count中加入方法。

```cpp
    shared_count(shared_count const &r) : pi(r.pi){
        if(pi){
            pi->add_ref_copy(); //在父类中实现这个方法，只要让++use_count_即可！
        }
    }
```

赋值语句，关键调用swap函数，的认真思考，画画图就好理解多了(前面已经写过这个了)。

**这个赋值语句写的真的很好，既让use_count_加1，又可以让原先的空间符合情况的释放。**

```cpp
    shared_ptr<T>& operator=(shared_ptr<T> const &r){
        if(this != &r){
            this_type(r).swap(*this);//调用拷贝构造，先创建一个无名临时的对象，
        }                         //因为调用了拷贝构造，所以在shared_count中调用方法,
        return *this;             //会让use_count_加1的。
    }
//////////////////////////////////////////////////////////////////////////////////////
    void swap(shared_ptr<T> &other){
        std::swap(px, other.px); //指针的交换
        pn.swap(other.pn);
    }
```

## 四、shared_ptr的模拟部分

```cpp
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include<iostream>
using namespace std;

//#define DISPLAY

#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include"shared_count.h"

template<class T>
class shared_ptr{
    typedef shared_ptr<T> this_type;
public:
    shared_ptr(T *p = 0) : px(p), pn(p){
#ifdef DISPLAY
        cout<<"Create shared_ptr object!"<<endl;
#endif
    }
    shared_ptr(shared_ptr<T> const &r) : px(r.px), pn(r.pn){}
    shared_ptr<T>& operator=(shared_ptr<T> const &r){
        if(this != &r){
            this_type(r).swap(*this);//调用拷贝构造，先创建一个无名临时的对象
        }
        return *this;
    }
    ~shared_ptr(){
#ifdef DISPLAY
        cout<<"Free shared_ptr object"<<endl;
#endif
    }
public:
    T& operator*()const{
        return *(get());
    }
    T* operator->()const{
        return get();
    }
    T* get()const{
        return px;
    }
public:
    long use_count()const{
        return pn.use_count();
    }
    bool unique()const{
        return pn.unique();
    }
    void reset(T *p){
        this_type(p).swap(*this);
    }
    void swap(shared_ptr<T> &other){
        std::swap(px, other.px); //指针的交换
        pn.swap(other.pn);
    }
private:
    T *px;
    shared_count pn;
};

#endif
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_COUNT_H_
#define _SHARED_COUNT_H_

#include"config.h"
#include"sp_counted_base.h"
#include"sp_counted_impl_xx.h"

class shared_count{
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx<T>(p)){
#ifdef DISPLAY
        cout<<"Create shared_cout object!"<<endl;
#endif
    }
    shared_count(shared_count const &r) : pi(r.pi){
        if(pi){
            pi->add_ref_copy();
        }
    }
    ~shared_count(){
#ifdef DISPLAY
        cout<<"Free shared_count object"<<endl;
#endif
        if(pi){
            pi->release();
        }
    }
public:
    long use_count()const{
        return pi != 0 ? pi->use_count() : 0;
    }
    bool unique()const{
        return use_count() == 1;
    }
    void swap(shared_count &r){
        sp_counted_base *tmp = r.pi;
        r.pi = pi;
        pi = tmp;
    }
private:
    sp_counted_base *pi;
};

#endif
//////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_BASE_H_
#define SP_COUNTED_BASE_H_

#include"config.h"

class sp_counted_base{  //抽象类
public:
    sp_counted_base() : use_count_(1){
#ifdef DISPLAY
        cout<<"Create sp_counted_base object"<<endl;
#endif
    }
    virtual ~sp_counted_base(){
#ifdef DISPLAY
        cout<<"Free sp_counted_base object"<<endl;
#endif
    }
public:
    virtual void dispose() = 0; //纯虚函数
    void release(){
        if(--use_count_ == 0){
            dispose();
            delete this;
        }    
    }
public:
    long use_count()const{
        return use_count_;
    }
    void add_ref_copy(){
        ++use_count_;
    }
private:
    long use_count_;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_IMPL_XX_H_
#define SP_COUNTED_IMPL_XX_H_

#include"sp_counted_base.h"

template<class T>
class sp_counted_impl_xx : public sp_counted_base{
public:
    sp_counted_impl_xx(T *p) : px_(p){
#ifdef DISPLAY
        cout<<"Create sp_counted_impl_xx object"<<endl;
#endif
    }
    ~sp_counted_impl_xx(){
#ifdef DISPLAY
        cout<<"Free sp_counted_impl_xx object"<<endl;
#endif
    }
public:
    void dispose(){
        delete px_;
    }
private:
    T *px_;
};

#endif
////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);

    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;

    shared_ptr<int> ps1 = ps;
    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;
    shared_ptr<int> ps2;
    ps2 = ps;
    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;

    //cout<<*ps<<endl;
    
}

```

以上就是对shared_ptr的部分源码剖析的理解了。

## 五、删除器

删除器d可以是一个函数对象(是一个对象，但是使用起来像函数)，也可以是一个函数指针；

可以根据自己定义的方式去管理(释放)内存空间。有2个特性：函数对象 operator()进行了重载。

删除器的使用，调用系统的：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

void My_Deleter(int *p){ //删除器
    cout<<"HaHa:"<<endl;
    delete p;
}
//靠删除器来管理空间，而不再向之前的调用析构函数。
int main(void){
    int *p = new int(10); //假设p是特殊的资源
    shared_ptr<int> ps(p, My_Deleter);
}
```

回过头来，对自己的空间进行释放，定义自定义的删除器。不采用默认方式释放，而是采用自己的方式释放！

删除器自己模拟部分代码：

```cpp
public:
    template<class Y, class D>
        shared_ptr(Y *p, D d) : px(p), pn(p, d){}//支持传递删除器
/////////////////////////////////////////////////////////////////////////////
    template<class Y, class D>
    shared_count(Y *p, D d) : pi(0){
        typedef Y* P;
        pi = new sp_counted_impl_pd<P, D>(p, d);
    }
///////////////////////////////////////////////////////////////////////////
template<class P, class D>
class sp_counted_impl_pd : public sp_counted_base{
public:
    sp_counted_impl_pd(P p, D d) : ptr(p), del(d){}
public:
    void dispose(){
        delete ptr;
    }
private:
    P ptr;
    D del;
};
//////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;


void My_Deleter(int *p){ //删除器
    cout<<"HaHa:"<<endl;
    delete p;
}

int main(void){
    int *p = new int(10); 
    shared_ptr<int> ps(p, My_Deleter);
}

```

以上就是删除器实现的主要代码，是在shared_ptr中实现的。

## 六、说明

原创文章链接：[C++进阶系列之Boost库智能指针（6）---shared_ptr(下)](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483975&idx=1&sn=2fa59f6a75fdbefb18a156ecec16f4c1&chksm=f94c887ace3b016c45755dd29908c3ede957ecfdd1cc44863e2892f1c4a93b178cfd5882b926&scene=21#wechat_redirect)


---


## C++进阶系列之Boost库智能指针_shared_array

- [一、上次写的删除器有些问题](#一上次写的删除器有些问题)
- [二、shared_array](#二shared_array)
- [三、如何使用shared_array](#三如何使用shared_array)
- [四、shared_array](#四shared_array)
- [五、说明](#五说明)

## 一、上次写的删除器有些问题

```cpp
template<class P, class D>
class sp_counted_impl_pd : public sp_counted_base{
public:
    sp_counted_impl_pd(P p, D d) : ptr(p), del(d){}
public:
    void dispose(){
        del(ptr);  //就是这里，将对象用作函数！！！
    }
private:
    P ptr;
    D del;
};
```

**del(ptr)  -> del.operator()(ptr);重载了()的类使用起来就是函数对象。**

**删除器：函数对象和函数都可以充当。**

## 二、shared_array

它和shared_ptr类似，它包装了new[]操作符在堆上分配的动态数组，也是采用了引用计数的机制。

shared_array的接口和功能与shared_ptr几乎是相同的，主要区别：

1. 接受指针p必须是new []的结果
2. 提供operator[]的重载，可以使用下标
3. 系统没有提供*、->的重载
4. 析构函数使用delete  [];

## 三、如何使用shared_array

系统调用：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

int main(void){
    int *p = new int[10];
    shared_array<int> pa(p);  //共享数组

    for(int i = 0; i < 10; i++){
        pa[i] = i+1;  //系统内进行了[]的重载
    }
    for(i = 0; i < 10; i++){
        cout<<pa[i]<<" ";
    }
    cout<<endl;

}
```

## 四、shared_array

模仿的源码如下：

```cpp
#ifndef _SHARED_ARRAY_H_
#define _SHARED_ARRAY_H_

#include"checked_delete.h"

template<class T>
class shared_array{
public:
    typedef checked_array_deleter<T> deleter;
    shared_array(T *p = 0) : px(p), pn(p, deleter()){} //无名对象
    ~shared_array(){
        
    }
public:
    T& operator[](int i)const{
        return px[i];
    }
private:
    T *px;
    shared_count pn;  //必须用到引用计数器对象
};

#endif
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CHECKED_DELETE_H_
#define _CHECKED_DELETE_H_

template<class T>
void checked_array_delete(T *x){
    delete []x;
}

template<class T>
struct checked_array_deleter{
public:
    void operator()(T *x)const{
        checked_array_delete(x);        
    }
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
#include"shared_array.h"
using namespace std;
/*
template<class T>
void checked_array_delete(T *x){
    delete []x;
}

template<class T>
struct checked_array_deleter{
public:
    void operator()(T *x)const{
        checked_array_delete(x);
    }
};
写好()的重载之后，就是在shared_counted.h中释放空间时将用到。
del(ptr)  -> del.operator()(ptr);重载了()的类使用起来就是函数对象
删除器：函数对象和函数都可以充当。
*/
int main(void){
    int *p = new int[10];
    shared_array<int> pa(p);

    for(int i = 0; i < 10; i++){
        pa[i] = i+1;
    }
    for(i = 0; i < 10; i++){
        cout<<pa[i]<<" ";
    }
    cout<<endl;
}

```

缺点：

1. 重载使用[]时要小心，shared_array不提供数组的索引范围检查
2. 所管理的空间是死的，不能够自动增长。

## 五、说明

原创文章链接：[C++进阶系列之Boost库智能指针（7）---shared_array](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483976&idx=1&sn=003e92e049245a52413eed20380bef52&chksm=f94c8875ce3b016367baf90693e267cb82d844ed0273d03f1338b2efe9544f08402f0ece84dd&scene=21#wechat_redirect)


---
