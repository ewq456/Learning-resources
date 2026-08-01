# STL常用算法


## C++进阶系列之STL_find_if()_plus_for_each()的用法

- [一、STL算法->find_if()](#一stl算法-find_if)
- [二、STL算法->plus的使用](#二stl算法-plus的使用)
- [三、STL算法->for_each()](#三stl算法-for_each)
- [四、for_each()和transform()的区别](#四for_each和transform的区别)
- [五、说明](#五说明)

## 一、STL算法->find_if()

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

template<typename Type>
class IsDiv{
    public:
        IsDiv(const Type &divisor){
            this->divisor = divisor;
        }   

        bool operator()(Type &t){
            return t%divisor == 0;
        }   
    protected:
    private:
        Type divisor;
};

int main(void){
    vector<int> v2; 

    for(int i = 10; i < 33; i++){
        v2.push_back(i);
    }   
    int a = 4;
    IsDiv<int> myDiv(a);

    //find_if(v2.begin(), v2.end(), myDiv);
    vector<int>::iterator it;
    it =find_if(v2.begin(), v2.end(), IsDiv<int>(a) );
    if(it == v2.end()){
        cout<<"容器中没有值是4的元素"<<endl;
    }else{
        cout<<"第一个被4整除的元素是:"<<*it<<endl;
    }

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvoqFPicA0e9NNqZ9OCMx8JHsYgnEuTHAgtiavJhrBd4lGpNC1DjpoO6Ug/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、STL算法->plus的使用

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//plus 预定义好的函数对象,能实现不同数据 + 算法；
//实现了数据类型和算法的分离======》通过函数对象技术实现的;
//
//思考,怎么知道plus<type>是2个参数------>多看看源码;
void main21(){
    plus<int> intAdd;
    int x = 10;
    int y = 20;

    int z = intAdd(x, y);
    cout<<"z:"<<z<<endl;

    plus<string> stringAdd;

    string s1 = "aaa";
    string s2 = "bbb";
    string s3 = stringAdd(s1, s2);
    cout<<"s3:"<<s3<<endl;

    vector<string> v1;
    v1.push_back("bbb");
    v1.push_back("aaa");
    v1.push_back("ccc");
    v1.push_back("zzz");
    v1.push_back("ccc");
    v1.push_back("ccc");

    sort(v1.begin(), v1.end(), greater<string>()); //降序排列;
    vector<string>::iterator it;
    for(it = v1.begin(); it != v1.end(); it++){
        cout<<*it<<endl;
    }
    //求“ccc”出现的字符串的个数;
    string sc = "ccc"; //函数适配器：将函数和参数强行绑定;
    //equal_to<string>有2个参数，left参数来自容器,right参数来自sc,
    //bind2nd就是函数适配器:把预定义函数对象和第二个参数进行绑定;`
    int num = count_if(v1.begin(), v1.end(), bind2nd(equal_to<string>(), sc));
    cout<<"num:"<<num<<endl;
}

int main(void){
    main21();

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvZM1bRM6q4sdyx2hzgOnEialSsggaKfcfDxRuQic0icu1ibP6XfgwlepoCg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、STL算法->for_each()

代码如下

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

void printV(vector<int> &v){
    vector<int>::iterator it;

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

void showElem(int &n){
    cout<<n<<" ";
}

class MyShow{
    public:
        MyShow(){
            num = 0;
        }
    void operator()(int &n){
        num++;
        cout<<n<<" ";
    }
    void printNum(){
        cout<<"num :"<<num<<endl;
    }
    private:
        int num;
};

int main(void){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    printV(v1);

    //第三个参数是：函数对象/回掉函数
    //for_each(v1.begin(), v1.end(), showElem)；//利用的是回调函数
    for_each(v1.begin(), v1.end(), MyShow()); //利用的是函数对象(这个类中重载了())
    //函数的返回值是函数对象
    cout<<endl;    
    MyShow my1 = for_each(v1.begin(), v1.end(), MyShow()); //利用的是函数对象(这个类中重载了())
    my1.printNum();

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwveJVvVuSPViaiaIdvlYLuZxKd0OMw0xLliaiaA5fomaibVR0PUJ9xguDZngw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、for_each()和transform()的区别

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

void showElem(int &n){
    cout<<n<<" ";
} 
int showElem2(int &n){
    cout<<n<<" ";
    return n;
} 

//for_each和transform的本质区别：
//结论：
//1、一般情况下,for_each所使用的函数对象,参数是引用,没有返回值;
//2、transform所使用的函数对象,参数一般不使用引用,而是还有返回值;
int main(void){
    vector<int> v1; 
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    
    vector<int> v2 = v1; 

    for_each(v1.begin(), v1.end(), showElem);
    transform(v2.begin(), v2.end(), v2.begin(), showElem2);//transform对回调函数的要求;返回值必须有
    cout<<endl;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvXjppSfsia7icm7kp3wGxIHyPqW5dHf4YeE1ZS27HPcgYSNu9acKdVqvA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之STL（9）---find_if(),plus,for_each()的用法](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484013&idx=1&sn=33af2e60e7c8648ff419a87dde7cd24a&chksm=f94c8850ce3b0146b76800c82e23ce29da8f0286cb919a66da29524c0c04b4109cf1d52093ef&scene=21#wechat_redirect)


---


## C++进阶系列之STL_STL查找_排序_替换_集合算法

- [一、STL查找算法](#一stl查找算法)
- [二、STL排序算法](#二stl排序算法)
- [三、STL拷贝替换](#三stl拷贝替换)
- [四、STL集合算法](#四stl集合算法)
- [五、说明](#五说明)

## 一、STL查找算法

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//查找算法！！！
void main_adjacent_find(){
    vector<int> v1; 

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(5);

    //查找第一个元素重复的位置;
    vector<int>::iterator it; 
    it = adjacent_find(v1.begin(), v1.end()); //查找第一个重复出现的数字;
    if(it == v1.end()){
        cout<<"没有找到重复的元素"<<endl;
    }else{
        cout<<*it<<endl;
    }   

    int index = distance(v1.begin(), it); //从头开始,的知当前迭代器的指针所在的数组下标处;
    cout<<"index:"<<index<<endl;
}

void main_binary_search(){
    vector<int> v1;

    //0 1 2 3 4 5.......n-1
    //二分法,10次就可以找到了;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    bool b = binary_search(v1.begin(), v1.end(), 7);
    if(b == true){
        cout<<"找到了"<<endl;
    }else{
        cout<<"没找到"<<endl;
    }
}

void main_count(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);   
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(7);
    v1.push_back(9);
    v1.push_back(7);

    int num = count(v1.begin(), v1.end(), 7);

    cout<<"num:"<<num<<endl;
}

bool GreatThree(int num){
    if(num > 3){
        return true;
    }
    return false;
}

void main_count_if(){
    vector<int> v1;     

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    int num = count_if(v1.begin(), v1.end(), GreatThree);
    cout<<"num:"<<num<<endl;
}

void main_find(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    vector<int>::iterator it;
    it = find(v1.begin(), v1.end(), 5);
    cout<<*it<<endl;
}    
void main_find_if(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    vector<int>::iterator it;
    it = find_if(v1.begin(), v1.end(), GreatThree); //返回的是第一个回调函数所指向的迭代器;
    cout<<*it<<endl;
}
int main(void){
    main_adjacent_find();   //查找第一个重复的元素;
    main_binary_search();  //二分法查找某一个元素;
    main_count();  //查找某一个元素出现的次数; 针对基础数据类型
    main_count_if(); //用一个一元谓词,可以查找大于某一个数字的个数; 针对自定义的数据类型
    main_find();  //查找某一数据，通过迭代器指出; 针对基础数据类型
    main_find_if();  //查找某一数据，通过迭代器指出; 针对自定义数据类型;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvOGVxMcraBNDyZ288KttxsPtcvc6fk6K06hAWy30fQ9UJD3RiaR0eApg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、STL排序算法

代码如下：

```cpp
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//排序算法
void printV(vector<int> &v){
    vector<int>::iterator it; 

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;
}

void main_merge(){
    vector<int> v1; 
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);

    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

    printV(v3);
}

class Student{
    public:
        Student(string name, int id){
            m_name = name;
            m_id = id;
        }
    public:
        string m_name;
        int m_id;
};

bool Compare(Student s1, Student s2){
    return (s1.m_id < s2.m_id);
}

void main_sort(){
    Student s1("老大", 1);
    Student s2("老二", 2);    
    Student s3("老三", 3);
    Student s4("老四", 4);

    vector<Student> v1;
    v1.push_back(s4);
    v1.push_back(s1);
    v1.push_back(s3);
    v1.push_back(s2);

    vector<Student>::iterator it;
    for(it = v1.begin(); it != v1.end(); it++){
        cout<<it->m_id<<"\t"<<it->m_name<<endl;
    }

    //sort()要对自定义的数据类型进行排序,就的进行自定义数据类型的排序;
    sort(v1.begin(), v1.end(), Compare); //Compare就是谓词,谓词就是函数名称,返回值为bool类型;

    for(it = v1.begin(); it != v1.end(); it++){
        cout<<it->m_id<<"\t"<<it->m_name<<endl;
    }
}

void main_random_shuffle(){
    vector<int> v1;    
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    //对动态数组进行随机打乱
    random_shuffle(v1.begin(), v1.end());

    printV(v1);

    //对字符串随机的打乱顺序;
    string str = "abcdefg";
    random_shuffle(str.begin(), str.end());;
    cout<<"str:"<<str<<endl;
}

void main_reverse(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    reverse(v1.begin(), v1.end());
    printV(v1);  
}

int main(void){
    main_merge(); //归并排序
    main_sort();
    main_random_shuffle();
    main_reverse();

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvDNy6aryFTH097BmzCcZOUiaaGHbAMpzYvdxfCwNSpJiciasoumxha4Amw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、STL拷贝替换

代码如下：

```cpp
#include<iostream>
#include<numeric> //accumulate()函数的头文件;
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//拷贝替换

void printV(vector<int> &v){
    vector<int>::iterator it;

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

void main_copy(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.resize(v1.size());  //调整容器大小的函数;

    copy(v1.begin(), v1.end(), v2.begin());  //拷贝容器函数;

    printV(v2);

}

void main_replace(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(5);

    replace(v1.begin(), v1.end(), 3, 8);  //替换函数,将前面的数据都用后面的数据替换;
    printV(v1);
}

bool great_equal(int &n){
    if(n >= 5){
        return true;
    }else{
        return false;
    }
}    
void main_replace_if(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(8);
    v1.push_back(8);
    v1.push_back(8);
    v1.push_back(5);

    replace_if(v1.begin(), v1.end(), great_equal, 1);   //这里就是可以替换范围内的数据,通过谓词进行控>
制!!,将great_equal范围内的数字(返回值为真的)进行替换!!!
    printV(v1);
}

void main_swap(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2;
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);

    swap(v1, v2);  //交换了v1、v2容器中的内容!!!
    printV(v1);
}

void main_accumulate(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    int tmp = accumulate(v1.begin(), v1.end(), 100);  //求和函数,加上一个初始值100;
    cout<<tmp<<endl;

}

void main_fill(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    fill(v1.begin(), v1.end(), 8);  //将容器中的数值全都改为8;
    printV(v1);
}
int main(void){
    main_copy();  //拷贝
    main_replace();  //替换 基础数据类型
    main_replace_if();  //替换范围 自定义数据类型
    main_swap();  //交换容器中的内容
    main_accumulate(); //求和函数
    main_fill();


    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvrFwZtlEpRYuDh4AwRibUXIolRFRme0j4SEKYmsiclV7ZvcXm466WdbGQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、STL集合算法

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;

void printV(vector<int> &v){
    vector<int>::iterator it; 

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;
}
//集合
int main(void){
    vector<int> v1; 
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(1);
    vector<int> v3; 
    v3.resize(v1.size() + v2.size());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin()); //集合中取并集;没有填满的空间默，认为0;
    printV(v3);

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8Ewvx02uhrVZVS7INNgqh6sKKdceVohUzXbFzyUaUQiboZtRuCLTb3KjXTg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之STL（10）---STL查找、排序、替换、集合算法](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484014&idx=1&sn=13eae32f965cd1cdbf6d590b9e05aa43&chksm=f94c8853ce3b0145188f0b4d516b83b2ff5a887fc840b123de29a6cd5bef70633eb6bced1c56&scene=21#wechat_redirect)


---
