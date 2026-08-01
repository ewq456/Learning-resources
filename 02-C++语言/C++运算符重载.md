# C++运算符重载


## C++从零入门学习系列_友元函数_运算符重载const_static

- [一、友元函数](#一友元函数)
- [二、运算符的重载](#二运算符的重载)
  - [2.1、例1：++i 和 i++有什么区别？](#21例1i-和-i有什么区别)
  - [2.2、例2：String类](#22例2string类)
- [三、const和static](#三const和static)
- [四、说明](#四说明)

## 一、友元函数

在类中一般的成员函数具备：

1. 该函数能访问类中的私有部分；
2. 该函数位于类的作用域之中；
3. 该函数必须经由一个对象去激活，也就是说有一个this指针。

友元函数不同之处：

1、在 #include<iostream> using namespace std; 的前提下，必须的类外先声明；

```cpp
class Test;
  void fun();    //有元函数的声明
```

但是在#include<iostream.h>中不用这个有元函数的声明；这是早期头文件的包含。

2、在类内必须声明是朋友，friend(关键字)，函数声明

```cpp
class Test{
  friend void fun();  //朋友没有公有，私有，保护之分，所以限定修饰符在这不起任何作用
}；
```

3、在类外实现方法的定义，此时不用再加friend了；

```cpp
void fun(){
  ..........
}
```

有元函数具有的特性：该函数能访问类的私有数据；不是该类的成员函数，也不需要对象驱动；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwXjgZjVVfkUTDibQPCT5nnDxY0JwQavibFG74RpRkuYDFicFHBvkukQ9yg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

还有友元类，跟其使用一样，类中所有函数均可调用其朋友的私有数据；

## 二、运算符的重载

个人认为C++中运算符的重载很有用，也很重要。这相当于函数的调用，对其的另一种更加人文化的解释，并告诉 C++编译器，遇到该重载运算符时调用此函数。

定义运算符重载的一般格式：
> 返回值类型 类名：：operator重载的运算符(参数列表)；

假如出现复数类：

```cpp
    Complex{
    public:
        .....
    private:
        int real;
        int p_w_picpath;
    }；
```

```cpp
    //主函数中：
    Complex t1(1, 2);
    Complex t2(2, 3);
    Complex t3;
    t3 = t1 + t2;
```

此时t1和t2的类型不定，就得对+进行运算符的重载；使其更符合人文化，其本质不变，t1.operator+(t2);

对象的类型不定，编译器不知道怎么输出，自己就得对<<和>>运算符进行重载，以达到输出对象的目的。还必须是友元函数；

```cpp
class Complex;    //这是第一步，类外声明。
    ostream& operator<<(ostream &out, const Complex &c);
    istream& operator>>(istream &in, Complex &c);
    
class Complex{   //这是第二步，对其在类内说明是朋友。
    friend ostream& operator<<(ostream &out, const Complex &c);
    friend istream& operator>>(istream &in, Complex &c);
};
  
ostream& operator<<(ostream &out, const Complex &c){
    out<<"("<<c.m_real<<","<<c.m_imag<<")";
    return out;   //这是第三步，在类外进行定义。
}
istream& operator>>(istream &in, Complex &c){
    in>>c.m_real>>c.m_imag;
    return in;
}
```

关于这个<<对应一个要输出的值，在定义时，不用endl回车。

对于Complate类的补充，t1 = t2 + 10;  //成员方法重载即可。内部有一个隐藏参数。

```cpp
t1 = 10 + t2;  //没有对象驱动，还要10.operator+(t2);是错的，所以此时用友元函数，传两个参数就是有两个参数。
```

运算符的重载要注意：

1. operator后面是一个合法的运算符，将右操作数做为函数的实参；
2. ++ --前后的问题，用函数重载区分，后加的(int)参数；
3. ?:  .   .*  ::  sizeof不能重载，其它的应该都可以进行重载。

### 2.1、例1：++i 和 i++有什么区别？

对其进行重载，如下：

```cpp
#include<iostream>
using namespace std;

class Int;
ostream& operator<<(ostream &out, const Int &s);

class Int{
    friend ostream& operator<<(ostream &out, const Int &s);
public:
    Int(int m = 0) : t(m){}
    ~Int(){}
public:
    Int& operator++()//++t  先加1，再将此对象的引用返回
    {
        t++;
        return *this;
    }
    Int operator++(int) //t++ 后加的要有一个参数int区分，
    {
        Int tmp(t);    //创建一个临时对象，
        t++;           //原有对象加了一下，
        return tmp;    //返回临时对象，后加。
    }
private:
    int t;
};

ostream& operator<<(ostream &out, const Int &s){
    out<<s.t;
    return out;
}
int main(void){
    Int t1(6);
    Int t2;
    Int t3;

    t2 = ++t1;
    cout<<"t1 = "<<t1<<", t2 = "<<t2<<endl;  //对输出运算符重载了，才能输出对象。
    t3 = t1++;
    cout<<"t1 = "<<t1<<", t3 = "<<t3<<endl;

    return 0;
}

```

运行结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwrntPwnaAdRv0y0pBzG1QxNS08ibEYXX9UcTzrm55AQCCqr6jdPsx0Jg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

从结果可以看出，确是实现了，这块的本质是运算符对++的重载。

**前加，返回的是引用，后加还得调用构造函数和拷贝构造；所以前加++i;效率更高，运行速度也更快。**

### 2.2、例2：String类

```cpp
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String;
ostream& operator<<(ostream &out, const String &str);

class String{
    friend ostream& operator<<(ostream &out, const String &str);
public:
    String(const char *str = ""){
        if(str == NULL){
            data = new char[1];
            data[0] = 0;
        }else{
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        }
    }
    //String(const String &str){}
    String& operator=(const String &str){
        if(this != &str){
            delete []data;
            data = new char[strlen(str.data) + 1];
            strcpy(data, str.data);
        }

        return *this;
    }
    ~String(){
        delete []data;
    }
public:
    String operator+(const String &str){
        char *tmp;

        tmp = new char[strlen(data) + strlen(str.data) + 1];
        strcpy(tmp, data);
        strcat(tmp, str.data);

        return String(tmp);
    }
    void operator+=(const String &str){
        char *new_data = new char[strlen(data) + strlen(str.data) + 1];
        strcpy(new_data, data);
        strcat(new_data, str.data);
        delete []data;
        data = new_data;
/*
        realloc(data, strlen(data) + strlen(str.data) + 1); //此时对原有的数组空间进行动态扩长，
             // 给谁扩长    加上原先，一共要有多长        即原有值不变。
        strcat(data, str.data);
*/
    }
    char operator[](int pos){
        assert(pos >= 0 && pos < strlen(data));
        return data[pos];
    }
    char operator*(){
        return data[0];
    }
    bool operator==(const String &str){
        return strcmp(data, str.data) ? false : true;
    }
    bool operator!=(const String &str){
        return !(*this == str);  //调用==这个编写过的函数
    }
private:
    char *data;
};

ostream& operator<<(ostream &out, const String &str){
    out<<str.data;
    return out;
}

int main(void){
    String s1("hello");
    String s2("world");
    String s3;

    s3 = s1 + s2;
    cout<<s3<<endl;
    s1 += s2;
    cout<<s1<<endl;
    cout<<s1[1]<<endl;
    cout<<*s1<<endl;
    if(s1 == s3){
        cout<<"相等"<<endl;
    }else{
        cout<<"不相等"<<endl;
    }
    if(s1 != s3){
        cout<<"不相等"<<endl;
    }else{
        cout<<"相等"<<endl;
    }
    return 0;
}
```

对其+，+=，[]，*，==，！=进行了运算符的重载，结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwXfibJCKAWrNOACiaNUT5SVqsmSj4W1LXwibqc0NvxEicG47q8AJbKRAvkw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、const和static

在C++中const是非常重要的，现在说明常函数之间的关系：普通函数可以调用常函数，常函数不能调用普通函数(因为没有this)；

```cpp
void fun()const{}
void fun(){}          //一个有const，一个没有，参数类型不一样，所以这是函数的重载！
```

static在C++中有成员和方法，静态成员的在类外初始化；类的静态成员为所有对象所共享。

静态方法：

- 可以调用该类的私有成员；
- 应该位于类的作用域之中；
- 类名直接调用，可以不用方法；

**静态方法只能调用静态成员，和静态函数；非静态的可以调用静态成员或方法。**

## 四、说明

原创文章链接：[C++从零入门学习系列（12）---友元函数 运算符重载const、static](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483921&idx=1&sn=b3cecef86fdf30b8d289e196e65ab3fd&chksm=f94c882cce3b013a68486cad152ccca541b485886cf97424f35c8b5e0800754c49ccd7fbd0b0&scene=21#wechat_redirect)


---


## C++从零入门学习系列_array和string的运算符重载

- [一、array类](#一array类)
- [二、string类](#二string类)
- [三、说明](#三说明)

## 一、array类

```cpp
#include<iostream>
using namespace std;

class Array{
    public:
        Array(int count);
        Array(const Array &t);
        ~Array();
    public:
        void setData(int i, int data);
        int getData(int i);
        int length();
    private:
        int len;
        int *p;
};

Array::Array(int count){
    len = count;
    p = new int[len];
}
//有指针,的进行深拷贝;
Array::Array(const Array &t){
    len = t.len;
    p = new int[len];
    for(int i = 0; i < t.len; i++){
        p[i] = t.p[i];
    }

}
Array::~Array(){
    if(p){
        delete []p;
        p = NULL;
    }

}
void Array::setData(int i, int data){
    p[i] = data;
}
int Array::getData(int i){
    return p[i];
}
int Array::length(){
    return len;
}


int main(void){
    Array array(10);
    int i;

    for(i = 0; i < array.length(); i++){     
        array.setData(i, i);
    }

    for(i = 0; i < array.length(); i++){
        cout<<array.getData(i)<<" ";
    }
    cout<<endl;

    Array array1 = array;
    for(i = 0; i < array1.length(); i++){
        cout<<array1.getData(i)<<" ";
    }
    cout<<endl;


    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8gaDwDbInyH9Z5vyjjicPpQKYp5XzdjzEAnqXiacb3tO2df1j2k9j73zYtA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、string类

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

class MyString{
    public:
        friend ostream& operator<<(ostream &out, const MyString &s1);
        friend istream& operator>>(istream &in, MyString &s2);
        MyString(int len = 0){ //默认参数看我们是否自己开辟大小的空间;
            if(len != 0){ 
                m_len = len;
                m_p = new char[m_len+1];
                memset(m_p, 0, m_len);
            }else{

                m_len = 0;
                m_p = new char[m_len+1];    
                strcpy(m_p, "");
            }   
        }   
        MyString(const char *p){
            if(p == NULL){
                m_len = 0;
                m_p = new char[m_len+1];    
                strcpy(m_p, "");
            }else{
                m_len = strlen(p);
                m_p = new char[m_len+1];
                strcpy(m_p, p);
            }
        }
        MyString(const MyString &s){
            m_len = s.m_len;
            m_p = new char[m_len+1];
            strcpy(m_p, s.m_p);
        }
        MyString& operator=(const MyString &t){
            if(m_p){
                delete []m_p;
                m_p = NULL;
                m_len = 0;
            }

            m_len = t.m_len;
            m_p = new char[m_len+1];
            strcpy(m_p, t.m_p);

            return *this;
        }
        ~MyString(){
            if(m_p) {
                delete []m_p;         
                m_p = NULL;
                m_len = 0;
            }
        }
    public:
        MyString operator=(const char *p){
            if(m_p){
                delete []m_p;
                m_p = NULL;
                m_len = 0;
            }
            if(p == NULL){
                m_len = 0;
                m_p = new char[m_len+1];
                strcpy(m_p, "");
            }else{
                m_len = strlen(p);
                m_p = new char[m_len+1];
                strcpy(m_p, p);
            }

            return *this;
        }
        char& operator[](int index){
            return m_p[index];
        }     
        bool operator==(const char *p)const{  //判断与字符串是否相等,看长度和里面的内容是否相等!!!
            if(p == NULL){
                if(m_len == 0){
                    return true;
                }else{
                    return false;
                }
            }else{
                if(m_len == strlen(p)){
                    return !strcmp(m_p, p);
                }else{
                    return false;
                }
            }
        }
        bool operator==(const MyString &s)const{
            if(m_len != s.m_len){
                return false;
            }

            return !strcmp(m_p, s.m_p);
        }

        bool operator!=(const char *p)const{
            return !(*this == p);
        }   
        bool operator!=(const MyString &s)const{
            return !(*this == s);
        }
        int operator<(const char *p)const{
            return strcmp(m_p, p);
        }
        int operator<(const MyString &s)const{
            return strcmp(m_p, s.m_p);
        }

        int operator>(const char *p)const{
            return strcmp(p, m_p);
        }
        int operator>(const MyString &s)const{
            return strcmp(s.m_p, m_p);
        }
        //怎么样把类的指针露出来.

    public:
        char *c_str(){     
            return m_p;
        }
        const char *c_str2(){
            return m_p;
        }
        int length(){
            return m_len;
        }
    private:
        int m_len;
        char *m_p;
};


ostream& operator<<(ostream &out, const MyString &s1){
    out<<s1.m_p;

    return out;
}

istream& operator>>(istream &in, MyString &s2){
    in>>s2.m_p;

    return in;
}
int main(void){    
    MyString s1;
    MyString s2("s2");
    MyString s3 = s2;
    MyString s4 = "s444444444444";

    s4 = "s22222222222";

    s4 = s2;

    s4[1] = '3';
    printf("%c\n", s4[1]); //测试[]改变值了吗?
    
    cout<<s4<<endl;

    if(s2 == "s2"){
        cout<<"相等"<<endl;
    }else{
        cout<<"不相等"<<endl;
    }

    s3 = "aaa";
    
    int flag = (s3 < "bbb");
    if(flag < 0){
        cout<<"s3小于bbb"<<endl;  
    }else{
        cout<<"s3大于bbb"<<endl;
    }

    s3 = "adasf";
    strcpy(s3.c_str(), "sga");
    cout<<s3<<endl;

    MyString s9(100);//默认输入要开辟字符串的空间大小;
    cout<<"请输入一个数字 :";
    cin>>s9;
    cout<<s9<<endl;

    return 0;
}
```

运行结果:

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8ga2bpqA9858WBqAvqVnwRyn5Ez8rn3GkBDkN31Eo4UtJQ8nteCyXqRpQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、说明

原创文章链接：[C++从零入门学习系列（8）---array和string的运算符重载](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483897&idx=1&sn=8bef60549c28548d57f2893ec89f6107&chksm=f94c8bc4ce3b02d2b854597ccfc47e9fb9150e85e6e5ff9630dd7f80f6b63c746dd04e5c906a&scene=21#wechat_redirect)


---
