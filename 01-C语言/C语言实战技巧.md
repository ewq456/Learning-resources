# C语言实战技巧与心得


## C语言中的一些不足

- [一、对于 register 关键字](#一对于-register-关键字)
- [二、变量可以重复定义](#二变量可以重复定义)
- [三、对于函数的返回值和函数的参数](#三对于函数的返回值和函数的参数)
- [四、三目运算符](#四三目运算符)
- [五、对于C语言中的const](#五对于c语言中的const)
- [六、说明](#六说明)

编程的学习，绝非一朝一夕，只有日积月累，长久的坚持学习，去编程，对我们的影响将是潜移默化的，最终技术的提升是水到渠成，让我们一起开启 Linux C/C++ 之旅.

## 一、对于 register 关键字

1、C 程序

```c
#include<stdio.h>

int main(void){
   register int a = 10;

   printf("&a = %p\n", &a);
   return 0;
}
```

运行结果:

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjm9Lb7wJT0fXjFHCfp0PnxrDx1mQoY5e3QtiaiaibeM9YSicgcJh4iaTJibww/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、C++程序

```cpp
#include<iostream>
#include<stdio.h>
using namespace std;

int main(void){
   register int a = 10;

   printf("&a = %p\n", &a);
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOj9hKe5cjbPVR2vvPwBzScic1w73IsibDiajfibav74RIo89INLxVYpgHbKw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**C语言中register(寄存器存储变量)，不能对这个所修饰的变量进行取地址。**

**C++中可以对register修饰的变量进行取地址，因为C++编译器内部做好了优化处理。**

## 二、变量可以重复定义

代码如下

```c
#include<stdio.h>

int g_a;   //在这里变量都已经定义了
int g_a = 100;
int main(void){
   printf("%d\n", g_a);
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjqaJNhKI8w1khVZ05ZY9WD6b5SgQy8Mrq9R4eJaibAON8Yh6V2F2LN4g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C编译器检查不严格，可以这样重复定义变量。**

## 三、对于函数的返回值和函数的参数

代码如下

```c
#include<stdio.h>

//C++编译器是非常严格的
f(i){  
   printf("%d\n", i);
}

g(){    //C语言的编译器是不严格的(存在默认类型);
   return 5;
}

int main(void){
   f('A');

   printf("%d\n", g(1, 2, 3, 4, 5, 6));
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjRDPxtgFXOhqVADs4sLgk5bWSXFB8s5iafyZNBzv3NNIkThiahhLvXcaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C语言对于函数的参数和返回值的要求不是那么的严格意义上的。**

## 四、三目运算符

代码如下

```c
#include<stdio.h>

int main(void){
   int a = 10;
   int b = 20;
   //在C语言中,表达式的结果,存放在寄存器
   //在C语言中,表达式返回的是变量的值
   //(a < b ? a : b)  (里面返回的是常量,常量不能&)  = 30;
   //10 = 30;
   //返回的是一段连续的空间即可,即一段内存的首地址;
   *(a < b ? &a : &b) = 30;   //C++编译器对C++语言的优化,内部就是这样实现的;

   printf("a = %d, b = %d\n", a, b);
   return 0;

}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjciaehhRJiauvkZTZ9hW1Fibrw17ScukDmeicFsULzvZngIS9RpUGCFaWFQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**在C语言中，三目运算符的返回时一个值，不是一段连续的内存空间，所以对其不能进行赋值操作。**

## 五、对于C语言中的const

1、代码如下

```c
#include<stdio.h>

typedef int* TYPE;

int main(void){
   //TYPE const a;
   const TYPE a;
   int b = 10;
   int c = 20;

   a = &b;
   a = &c;

   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjNKPD2vgTTicicU13x1icaZDnNkEABw0Ctpibherntz72O9GnRt8P7icGwXg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

原因分析：类比法，const int a; <===>  int const a;  Type的数据类型是：int *

**此时的情况是：const Type a; <===> Type const a;  此时可以说明的是：const修饰的是指针变量的值，是常量，不能更改，而这个指针所指向空间的值是可以改变的。**

2、代码如下

```c
#include<stdio.h>

int main(void){

   //C语言中的const是一个冒牌货
   const int a = 10;//只读变量,在内存中分配空间
   int *p = (int *)&a;

   *p = 20; //间接赋值
   printf("a = %d\n", a);
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjYrPGUyBOHibDH9r0Kic31msHAg9iaUACuqw1826xgtj8I8e8233kbCKvg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**在C语言中，const修饰的是一个冒牌货，叫做只读变量，不是真正意义上的常量，可以通过指针间接赋值对其修改。**

在C++中的情况，代码如下

```c++
#include<stdio.h>
#include<iostream>
using namespace std;

int main(void){
   const int a = 10; //符号表,键值对的存储
   int *p = (int *)&a;//&,此时另外分配了内存空间,时机:编译器在编译期间;
   
   //C++语言中const是一个真正的常量
   *p = 20; //间接赋值
   printf("a = %d\n", a);
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjXdLD397mabudiaVWvDaNfEic6mmiaovKeFVu6s610gCXQw9H0V5ojfQFw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C++中的const所修饰的是真正的常量，在对其进行&运算时，将会开辟另外的内存空间。**

## 六、说明

原创文章链接：[C 语言中的一些不足](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483665&idx=1&sn=d0f838ba51686bbdde5a9c9c51c54a76&chksm=f94c8b2cce3b023a1a4d2c879d54f762752f9d4979db704d4c93ba860f0df78aef771ef93565&scene=21#wechat_redirect)


---


## 我为什么建议大家一定的会C语言

- [一、C 的认识](#一c-的认识)
- [二、C 的结缘](#二c-的结缘)
- [三、C 的体会](#三c-的体会)
- [四、C 的世界](#四c-的世界)
- [五、说明](#五说明)

在如今 Python 和 Java 大火的市场前景下，我还是建议，如果你还在学校读书，或者你有大把的空闲时间，不着急去找工作，那就静下心来，好好学习一下 C 语言，会让你受益终生，也会让你的编程之路走的更远。

## 一、C 的认识

1、C 语言作为编程最古老的语言之一，至今走过了快半个世纪，久经考验，仍然是宝刀未老，在排行榜上常年名列前茅，这铁铮铮的事实还不能说明问题吗？其设计的精髓，其内涵思想，都是值得当下的我们学习与借鉴的。

2、C 语言作为我接触编程的开始，对我的影响很大，带我入了 IT 这行，我本人也是极其的喜欢 C 语言，C 语言涉及了很多底层的知识，比如：内存、寻址、如果你不懂操作系统相关知识、是很难学会 C 语言的，而 Windows、Linux、Unix 等操作系统的内核 90% 以上都使用 C 语言开发，C 语言是一门直通底层的语言。

3、学习 C 语言，这仅仅是基础部分，想靠这个去找工作，是远远不够的，在有了 C 的基础之上，看你自己的兴趣和方向而定，到时候，想走后台，选择 Java C++ Go 之一可以去学，想走人工智能领域的，可以去学 Python，想走运维的，可以深入Linux领域，还有安卓、前端等，到那个时候，才是天高任鸟飞，海阔凭鱼跃。

4、学习 C 语言并不一定要从事与 C 语言有关的开发工作，**但是可以给你养成一种学习编程的思考方式，和逻辑推理能力**，其它很多的语言在语法上都和 C 语言类似， Java、C++、C#、PHP、JavaScript 等，学完 C 语言再学这些语言都轻松很多。

5、C 语言能干什么，据我所知：

- C 语言主要用于底层开发，操作系统，搜索引擎；

- Linux 嵌入式方向，单片机这些，可以开发硬件驱动，让硬件和操作系统连接起，通过软件操作硬件；

- 开发系统组件或服务（一般是对效率要求比较高的），用于支撑上层应用；

6、不要给我说 C 语言入门比较难，我也是非科班出身，一路全凭自己摸索，自己的智商并不高，我能做的到，代表大部分人应该都可以，换一种角度思考，如果难的都搞定了，简单的还是问题吗？

## 二、C 的结缘

我说说我自己本人的亲身经历，我在大二的时候，开始接触 C，大半年的时间，总是理解不了指针，被指针的各种用法所深深的折磨，C 也仅仅是掌握了皮毛，那时候的自己，就觉得自己是不是不适合学习编程，自己太笨了，总也学不会。

我现在还记得清楚，自己当时是上课前，趴在桌子上休息，不知道怎么突然想到了指针，灵光一现，明白了指针是怎么回事，我当时非常的激动，立马跑回宿舍，拿起电脑进行了一系列的验证，都是成功的，那可是我学习编程历时半年，第一次有成就感的时候，很激励自己，之后的自己就豁然开朗，对编程的认知提升了一个层次，在理解其他的知识点就感觉轻松，容易多了，那次经历真的很玄学。

之后的自己在编程的路上，也遇到了种种困难，但是每每想起指针的那件事情，我就信心满怀，**我觉得该经历的迟早都会来，早点经历过、被折磨过，自己才能有提升，经历过的人都懂**。

## 三、C 的体会

大学期间我是搞 Linux C/C++ 服务器开发的，对于 Linux C/C++ 是相当的熟悉，现在的我在公司中是一名算法工程师，由一名后台转算法，仅仅用了 3 个月的时间，但是为什么我能这么快的成功转型呢？

**扎实的基础功底、快速的学习能力、解决问题的能力、以及个人潜力**。

扎实的基础功底很重要，基础是什么：数据结构 + 算法，操作系统 + 计算机网络，Linux + C，数据库 + 设计模式，那么之中就有一门 C 语言，C 是学习编程的基础，很锻炼一个人的逻辑思维能力。

快速学习的能力必须具备，干 IT 这行，技术在不断的更新迭代，就的不断的去学习，树立终生学习的理念，牢记一句话，在校期间，不管你学的是什么编程语言，什么编程技术，工作了，可能你以前学的那些都用不上（反正我以前学的基本都用不上，自己来公司从 0 开始），这是很正常的，但编程素养和编程习惯在就行了，这些都是相通的，公司需要我做什么，我快速学习就好。

语言是工具，重要的是思想，我很认同这句话，我以前没接触过 go，在百度实习的时候，我导师还给了我 1 周的时间去熟悉，才上项目，以前没咋用 Python 写过代码，来了之后，直接 Python 上项目，现在的我，天天是：Python + sql，我想说的是，一门(**C 是基础，不算**)玩的 6 了，其他的还用学吗？直接动手干就是了。

个人潜力自己平时的多去琢磨，去研究技术，个人潜力是招人很看重的一方面，公司在面试的时候，很注重一个人在这方面的发展潜力，一般是通过算法题进行考察，算法强的，来了之后稍加培养就好（我想说的是，面试的时候，你敢说自己精通算法，国内互联网公司随便挑），公司不仅是面向当下，还是在面向未来在招人。

总之，企业招你是为了干活，你能不能快速的学习，以及将所学到的能否快速的应用到业务开发中，为公司的业务作出贡献，才能体现你的价值，而你就必须具备这种能力。

## 四、C 的世界

一定的对自己有清晰的定位，自己目前是一个什么样的处境，只有全面的认识自己，才能针对当下，做出战略性的方案，深度 > 广度，在互联网行业，对于我们来说，技术过硬让一切成为可能。

我接触 C 语言到现在大概 3 年时间了，我对 C 语言的认知，早已不仅仅停留在使用的层面上，而是对 C 的设计理念，设计哲学所深深的吸引，其人文化的思想，站在计算机独特的视角，以及 C 语言指针的伟大魅力，我被深深的折服其中，在 C 的世界中，充满了好奇心，总想去探索、去发现未知的世界。

C 语言能够让你更加深刻的认识内存和编译原理，了解程序的每一个细节，夯实基本功，站得“低”才能望的远，所以优秀的程序员都会学习 C 语言，你想成为优秀的程序员吗？如果想，就跟我一起探讨 C 之旅。

以上仅仅代表我个人看法，反正我是这么一步一步走过来的。

## 五、说明

原创文章链接：[我为什么建议大家一定的会 C 语言](https://mp.weixin.qq.com/s?__biz=MzU4MjQ3NzEyNA==&mid=2247483813&idx=1&sn=7c085b1b90efa3e67efb2b970ab0a96e&chksm=fdb6f58ecac17c98d1cda202d7fdbbf6f654692fdcbbe7c8d2ed2b331badef0899a6a208c54a&token=1250675081&lang=zh_CN#rd)


---
