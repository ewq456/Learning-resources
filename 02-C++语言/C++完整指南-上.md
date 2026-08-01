# C++完整指南（上）— 基础与面向对象


## 01-Cpp完整指南-上-基础与面向对象


> 本指南假设你已有C语言基础，按照从C过渡→面向对象→高级特性的正确顺序编排。

---

## 第一章：从C过渡到C++

### C与C++的关系

C++是C语言的**超集**，绝大多数C代码可以直接用C++编译器编译。C++在C的基础上增加了：

- 面向对象（类、继承、多态）
- 泛型编程（模板）
- 标准模板库（STL）
- 异常处理
- 引用类型
- 命名空间

### Hello World

```cpp
#include <iostream>
using namespace std;  // 使用std命名空间

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
```

### 命名空间

命名空间用于解决命名冲突：

```cpp
namespace MySpace {
    int value = 100;
    void func() { /* ... */ }
}

// 使用
MySpace::func();
using MySpace::value;
using namespace MySpace;  // 引入整个命名空间
```

### cin 和 cout

C++使用流式输入输出替代C的printf/scanf：

```cpp
int age;
cout << "请输入年龄: ";
cin >> age;
cout << "年龄是: " << age << endl;
```

### bool 类型

```cpp
bool b = true;
cout << b << endl;              // 输出: 1
cout << boolalpha << b << endl; // 输出: true
```

---

## 第二章：引用

### 什么是引用

**引用是变量的别名**，本质上是指针的语法糖（底层实现就是指针常量）。

```cpp
int a = 10;
int &ref = a;   // ref是a的引用（别名）

ref = 20;       // 修改ref就是修改a
// 现在 a = 20
```

### 引用的特点

1. 引用在定义时**必须初始化**
2. 引用一旦绑定，**不能改变**绑定对象
3. 引用**不是对象**，没有自己的地址（sizeof(ref)等于原变量大小）

### 引用作为函数参数

这是引用最常用的场景——避免拷贝，且语法更简洁：

```cpp
// C语言方式：传指针
void swap_c(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// C++方式：传引用
void swap_cpp(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
```

### 引用作为返回值

```cpp
int& getElement(int arr[], int index) {
    return arr[index];  // 可以作为左值
}

getElement(arr, 0) = 100;  // 修改arr[0]
```

### const 引用

```cpp
const int &ref = a;  // 不能通过ref修改a
// 常用于函数参数，避免拷贝且保证不修改原值
void print(const string &s) { /* 只读 */ }
```

---

## 第三章：new 和 delete

替代C语言的malloc/free：

```cpp
// 分配单个对象
int *p = new int(10);       // 分配并初始化为10
delete p;

// 分配数组
int *arr = new int[100];    // 分配100个int
delete[] arr;               // 注意要用delete[]

// C语言对比
int *p2 = (int*)malloc(sizeof(int));
free(p2);
```

**关键区别**：
- `new` 自动计算大小，`malloc`需要手动计算
- `new` 会调用构造函数，`malloc`不会
- `new` 返回正确类型的指针，`malloc`返回`void*`

---

## 第四章：类与对象（面向对象核心）

### 类的定义

```cpp
class Student {
private:            // 私有成员（默认）
    string name;
    int age;

public:             // 公有成员
    // 构造函数
    Student(const string &n, int a) : name(n), age(a) {}

    // 成员函数
    void study() {
        cout << name << " is studying" << endl;
    }

    // 获取器（getter）
    string getName() const { return name; }
    int getAge() const { return age; }
};
```

### 访问控制

| 访问限定符 | 类内部 | 派生类 | 外部 |
|:---------:|:------:|:------:|:----:|
| `public` | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ |

### 构造函数的初始化列表

```cpp
Student(const string &n, int a) : name(n), age(a) {
    // 这里是构造函数体
}
```

