# C++拷贝控制


## C++从零入门学习系列_引用_拷贝构造_赋值语句

- [一、引用](#一引用)
- [二、拷贝构造函数](#二拷贝构造函数)
- [三、赋值语句](#三赋值语句)
- [四、函数的优化调用](#四函数的优化调用)
- [五、说明](#五说明)

C++ 方向的学习，一定是痛苦而又漫长的，基础知识必须牢固！

## 一、引用

C++中有一种新的数据类型，对已开辟空间在取一个名字；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgegVdP3dp3MqSPZll5eqyfZQ1To2jT0E0JlI20ibSGrW2YIvurqG1QPOQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(引用空间内存图)</p>

**就是别名，不开辟新的空间，没有空引用；**

```cpp
例：int &b; 错误；
```

交换两个数字用引用实现：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeiaHVHQS8acMYnKvibL7woqgxt4p01fCJq0sLibJAzFTcWQDcLoT7DuL7A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(交换2数字)</p>

常见的几种引用形式：

1. 对变量引用：int a = 10; int &b = a;
2. 对指针引用：int *p = &a; int *&q = p;
3. 对数组引用：int ar[3] = {1, 2, 3,}; int (&b)[3] = ar;

此外还有以下类型的引用：

1. 常引用 const int x = 100;
   - int &y = x; 错的，非常量的不能引用常量，只有自己也加上const成为常量才可以引用。**常量只能常引用；**

2. int n = 20;
   - const int &m = n;   对的，常量引用非常量可以，因为你可以改变，我要求自己不能改变而已！**变量也可以常引用；**

3. const double d = 12.34;
   - const int &f = d;    对的，此时d和f由于不是同一种数据类型，所以地址不一样，此时f引用的不是真实的d，而是对产生的临时变量的引用(此时会把整数截取)；
4. double d = 12.34;
   - int &f = d;   错的，**临时变量一般都具备常量的性质**，我们往往在类型转换时所产生的中间临时变量具备常量的性质；所以要加const，对常量的引用；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgegAkyfziapJXlJ1ezcS8GvDzjGtPnpwXFEh15ELOhZ1tnB6uPmZDf2zQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**加上const后，常引用对常量，因为中间的临时变量都是常量(在类型转换时会产生中间的临时变量)；只要类型不同，就都会转换；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeP0ZeNjyTO8v9UaZdaBJA26vnF4cmoRkJjH6saOmSTpSV9KvWNI33sA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、拷贝构造函数

1、对象初始化对象，调用拷贝构造函数。

```cpp
Test(const Test &t){}
```

因为拷贝构造函数也是构造函数，所以和类名相同。const只是为了保护t不被更改；

&必须加上，因为 Test t(t1);此时相当于t1给t初始化，调用拷贝构造函数，将陷入无穷的递归当中，所以要使用引用；

2、拷贝构造函数系统会有默认的，按其成员进行拷贝！

3、 调用拷贝构造函数的三种场合: 

- 初始化对象时，Test t(t1); 和 Test t = t1;
- 形参实参传递时；
- 返回值为对象时，会创建一个无名的临时变量，(此时相当于对象给对象赋值),返回的是一个新的匿名对象。

## 三、赋值语句

赋值语句系统也有默认的，是各成员之间相互赋值。

```cpp
void operator=(const Test t);
```

赋值语句在对象赋值时调用，可以说是对=的重载；

此时const只是为了保护不被修改，t调用拷贝构造函数(对象给对象初始化赋值)，但是为了时间和空间的效率，此处用引用更好；

```cpp
void operator=(const Test &t);
```

此时不能连等赋值，t = t1 = t2;   这个的本质就是：t.operator=(t1.operator=(t2));所以的有返回值呀。


```cpp
Test& operator=(const Test &t){
  if(this != &t){
   data = t.data;
  }
    
  return *this;   
}
```

因为不是创建临时无名对象，所以可以引用返回；临时的不行，返回时空间就已经析构了。适用场合：Test t;  t = t1 =t2 = t3;(对象已经初始化过了，此时就叫做赋值)；

## 四、函数的优化调用

```cpp
#include<iostream>
using namespace std;
class Test{
public:
    Test(int d = 0) : data(d){
        cout<<"Create Test Object"<<this<<endl;
    }
    Test(const Test &t){
        cout<<"Copy Create Test Object"<<this<<endl;
        data = t.data;
    }
    Test& operator=(const Test &t){
        cout<<"Assign : "<<this<<endl;
        if(this != &t){
            data = t.data;
        }
        return *this;
    }
    ~Test(){
        cout<<"Free Test Object"<<endl;
    }
public:
    int GetData()const{
        return data;
    }
private:
    int data;
};
Test fun(Test x){
    int value = x.GetData();
    Test tmp(value);   //创建临时tmp对象，调用构造函数
    return tmp;        //返回值为对象，调用拷贝构造，借助中间桥梁返回；
}                      //立马先析构tmp和x临时对象，在进行赋值语句，最后析构其他对象；
int main(void){
    Test t1(100);     //创建对象t1，调用构造函数
    Test t2;          //创建对象t2，调用构造函数
    t2 = fun(t1);     //形参，实参传递，调用拷贝构造
    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcge5kPqNk0Jp3VeGvAgWQPOJibnIfibrNew2v1FV2Hd0Mib0uNB35OjEnoicA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

优化以上的代码，使节省空间和时间：

```cpp
Test fun(Test &x){
    int value = x.GetData();
    return Test(value);  //创建临时无名对象，编译器直接认为：直接就是这个t2对象
}

int main(void){
    Test t1(100);      //创建对象t1
    Test t2 = fun(t1); //不用再调用赋值语句；

    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeCVfZPicdn43TTnQhZzjnB5ITE8dRfhnUCxsrewgsIIXTm8CQ973TZng/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

效率最低-->代码的优化。

## 五、说明

原创文章链接：[C++从零入门学习系列（4）---引用，拷贝构造，赋值语句](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483875&idx=1&sn=9e8e73abf129dde7857c5114be4a44b4&chksm=f94c8bdece3b02c8a57dd6af372068806fa1d2599050c06c18641067cc74d252c252015aeb57&scene=21#wechat_redirect)


---


## C++从零入门学习系列_默认函数_深拷贝与浅拷贝_深赋值与浅赋值

- [一、C++ 默认函数](#一c-默认函数)
- [二、深拷贝与浅拷贝](#二深拷贝与浅拷贝)
- [三、说明](#三说明)

这篇文章是 C++ 面试高频知识点，必须熟悉默认函数、深浅拷贝、赋值！

## 一、C++ 默认函数

**C++中什么都不写，就有6个默认函数，由系统自动提供：**
***构造函数，拷贝构造函数，赋值语句，析构函数，对一般对象的取地址符，对常对象的取地址重载；***

对&运算符的重载：

```cpp
Test t3;

Test *pt = &t3;

Test* operator&(){

    return this;
}
```

对常对象的取地址重载：

```cpp
const Test t4;

const Test *pt1 = &t4;



const Test* operator&()const{

    return this;
}
```

## 二、深拷贝与浅拷贝

```cpp
#include<iostream>
#include<string.h>
#include<malloc.h>
using namespace std;

class String{
public:
    String(const char *str = ""){
        if(str == NULL){
            data = new char;
            data[0] = 0;
        }else{
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        }
    }
    ~String(){
        delete []data;
    }
private:
    char *data;
};

int main(void){
    String t1("abcdef");
    String t2 = t1;
    String t3("hello");
    t3 = t1;

    return 0;
}
```

运行结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgec73A8YtxWLtMRFY8UyVknBrJxAONPAN7PQHGEeFvXgibjjPx7teHlaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

可以知道，程序崩了，我们用的是系统默认的拷贝构造函数和赋值语句，此时只是各成员之间的赋值。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeqhoE8NtPqmAnL2libRDbBUhmYIfy4njIP5cAbscOqxhefayELELUPew/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**两个对象通过默认的拷贝构造，成员data之间相互赋值，使得data不同，data的值相同，指向了同一空间；**

**此时在最后调用析构函数时，形成了对同一空间的多次释放，是错误操作！！！，这就是浅拷贝。**

**两个对象通过默认的赋值语句，成员data之间相互赋值，使得data不同，data的值相同，指向了同一空间，浅赋值。**

解决方案，此时应给自己写拷贝构造和赋值语句，达成深拷贝：

```cpp
String(const String &s){
    data = new char[strlen(s.data) + 1];
    strcpy(data, s.data);
}
String& operator=(const String &s){
    if(this != &s){
        delete []data;
        data = new char[strlen(s.data) + 1];
        strcpy(data, s.data);
    }

    return *this;
}
```

深拷贝和深赋值的意思：**就是重新申请空间，各自保存自己的，最后在自己释放自己的，保证了对内存访问的安全性；**

深赋值应当注意以下四步：

1. 判断自己是否给自己赋值；
2. **释放原有空间  //有可能在构造对象时，已经指向了某一空间，此时就得先释放，不然就内存泄漏；**
3. 申请空间进行赋值；
4. 返回引用空间。

## 三、说明

原创文章链接：[C++从零入门学习系列（5）---默认函数，深拷贝与浅拷贝，深赋值与浅赋值](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483882&idx=1&sn=b32b37caedfd49614907fda2ba12476b&chksm=f94c8bd7ce3b02c108f42e685ddc248deebdc6c6a6d0b40c03b7b48c7e88ab141e466a590c18&scene=21#wechat_redirect)


---


## C++从零入门学习系列_写时拷贝_引用计数器模型

- [一、深浅拷贝的使用时机](#一深浅拷贝的使用时机)
- [二、引用计数器模型](#二引用计数器模型)
- [三、写时拷贝](#三写时拷贝)
- [四、说明](#四说明)

## 一、深浅拷贝的使用时机

- 浅拷贝：对只读数据共用一份空间，且只释放一次空间；
- 深拷贝：数据的修改，的不同空间；

## 二、引用计数器模型

- 使用变量use_count，来记载初始化对象个数；
- static模型(此处只用浅拷贝与浅赋值)。

```cpp
#include<iostream>
#include<string.h>
#include<malloc.h>
using namespace std;

class String{
public:
    String(const char *str = ""){
        if(str == NULL){
            data = new char;
            data[0] = 0;
        }else{
            data = new char[strlen(str) + 1];
            strcpy(data,str);
        }
        use_count++;     //每新创建一个对象，对引用计数器++；
    }
    String(const String &s){
        data = s.data;
        use_count++;      //创建出新的对象，use_count++；
    }
 //此处先不写赋值语句
    ~String(){
        if(--use_count == 0){  //当引用计数器减为0时，就是每次行析构对象时，都对它减一次，直到为0才释放空间，
            delete []data;
            data = NULL;
        }
    }
public:
    char* GetString()const{
        return data;
    }
private:
    char *data;
    static int use_count;   //此处use_count只有一份，负责记载创建了多少个对象；
};

int String::use_count = 0;  //C++中的静态变量全局只有一份，可以再类外进行初始化；

int main(void)
{
    String s1("hello");
    cout<<s1.GetString()<<endl;
    String s2;
    s2 = s1;  //浅赋值，调用默认的；
    cout<<s2.GetString()<<endl;
    String s3("xyz"); //创建t3对象，要出问题了；(对其就只创建出来，不在进行赋值语句等操作)；此时的情况是：已经有两个对象，其成员data指向同一空间，此时又有一个data指向另一个空
                      //间，但是use_count为0才释放空间，只释放一份，所以肯定有内存泄漏！！！
    return 0;
}
```

上面的static浅拷贝其实存在很大的问题，当t3对象创建时，use_count会加1；

当调用析构函数时，每次减1，为0时，释放空间。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgefjMrqfJ31OO1GYxHYlKrH5NJoF5oS16X2FhqU3djmu6a2uYFlydw8Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、写时拷贝

浅拷贝与深拷贝联合使用，看实际需求对其编写，此时我希望，对数据读时共用一份数据，需要修改时，在单独开辟空间进行修改，在进行改写，并且对象(初始化)应该有自己的data和use_count，赋值语句时共用一份就行，此时就需要句柄了，这就是写时拷贝；

具体完整代码如下：

```cpp
#include<iostream>
#include<malloc.h>
#include<string.h>
using namespace std;
class String;
class String_rep{        // 这个类是封装在内部供我们程序员自己使用的。
    friend class String;  //友元类，可以访问私有数据。
public:
    String_rep(const char *str = ""):use_count(0){  //构造函数的初始化
        if(str == NULL){
            data = new char[1];
            data[0] = 0;
        }else{
            data = new char[strlen(str)+1];
            strcpy(data,str);
        }
    }
    String_rep(const String_rep &rep);
    String_rep& operator=(const String_rep &rep);
    ~String_rep(){
        delete []data;
        data = NULL;
    }
public:
    void increment(){  
        use_count++;
    }
    void decrement(){   //这个函数至关重要，写了一个释放空间的函数，要在其后赋值语句中使用；
        if(--use_count == 0)
            delete this;
    }
    int use_count_()const{
        return use_count;
    }
public:
    char *getdata()const{
        return data;
    }
private:
    char *data;
    int use_count;
};
class String{
public:
    String(const char *str = ""):rep(new String_rep(str)){
        rep->increment();
    }
    String(const String &s){
        rep = s.rep;
        rep->increment();
    }
    String& operator=(const String &s){
        if(this != &s){
            rep->decrement();
            rep = s.rep;
            rep->increment();
        }
        return *this;
    }
    ~String(){
        rep->decrement();
    }
public:
    int use_count()const{
        return rep->use_count_();
    }
    void print()const{
        cout<<rep->data<<endl;
    }
    void toupper(){      //这个函数提供的意义：对其要改的对象重新申请空间，进行改写，使相互之间不影响。
        if(rep->use_count_() > 1){ //对象个数大于1才进行拷贝出来重新写，只有一个就直接在其上进行修改。
            String_rep *new_rep = new String_rep(rep->data);
            this->rep->decrement();
            rep = new_rep;
            rep->increment();
        }
        char *pch = rep->data;
        while(*pch){
            *pch -= 32;
            pch++;
        }
    }
private:
    String_rep *rep; // 句柄
};
int main(){
    String s1("hello");
    String s2 = s1;
    String s3("xyz");
    s3 = s2;
    s1.toupper();
    s1.print();
    cout<<"s1 count = "<<s1.use_count()<<endl;
    s2.print();
    cout<<"s2 count = "<<s2.use_count()<<endl;
    s3.print();
    cout<<"s3 count = "<<s3.use_count()<<endl;
    return 0;
}
```

以上的代码就可以达到目的，每次创建对象都有自己的data和use_count(调用构造函数),在赋值语句时先释放原有空间，在进行浅拷贝，构造函数时也是浅拷贝，对其进行了各自空间的管理与释放，并且在修改数据时拷贝出来一份即可。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgenEw1pWicgISD9iaZeMoMGsPB38StN5nsxnLQ1t2wvcvtx6PccEEH7icibQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

分析如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcge5OzqoPicTDJyL6Hz2R10wGw4uhwagA5XY2BRwYeADnqgUJCAJYfGtUA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

关于以上还有个问题：

```cpp
void decrement(){   
  if(--use_count == 0)
   delete this;
}
```

为什么不在String类的析构函数中写delete呢？

**原因：析构函数只有在对象释放是才调用，而在此时，通过赋值语句要释放空间，析构函数此时就不能及时释放原有空间，会造成内存泄漏，所以写一个释放空间的函数，内部有delete，会先调用析构函数，达到了及时释放空间的目的！**

以上只是对写时拷贝的粗浅理解。

## 四、说明

原创文章链接：[C++从零入门学习系列（6）---写时拷贝，引用计数器模型](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483883&idx=1&sn=0fbb190f803b577d0a91fa596d3812e6&chksm=f94c8bd6ce3b02c010313567eb28744033dc72ab666b3989570a1dcf1692986d3229780835d5&scene=21#wechat_redirect)


---
