# C++完整指南（下）— 模板与进阶


## 02-Cpp完整指南-下-模板与进阶


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
- > *引用: STL标准库完整指南（原文链接: ../03-STL标准库/01-STL完整指南.md）*
- > *引用: 设计模式完整指南（原文链接: ../05-设计模式/01-设计模式完整指南.md）*
- > *引用: Boost智能指针详解（原文链接: ../04-Boost库/01-Boost智能指针详解.md）*


---