**初始化列表比在函数体内赋值更高效**，因为：
- 成员变量在进入函数体之前已经初始化
- const成员和引用成员只能用初始化列表
- 避免了"默认初始化+赋值"的双重开销

### 析构函数

```cpp
~Student() {
    // 清理资源
    cout << "Student destroyed" << endl;
}
```

析构函数在对象生命周期结束时自动调用，用于释放资源。

**析构顺序**：先构造的后析构（栈的后进先出）。

---

## 第五章：构造函数与拷贝控制

C++编译器会为一个空类自动生成6个成员函数：

1. **默认构造函数** — `ClassName()`
2. **析构函数** — `~ClassName()`
3. **拷贝构造函数** — `ClassName(const ClassName&)`
4. **拷贝赋值运算符** — `ClassName& operator=(const ClassName&)`
5. **移动构造函数**（C++11）— `ClassName(ClassName&&)`
6. **移动赋值运算符**（C++11）— `ClassName& operator=(ClassName&&)`

### 拷贝构造 vs 赋值

```cpp
// 拷贝构造：用已有对象初始化新对象
MyClass obj2 = obj1;       // 调用拷贝构造
MyClass obj3(obj1);        // 调用拷贝构造

// 赋值：将已有对象的值赋给另一个已有对象
MyClass obj4;
obj4 = obj1;               // 调用赋值运算符
```

### 深拷贝 vs 浅拷贝

**浅拷贝**（默认拷贝构造）：只拷贝指针值，不拷贝指针指向的数据。

```cpp
class Shallow {
    char *data;
public:
    // 默认拷贝构造只拷贝了data指针的值
    // 两个对象的data指向同一块内存 → 重复释放！
};
```

**深拷贝**：拷贝指针指向的实际数据。

```cpp
class Deep {
    char *data;
public:
    Deep(const Deep &other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);  // 拷贝实际内容
    }
};
```

### 写时拷贝（Copy-On-Write）

**引用计数+写时拷贝**的高效方案：

```cpp
// 多个对象共享同一块数据，用一个引用计数跟踪
// 读取时共享，写入时才真正拷贝
class COWString {
    struct Data {
        char *str;
        int refCount;
    };
    Data *data;
public:
    // 拷贝构造：增加引用计数，不拷贝数据
    COWString(const COWString &other) {
        data = other.data;
        ++data->refCount;
    }
    // 写操作时检查引用计数，>1时先拷贝再写
};
```

---

## 第六章：this 指针

每个非静态成员函数都有一个隐藏的`this`指针，指向调用该函数的对象。

```cpp
class MyClass {
    int value;
public:
    MyClass& setValue(int value) {
        this->value = value;  // 用this区分成员和参数
        return *this;         // 返回自身，支持链式调用
    }
};

// 链式调用
MyClass obj;
obj.setValue(10).setValue(20);  // 等价于 obj.setValue(10); obj.setValue(20);
```

---

## 第七章：const 和 static 成员

### const 成员函数

```cpp
class MyClass {
    int value;
public:
    int getValue() const {   // const成员函数
        // value = 10;       // 错误！不能修改成员变量
        return value;
    }
};
```

- const成员函数承诺**不修改对象状态**
- const对象只能调用const成员函数
- 非const对象可以调用任何成员函数

### static 成员变量

```cpp
class Counter {
    static int count;        // 声明（类内）
public:
    Counter() { ++count; }
    static int getCount() { return count; }
};

// 必须在类外定义
int Counter::count = 0;
```

**static成员的特点**：
- 属于整个类，不属于任何对象
- 所有对象共享同一份数据
- 存放在静态存储区
- static成员函数没有this指针，只能访问static成员
- 本质上是**受限制的全局变量/全局函数**

---

## 第八章：友元

友元函数和友元类可以访问类的私有成员。

```cpp
class MyClass {
    int secret;
public:
    friend void show(const MyClass &obj);  // 友元函数
    friend class MyFriend;                 // 友元类
};

void show(const MyClass &obj) {
    cout << obj.secret << endl;  // 可以访问私有成员
}
```

