# C语言字符串操作


## strlen()_strcmp()_const

- [一、strlen() 函数的实现](#一strlen-函数的实现)
- [二、strcmp() 函数的实现](#二strcmp-函数的实现)
- [三、const 的用法](#三const-的用法)
- [四、说明](#四说明)

在 C 语言中，对于基础库函数的实现，是非常的重要的，很考验一个人的基本功，今天主要是写strlen()、strcmp() 这 2 个常用函数的具体实现。

## 一、strlen() 函数的实现

strlen(char  *str); 主要计算字符串的长度

```c
#include<stdio.h>

int strLen(char *str);
int strLen(char *str){
   int i = 0;
   
   while(*str){
       str++;
       i++;
   }
   
   return i;
}

void main(void){
   char *str = "abcdefg";
   int length;
   
   length = strLen(str);
   printf("%d\n", length);
}
```

## 二、strcmp() 函数的实现

strcmp(char *str1, char *str2); 比较 2 个字符串是否相同。

```c
#include<stdio.h>

int strCmp(char *str1, char *str2);

int strCmp(char *str1, char *str2){
   while(*str1 == *str2 && *str1 && *str2){
       str1++;
       str2++;
   }
   
   return *str1 - *str2;
}

void main(void){
   char *str1 = "hello";
   char *str2 = "hell";
   
   printf("%d\n", strCmp(str1, str2));
}
```

## 三、const 的用法

在 C 语言中，const 是只读。

1. const int a = 100 <=> int const a = 100;  a 空间是只读空间，a 空间的值不能更改；
2. const int *a; <=> int const *a;  *a 的值不能改变，a指针变量的值可以更改；
3. int* const a;  *a 的值可以更改，a 指针变量只读，不能改其值
4. const int* const a;   *a, a 均只读空间，其值不可更改

**const 离谁进，修饰谁，谁就不可更改。**

注意，用 Linux 进行编程，需要注意：

1. Linux 下 64 位与 32 位的区别：int 都是 4 字节的。64 位下，long 8 字节， 指针 8 字节；
2. Linux下注释块：

```c
#if  0 (注释)  1 (不注释)

...........   

#endif 
```

3. gcc -c 只编译不连接  gcc   .c   -o  目标文件 编译和连接
4. objdump -d test (可执行文件) > x86  反汇编文件查看 X86 内容

**编译结果往往与平台，编译器关系很大。**

## 四、说明

原创文章链接：[strlen()、strcmp()、const](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483676&idx=1&sn=c39b0edea41d37e4307d167fdc27ff6f&chksm=f94c8b21ce3b0237b16f899dc228989ce91ff48a98ff172aa52c4fdf0b3072e2caa84bedf2dc&scene=21#wechat_redirect)


---


## char__str1和char_str2[]的详解

- [一、内存管理](#一内存管理)
- [二、指针变量](#二指针变量)
- [三、对char *str1 = "hello world"的深刻理解](#三对char-str1--hello-world的深刻理解)
- [四、说明](#四说明)

学 C 不易，请坚持下去

C 语言的一个知识点：

```c
char *str1 = "hello world" 和 char str2[] = "hello world"; //其区别：
```

## 一、内存管理

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuzR6kYOicR77TNBmibnq7UXqamU05bFIKMI1vARmQz55Zqft6reMS74c6lwZXkRXSV3o87Ulpy6REg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(内存映像图)</p>

如上图所示：只读代码段一般存放的是编写好的程序；

**内存分为了：只读代码段，只读数据段，BSS，堆，栈五个不同区域。**

- 只读数据段放的是常量(字符串常量，数组名称，函数名称)，**只读区域不能更改；**
- BSS 区域存放的是全局变量和 static 静态类变量，又分为未初始化，值都为0，和已初始化区域；
- 堆中存放的是 malloc()，calloc()……申请的空间，不由操作系统回收，必须靠程序员自己通过 free() 回收空间，不然就是内存泄漏；
- 栈中存放的是局部变量，形参变量，栈中空间可被任何函数使用，是数据的可靠性很低；

## 二、指针变量

str1 是指针变量，str1++; right,指针加减整型，结果还是指针。

对于 str2 而言：

```c
char str2[] = "hello world"; <=> char str2[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'}。
```

这是对字符数组初始化，所以 str2 是数组名称(指针常量)，str2++；false，常量不能赋值。

**"hello world"字符串本身就是以 0 结尾的字符数组。**

"hello world"字符串常量在只读数据段，值本身内容不能被更改。

- str1 为指针变量，*str1 = 't'; false,更改的是只读数据段中的区域；
- str2 为数组名称，其空间在栈中申请，*str2 = 't'; true，栈中的数据可以被更改；

## 三、对char *str1 = "hello world"的深刻理解

- strlen(str1);    11
- strlen(str2);    11
- sizeof(str2);    12   数组名称，求字节数，是数组所申请的空间的字节数，在上0结束标志  
- sizeof(str1);    4/8  与平台有关，32位系统下，指针 4 字节，64 位，指针8字节；
- sizeof(*str1);   1    *str1 就是'h'，占用一个字
- sizeof("hello world");   12   字符串常量所占空间；

strlen();   求得是字符串长度，不算那个 0；sizeof()；关键字，单目运算符，求字节数，算字符串的结束标志 0，这就是区别。

数组[]中的值，由初值个数决定。

## 四、说明

原创文章链接：[char *str1 和 char str2[]的详解](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483673&idx=1&sn=af2d886143a8a9c96e063f550d3f1f14&chksm=f94c8b24ce3b0232b6a3f0ca50b0ad89dbd9f9f74ba157d42361e6bea2bc3e27cb9c10938307&scene=21#wechat_redirect)


---


## 实现strcpy()和strstr()函数的多种方法

- [一、编程实现 strcpy() 函数](#一编程实现-strcpy-函数)
- [二、求子串出现在字符串中的次数](#二求子串出现在字符串中的次数)
- [三、去掉字符串的前后空格](#三去掉字符串的前后空格)
- [四、说明](#四说明)

大家好，持续带来 C 中基础知识点，我希望的是，各位有所思考，把代码理解消化，在自己敲一遍，才能有所感受与提升。

## 一、编程实现 strcpy() 函数

1、方法一

```c
#include<stdio.h>

int main(void){
    char str1[80] = "abcdefg";
    char str2[80];
    int i;

    for(i = 0; str1[i]; i++){
        str2[i] = str1[i];
    }   

    str2[i] = 0;
    printf("%s\n", str1);
    printf("%s\n", str2);

    return 0;
}
```

2、方法二，一行核心代码实现字符串复制

```c
#include<stdio.h>

int str_copy(char *str1, char *str2);
int str_copy(char *str1, char *str2){
/*  
    for(; *str1; str1++, str2++){
        *str2 = *str1;
    }
    *str2 = 0;
}

    for(; *str1; ){
        *str2++ = *str1++;
    }

    *str2 = 0;

    while((*str2 = *str1) != 0){
        str1++;     //此时,就不用出循环在赋指为0；
        str2++;
    }

    while((*str2++ = *str1++) != 0);
*/  
    if(str1 == NULL || str2 == NULL){
        return -1; 
    }

    while(*str2++ = *str1++);

    return 0;

int main(void){
    char str1[80] = "abcdefg";
    char str2[80];
    //char *str2 = NULL;
    int ret = 0;

    ret = str_copy(str1, str2);
    if(ret != 0){
        printf("有一个地址为空,所以有错\n");
    }else{
        printf("%s\n", str1);
        printf("%s\n", str2);
    }

    return 0;
}

```

运行结果：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfQvX1uNcTwzticuGT5c2VLT18K5ODQBicLErstUHwUCTcFNqQfxsLPHlw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

## 二、求子串出现在字符串中的次数

```c
#include<stdio.h>
#include<string.h>

void strstrCount(char *p, char *q, int *count);
void strstrCount(char *p, char *q, int *count){
    int c = 0;

    if(p == NULL || q == NULL){
        printf("有地址为空,不能查找子串个数\n");
        return;
    }   

    while(p = strstr(p, q)){
        c++;
        p = p + strlen(q);
        if(p == NULL){
            break;
        }   
    }   

    *count = c;
}

int main(void){
    char *p = "abc12421abc34345abc325423abc";
    char *q = "abc";
    int count = 0;

    strstrCount(p, q, &count);
    printf("%d\n", count);

    return 0;
}
```

运行结果：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfTNS5dRtW26EJTRuZ0qafY2PFibIaaQGFcAKIqibeORH3oQ8YJ41szP0g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

## 三、去掉字符串的前后空格

```c
#include<stdio.h>
#include<string.h>
#include<malloc.h>

void trimSpace(char **str1, char *str2);
void trimSpace(char **str1, char *str2){
    int length = strlen(str2);
    char *tmp;

    *str1 = (char *)malloc(sizeof(char)*length);
    tmp = *str1;

    for(; *str2; str2++){
        if(*str2 != ' '){
            *tmp++ = *str2;
        }   
    }   
    *tmp = 0;
}

int main(void){
    char str[] = "               abcdefg               "; 
    char *str1;

    printf("%s\n", str);
    trimSpace(&str1, str);
    printf("%s\n", str1);
} 
```

运行结果
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfiadhCeZcic1iafaHHdCQBNEf48E0uQgt88Dic9lRnI8c7QDib1eHJibdWLqg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**以上的代码都是我亲自实践过的，有些细节多多思考，每天进步一点点，去理解清楚，在敲出来！**

## 四、说明

原创文章链接：[实现strcpy()和strstr()函数的多种方法](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483682&idx=1&sn=44efebae423d9eaf62b2c91648064a7e&chksm=f94c8b1fce3b02097128064913561e3a14113086ac6d93bd160c69d42f5c5aae4a462ca34a37&scene=21#wechat_redirect)


---