### 友元函数模板化

```cpp
template<typename T>
class Container {
    T data;
    // 将模板函数声明为友元
    template<typename U>
    friend void print(const Container<U> &c);
};
```

---

## 第九章：运算符重载

C++允许自定义运算符的行为：

```cpp
class Complex {
    double real, imag;
public:
    // 成员函数方式重载 +
    Complex operator+(const Complex &other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 友元函数方式重载 <<
    friend ostream& operator<<(ostream &os, const Complex &c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

    // 前置++
    Complex& operator++() {
        ++real;
        return *this;
    }

    // 后置++（int参数是占位符，区分前置和后置）
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }
};

// 使用
Complex a(1, 2), b(3, 4);
Complex c = a + b;
cout << c << endl;  // 4 + 6i
```

### 可重载和不可重载的运算符

**可重载**：`+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= && || ++ -- , ->* -> () [] new new[] delete delete[]`

**不可重载**：`. .* :: ?: sizeof typeid`

---

## 第十章：继承

### 基本语法

```cpp
// 基类
class Animal {
protected:
    string name;
public:
    Animal(const string &n) : name(n) {}
    void eat() { cout << name << " is eating" << endl; }
};

// 派生类
class Dog : public Animal {
public:
    Dog(const string &n) : Animal(n) {}
    void bark() { cout << name << " is barking" << endl; }
};

Dog dog("旺财");
dog.eat();   // 继承自Animal
dog.bark();  // Dog自己的方法
```

### 继承方式

| 继承方式 | 基类public → | 基类protected → | 基类private → |
|:-------:|:----------:|:-------------:|:------------:|
| public继承 | public | protected | 不可访问 |
| protected继承 | protected | protected | 不可访问 |
| private继承 | private | private | 不可访问 |

**99%的情况下使用 public 继承。**

### 继承中的构造函数和析构函数顺序

```
构造：基类 → 派生类（先父母，后孩子）
析构：派生类 → 基类（先孩子，后父母）
```

### 菱形继承与虚继承

```
      A
     / \
    B   C
     \ /
      D
```

问题：D中有两份A的成员，造成数据冗余和二义性。

**解决方案：虚继承**

```cpp
class B : virtual public A { /* ... */ };
class C : virtual public A { /* ... */ };
class D : public B, public C { /* ... */ };
// 现在D中只有一份A的成员
```

`virtual`让基类做出声明，承诺愿意共享它的基类给共同的后代。

---

## 第十一章：多态（面向对象的精髓）⚠️

### 什么是多态

**多态**：同一接口，不同实现。通过基类指针/引用调用派生类重写的方法。

### 虚函数

```cpp
class Animal {
public:
    virtual void speak() {  // 虚函数
        cout << "Animal sound" << endl;
    }
    virtual ~Animal() {}    // 虚析构函数（必须！）
};

class Dog : public Animal {
public:
    void speak() override {  // 重写（推荐加override关键字）
        cout << "汪! 汪!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "喵~" << endl;
    }
};

// 多态的使用
Animal *p = new Dog();
p->speak();  // 输出: 汪! 汪!（调用的是Dog的speak）
delete p;
```

### 虚函数表（vtable）原理

每个含有虚函数的类都有一个**虚函数表**（vtable），对象中有一个**虚函数表指针**（vptr）。

```
对象内存布局：
┌──────────┐
│  vptr    │ → 指向虚函数表
├──────────┤
│  成员变量 │
└──────────┘

虚函数表：
┌─────────────────┐
│ &Animal::speak() │ → Animal的虚表
├─────────────────┤
│ &Dog::speak()    │ → Dog的虚表（覆盖了Animal::speak）
└─────────────────┘
```

### 纯虚函数与抽象类

```cpp
class Shape {                              // 抽象类
public:
    virtual double area() const = 0;       // 纯虚函数
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    double area() const override {
        return 3.14159 * radius * radius;
    }
};
// Shape s;  // 错误！不能实例化抽象类
```

含有纯虚函数的类称为**抽象类**，不能实例化，只能作为基类。

### explicit 关键字

```cpp
class MyClass {
public:
    explicit MyClass(int x) { /* ... */ }  // 禁止隐式转换
};

// MyClass obj = 10;  // 错误！不能隐式转换
MyClass obj(10);      // 正确：显式调用
```

---

## 第十二章：C++中四种类型转换

```cpp
// 1. static_cast — 编译期检查的类型转换
int a = 10;
double d = static_cast<double>(a);
// 用于相关类型之间的转换（如父子类指针转换）

// 2. dynamic_cast — 运行时检查的类型转换
Animal *p = new Dog();
Dog *d = dynamic_cast<Dog*>(p);  // 安全的向下转型
// 失败时返回nullptr（指针）或抛异常（引用）

// 3. const_cast — 去掉const属性
const int *cp = &a;
int *mp = const_cast<int*>(cp);
// 慎用！修改const对象是未定义行为

// 4. reinterpret_cast — 重新解释二进制位
int *ip = &a;
char *cp2 = reinterpret_cast<char*>(ip);
// 最危险的转换，仅在必须时使用
```

---

## 下一步

掌握以上内容后，继续学习 ### C++完整指南（下）— 模板、异常与进阶特性


> 接上篇，本篇涵盖泛型编程、异常处理、STL、C++11新特性等。

---

## 第十三章：函数模板与类模板

### 函数模板

函数模板是泛型编程的基础，让函数能与类型无关地工作：

```cpp
// 函数模板
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// 使用
int i = max(10, 20);          // T = int
double d = max(3.14, 2.71);   // T = double
string s = max(string("abc"), string("xyz")); // T = string
```

**模板参数可以有多**个：

```cpp
template<typename T1, typename T2>
void print(T1 a, T2 b) {
    cout << a << " and " << b << endl;
}
```

### 类模板

```cpp
template<typename T>
class Stack {
    T data[100];
    int top;
public:
    Stack() : top(-1) {}
    void push(const T &val) { data[++top] = val; }
    T pop() { return data[top--]; }
    bool empty() const { return top == -1; }
};

// 使用
Stack<int> intStack;
Stack<string> strStack;
```

### 模板特化

当模板对特定类型需要特殊处理时：

```cpp
// 通用模板
template<typename T>
class Compare {
public:
    bool equal(T a, T b) { return a == b; }
};

// 对char*的特化（全特化）
template<>
class Compare<char*> {
public:
    bool equal(char* a, char* b) {
        return strcmp(a, b) == 0;
    }
};
```

### 可变参数宏

C/C++中宏支持可变参数，通过`__VA_ARGS__`和`...`实现：

```cpp
#define PRINT(templt, ...) fprintf(stdout, templt, __VA_ARGS__)
#define LOG(fmt, ...) printf("[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
```

### # 和 ## 的作用

- `#`：字符串化操作符，将宏参数转为字符串
- `##`：标记粘贴操作符，将两个标记拼接成一个

```cpp
#define STRINGIFY(x) #x          // STRINGIFY(hello) → "hello"
#define CONCAT(a, b) a##b        // CONCAT(my, Var) → myVar
#define varNum(x) var##x         // varNum(1) → var1
```

---

## 第十四章：异常处理

### 基本语法

```cpp
try {
    // 可能抛出异常的代码
    if (error_condition) {
        throw runtime_error("Something went wrong");
    }
} catch (const runtime_error &e) {
    cout << "Runtime error: " << e.what() << endl;
} catch (const exception &e) {
    cout << "Exception: " << e.what() << endl;
} catch (...) {
    cout << "Unknown exception" << endl;
}
```

### 标准异常类

```
std::exception
  ├── std::logic_error
  │     ├── std::invalid_argument
  │     ├── std::domain_error
  │     ├── std::length_error
  │     └── std::out_of_range
  └── std::runtime_error
        ├── std::range_error
        ├── std::overflow_error
        └── std::underflow_error
```

### 异常安全

```cpp
// RAII模式确保异常安全
class FileGuard {
    FILE *fp;
public:
    FileGuard(const char *path) : fp(fopen(path, "r")) {}
    ~FileGuard() { if (fp) fclose(fp); }
    FILE* get() { return fp; }
};

void process() {
    FileGuard fg("data.txt");
    // 即使抛出异常，析构函数也会自动调用
}
```

---

## 第十五章：流类库和文件IO

### iostream 层次

```
ios_base → ios → istream  → iostream
              → ostream ↗
                    ↖ ifstream → fstream
                    ↙ ofstream ↗
                    ↖ istringstream → stringstream
                    ↙ ostringstream ↗
```

### 文件操作

```cpp
#include <fstream>

// 写文件
ofstream ofs("test.txt");
ofs << "Hello, File!" << endl;
ofs.close();

// 读文件
ifstream ifs("test.txt");
string line;
while (getline(ifs, line)) {
    cout << line << endl;
}
ifs.close();
```

### 字节流写入文件示例

```cpp
std::fstream file("output.txt", std::ios_base::out | std::ios_base::trunc);
if (!file.is_open()) {
    cerr << "Open failed!" << endl;
    return;
}
file << data;
file.close();
```

---

## 第十六章：C++11 重要新特性

### auto 类型推导

```cpp
auto i = 42;              // int
auto d = 3.14;            // double
auto it = vec.begin();    // vector<int>::iterator
```

### 范围for循环

```cpp
vector<int> vec = {1, 2, 3, 4, 5};
for (int x : vec) {
    cout << x << " ";
}
for (auto &x : vec) {     // 引用，可以修改
    x *= 2;
}
```

### lambda表达式

```cpp
// [捕获列表](参数列表) -> 返回类型 { 函数体 }
auto add = [](int a, int b) -> int { return a + b; };

// 捕获外部变量
int factor = 10;
auto multiply = [factor](int x) { return x * factor; };

// 常用于算法
sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
```

### 智能指针

```cpp
#include <memory>

// unique_ptr：独占所有权，不能拷贝
unique_ptr<int> up1 = make_unique<int>(10);
// unique_ptr<int> up2 = up1;  // 错误！

// shared_ptr：共享所有权，引用计数
shared_ptr<int> sp1 = make_shared<int>(20);
shared_ptr<int> sp2 = sp1;  // 引用计数变为2

// weak_ptr：弱引用，不增加引用计数
weak_ptr<int> wp = sp1;
if (auto sp = wp.lock()) {  // 尝试获取shared_ptr
    cout << *sp << endl;
}
```

### 移动语义

```cpp
class MyVector {
    int *data;
    size_t size;
public:
    // 移动构造函数
    MyVector(MyVector &&other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 移动赋值
    MyVector& operator=(MyVector &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

### std::thread 多线程

```cpp
#include <thread>
#include <atomic>

// 基本用法
void task(int id) {
    cout << "Thread " << id << " running" << endl;
}

thread t1(task, 1);
t1.join();  // 等待线程结束

// 传递引用参数（使用std::ref）
void modify(int &x) { x = 100; }
int value = 0;
thread t2(modify, ref(value));
t2.join();
// value = 100

// 原子操作（无需mutex）
atomic_int counter = 0;
void increment() {
    for (int i = 0; i < 10000; i++) {
        counter++;  // 原子操作，线程安全
    }
}
```

### std::thread 常用API

| 函数 | 说明 |
|------|------|
| `thread()` | 默认构造，空线程 |
| `thread(fn, args...)` | 创建线程执行fn |
| `join()` | 等待线程结束（阻塞）|
| `detach()` | 分离线程，独立运行 |
| `joinable()` | 检查线程是否可join |
| `get_id()` | 获取线程ID |

---

## 第十七章：C++空类与编译器生成函数

空类默认会生成6个函数（C++11后）：

```cpp
class Empty {
    // 编译器自动生成：
    // 1. Empty()                         — 默认构造函数
    // 2. ~Empty()                        — 析构函数
    // 3. Empty(const Empty&)             — 拷贝构造函数
    // 4. Empty& operator=(const Empty&)  — 拷贝赋值运算符
    // 5. Empty(Empty&&)                  — 移动构造函数 (C++11)
    // 6. Empty& operator=(Empty&&)       — 移动赋值运算符 (C++11)
};
```

### 拷贝构造与赋值运算符的区别

- **拷贝构造函数**：用已有对象**初始化新对象**
- **赋值运算符**：将一个已有对象的值赋给**另一个已有对象**

```cpp
MyClass obj2 = obj1;   // 拷贝构造（初始化）
MyClass obj3(obj1);    // 拷贝构造（初始化）
obj3 = obj2;           // 赋值运算符（已存在的对象）
```

### 结构化绑定 (C++17)

```cpp
pair<int, string> p = {1, "hello"};
auto [id, msg] = p;  // id=1, msg="hello"

map<int, string> m = {{1, "a"}, {2, "b"}};
for (auto [key, value] : m) {
    cout << key << ": " << value << endl;
}
```

---

## 第十八章：时间处理

### struct tm 结构体

```c
struct tm {
    int tm_sec;    // 秒 [0, 59]
    int tm_min;    // 分 [0, 59]
    int tm_hour;   // 时 [0, 23]
    int tm_mday;   // 日 [1, 31]
    int tm_mon;    // 月 [0, 11]（0=一月）
    int tm_year;   // 年（从1900年起）
    int tm_wday;   // 星期 [0, 6]（0=周日）
    int tm_yday;   // 年中第几天 [0, 365]
    int tm_isdst;  // 夏令时标识
};
```

### 关键函数

```cpp
// 获取当前时间戳
time_t now = time(NULL);

// time_t → struct tm（本地时间）
struct tm *info = localtime(&now);

// struct tm → 字符串
char *str = asctime(info);  // "Mon Sep 30 21:59:47 2019\n"

// 格式化输出
char buf[80];
strftime(buf, 80, "%Y-%m-%d %H:%M:%S", info);
// "2018-09-19 08:59:07"

// struct tm → time_t
time_t ts = mktime(info);
```

### strftime 常用格式化符

| 格式符 | 说明 | 示例 |
|:------:|------|------|
| `%Y` | 四位年份 | 2024 |
| `%m` | 月份(01-12) | 08 |
| `%d` | 日(01-31) | 19 |
| `%H` | 24小时制 | 14 |
| `%M` | 分钟 | 55 |
| `%S` | 秒 | 02 |
| `%A` | 完整星期名 | Sunday |
| `%B` | 完整月份名 | March |

### ctime vs asctime

| | ctime | asctime |
|:--|:------|:--------|
| 参数 | `time_t*` | `struct tm*` |
| 缓冲区 | 静态（多次调用覆盖）| 静态 |
| 适用 | 直接使用time_t | 已有struct tm |

---

## 下一步

掌握C++完整指南上下篇后，继续学习：
- > 📎 **STL标准库完整指南** — *相关笔记已收录于本知识库其他文件*
- > 📎 **设计模式完整指南** — *相关笔记已收录于本知识库其他文件*
- > 📎 **Boost智能指针详解** — *相关笔记已收录于本知识库其他文件*


---。

内容包括：函数模板/类模板、异常处理、流类库和文件IO、C++11新特性（智能指针、lambda、move语义等）。


---
