# Linux系统编程完整指南


## 00-Linux系统编程完整指南


> Linux系统编程是嵌入式/后端开发的必备技能。本篇整理核心知识，按学习顺序编排。

---

## 第一章：Linux 基础入门

### 安装虚拟机

学习Linux第一步：安装虚拟机（VMware + Red Hat / Ubuntu镜像）。

### Linux 核心思想

1. **一切皆文件** — 目录、设备、进程都是文件
2. **不区分扩展名** — 扩展名给人看的，Linux不依赖扩展名判断文件类型
3. **严格区分大小写**

### 目录结构速查

| 目录 | 用途 |
|------|------|
| `/` | 根目录 |
| `/home` | 用户家目录 |
| `/etc` | 配置文件 |
| `/var` | 日志、可变数据 |
| `/tmp` | 临时文件 |
| `/dev` | 设备文件 |
| `/proc` | 进程信息（虚拟文件系统）|
| `/usr` | 用户程序和数据 |

### 最常用命令

```bash
# 文件和目录
ls -la          # 列出文件（含隐藏）
cd /path        # 切换目录
pwd             # 显示当前路径
mkdir -p a/b    # 递归创建目录
rm -rf dir/     # 删除目录（慎用！）
cp -r src/ dst/ # 复制
mv old new      # 移动/重命名

# 查看文件
cat file        # 查看全部
head -n 10      # 前10行
tail -f file    # 追踪末尾（实时日志）
more/less       # 分页查看

# 权限
chmod 755 file  # 修改权限(rwxr-xr-x)
chown user:grp  # 修改所有者
chgrp group     # 修改所属组

# 进程
ps aux          # 查看所有进程
ps -eLf         # 查看进程+线程
top             # 动态进程监控
kill -9 PID     # 强制杀进程
killall 进程名   # 按名杀进程
pstree          # 进程树

# 系统
df -h           # 磁盘使用
du -sh dir/     # 目录大小
free -h         # 内存
uname -a        # 系统信息
dmesg           # 内核日志

# 网络
ping host       # 测试连通
netstat -tlnp   # 查看监听端口
ifconfig/ip addr # 网络接口
ssh user@host   # 远程登录
scp file host:  # 远程拷贝

# 压缩
tar -czf a.tar.gz dir/  # 打包压缩
tar -xzf a.tar.gz       # 解压
```

### 文件属性

Linux文件10个属性字符：
```
-rwxr-xr-x
│├─┤├─┤├─┤
│ u  g  o
│
文件类型: -普通,d目录,l链接,b块设备,c字符设备,p管道
```

- u=所有者, g=所属组, o=其他用户
- r=读(4), w=写(2), x=执行(1)

### 特殊权限

| 权限 | 说明 | 设置 |
|------|------|------|
| SUID | 以文件所有者权限执行 | `chmod u+s` / 4xxx |
| SGID | 目录下新建文件继承目录组 | `chmod g+s` / 2xxx |
| SBIT | 只能删除自己创建的文件 | `chmod o+t` / 1xxx |

### 软链接与硬链接

| 特性 | 软链接 (ln -s) | 硬链接 (ln) |
|------|:-------------:|:----------:|
| 本质 | 存路径的特殊文件 | 同一inode的别名 |
| 跨文件系统 | ✅ | ❌ |
| 链接目录 | ✅ | ❌ |
| 源文件删除 | 链接失效 | 仍可访问 |
| inode | 不同 | 相同 |

### 重定向

```bash
# 标准输出覆盖写入
command > file

# 标准输出追加写入
command >> file

# 标准输入重定向
command < file

# 标准错误重定向
command 2> file

# 合并输出和错误
command > file 2>&1
```

### find 命令

```bash
find 路径 -name "*.c"        # 按名查找
find 路径 -size +1M          # 大于1M的文件
find 路径 -type f            # 普通文件
find 路径 -perm 755          # 按权限
find 路径 -user username     # 按所有者
find 路径 -exec 命令 {} \;   # 对结果执行命令
```

### grep 与正则表达式

```bash
grep -i "pattern" file      # 忽略大小写
grep -v "pattern" file      # 反向匹配
grep -n "pattern" file      # 显示行号
grep -r "pattern" dir/      # 递归搜索
```

正则元字符：
- `.` 匹配任意单个字符
- `*` 匹配前一个字符0-n次
- `.*` 匹配任意长度任意字符
- `^` 行首, `$` 行尾
- `[abc]` 匹配a/b/c中任意一个
- `[^abc]` 不匹配a/b/c
- `\{m,n\}` 匹配m到n次

### 用户和组管理

```bash
useradd username            # 添加用户
userdel username            # 删除用户
passwd username             # 设置密码
usermod -g group user       # 修改主组
groupadd groupname          # 添加组
id username                 # 查看用户信息
su - username               # 切换用户（完整登录）
```

---

## 第二章：文件IO

### 文件描述符

文件描述符是一个非负整数，Linux中一切IO都通过文件描述符操作：

| 文件描述符 | 宏 | 含义 |
|:---------:|:---:|------|
| 0 | STDIN_FILENO | 标准输入 |
| 1 | STDOUT_FILENO | 标准输出 |
| 2 | STDERR_FILENO | 标准错误 |

### 基本API

```c
#include <fcntl.h>
#include <unistd.h>

// 打开/创建文件
int fd = open("file.txt", O_RDWR | O_CREAT, 0644);

// 读取
ssize_t n = read(fd, buf, sizeof(buf));

// 写入
ssize_t n = write(fd, buf, strlen(buf));

// 定位
off_t pos = lseek(fd, 0, SEEK_SET);  // 文件开头
lseek(fd, 0, SEEK_END);              // 文件末尾
lseek(fd, 10, SEEK_CUR);             // 当前位置+10

// 关闭
close(fd);
```

### 文件描述符复制

```c
int newfd = dup(oldfd);              // 复制fd
dup2(oldfd, newfd);                  // 将newfd指向oldfd
```

---

## 第三章：进程管理

### 进程概念

进程是可执行程序的运行实例，每个进程有唯一的PID。

### 进程状态

| 状态 | 符号 | 含义 |
|------|:----:|------|
| 运行 | R | 正在运行或可运行 |
| 可中断睡眠 | S | 等待事件完成 |
| 不可中断睡眠 | D | 等待IO，不响应信号 |
| 僵尸 | Z | 已结束但未被父进程回收 |
| 停止 | T | 被暂停 |

### 进程创建

```c
pid_t pid = fork();
if (pid == 0) {
    // 子进程
    printf("I'm child, PID=%d\n", getpid());
} else if (pid > 0) {
    // 父进程
    printf("I'm parent, child PID=%d\n", pid);
}
```

**fork 的特点**：
- 子进程是父进程的拷贝（Copy-On-Write优化）
- 子进程从fork()的下一句开始执行
- 父子进程拥有独立的地址空间

### exec函数族

```c
// 用新程序替换当前进程映像
execl("/bin/ls", "ls", "-l", NULL);
execv("/bin/ls", argv);
execle("/bin/ls", "ls", "-l", NULL, envp);
```

**fork + exec 模式**：fork创建子进程 → exec替换子进程 → 实现进程多样性。

### 进程退出与回收

```c
exit(0);                // 正常退出
_exit(0);               // 直接退出（不清理IO缓冲）

// 父进程等待子进程结束
pid_t pid = wait(&status);        // 等待任意子进程
pid_t pid = waitpid(pid, &status, 0);  // 等待指定子进程
```

### 特殊进程

**僵尸进程**：子进程已结束但父进程未调用wait()回收。解决：父进程调用wait()或处理SIGCHLD信号。

**孤儿进程**：父进程先于子进程结束，子进程被init/systemd收养。

**守护进程**：后台运行，脱离终端。创建步骤：
1. `fork()` 并退出父进程
2. 子进程调用 `setsid()` 创建新会话
3. 再次 `fork()` 并退出，确保不是会话首进程
4. 更改工作目录、重定向标准IO

---

## 第四章：进程间通信（IPC）

### 管道（Pipe）

```c
int fd[2];
pipe(fd);              // fd[0]=读端, fd[1]=写端
// 单向通信，只能用于父子进程

// 命名管道（FIFO），可用于无亲缘关系进程
mkfifo("myfifo", 0644);
```

### 信号（Signal）

信号是异步通知机制：

```c
#include <signal.h>

// 信号处理函数
void handler(int signo) {
    printf("Received signal %d\n", signo);
}

// 注册信号处理
signal(SIGINT, handler);   // Ctrl+C

// 发送信号
kill(pid, SIGUSR1);
raise(SIGUSR1);            // 给自己发信号
alarm(5);                  // 5秒后收到SIGALRM
```

常用信号：SIGINT(Ctrl+C)、SIGTERM(终止)、SIGKILL(强制杀)、SIGCHLD(子进程状态变化)、SIGUSR1/SIGUSR2(用户自定义)

### 共享内存

```c
// 创建共享内存
int shmid = shmget(key, size, IPC_CREAT | 0666);

// 映射到进程地址空间
void *addr = shmat(shmid, NULL, 0);

// 解除映射
shmdt(addr);

// 删除共享内存
shmctl(shmid, IPC_RMID, NULL);
```

**最快的IPC方式**：数据直接读写内存，不需要内核中转。

### 消息队列

```c
int msqid = msgget(key, IPC_CREAT | 0666);

// 发送消息
msgsnd(msqid, &msg, sizeof(msg)-sizeof(long), 0);

// 接收消息（可按类型选择性接收）
msgrcv(msqid, &msg, sizeof(msg)-sizeof(long), msg_type, 0);
```

### 信号量（Semaphore）

```c
int semid = semget(key, 1, IPC_CREAT | 0666);

// P操作（减1，获取资源）
struct sembuf p = {0, -1, 0};
semop(semid, &p, 1);

// V操作（加1，释放资源）
struct sembuf v = {0, 1, 0};
semop(semid, &v, 1);
```

### 文件IPC

使用磁盘文件+信号（SIGUSR1）实现同步通信，适用于复杂数据交换。

---

## 第五章：多线程

### 线程 vs 进程

| 特性 | 进程 | 线程 |
|------|:----:|:----:|
| 地址空间 | 独立 | 共享 |
| 创建开销 | 大 | 小 |
| 通信方式 | IPC | 直接读写共享内存 |
| 隔离性 | 强 | 弱（一个线程崩溃可能影响整个进程）|

### pthread 基本API

```c
#include <pthread.h>

// 创建线程
pthread_t tid;
pthread_create(&tid, NULL, thread_func, arg);

// 等待线程结束
pthread_join(tid, NULL);

// 线程退出
pthread_exit(NULL);

// 取消线程
pthread_cancel(tid);

// 获取自身ID
pthread_self();

// 比较线程ID
pthread_equal(tid1, tid2);
```

### 线程同步

**互斥锁（Mutex）**：

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&mutex);
// 临界区代码
pthread_mutex_unlock(&mutex);
```

**条件变量（Condition Variable）**：

```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 等待条件
pthread_mutex_lock(&mutex);
while (!condition) {
    pthread_cond_wait(&cond, &mutex);  // 释放锁并等待
}
pthread_mutex_unlock(&mutex);

// 发送信号
pthread_cond_signal(&cond);     // 唤醒一个等待线程
pthread_cond_broadcast(&cond);  // 唤醒所有等待线程
```

**读写锁（RWLock）**：

```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

// 读锁（可多个线程同时持有）
pthread_rwlock_rdlock(&rwlock);

// 写锁（互斥）
pthread_rwlock_wrlock(&rwlock);

pthread_rwlock_unlock(&rwlock);
```

**读写锁规则**：
- 写锁优先：有写者等待时，新读者不能获取锁（默认）
- 读锁优先：读者优先获取锁，写者可能饥饿

### 生产者-消费者模型

```c
// 共享缓冲区
#define BUF_SIZE 8
struct {
    int buf[BUF_SIZE];
    int nput;    // 下一个放入位置
    int nval;    // 下一个值
    int size;    // 当前元素数量
} shared;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t noempty = PTHREAD_COND_INITIALIZER; // 非空条件
pthread_cond_t nofull = PTHREAD_COND_INITIALIZER;  // 非满条件

// 生产者
void *producer(void *arg) {
    for (int i = 0; i < MAX_NUM; i++) {
        pthread_mutex_lock(&mutex);
        while (shared.size >= BUF_SIZE)          // 缓冲区满了
            pthread_cond_wait(&nofull, &mutex);   // 等待非满
        shared.buf[shared.nput++] = shared.nval++;
        shared.nput %= BUF_SIZE;
        shared.size++;
        pthread_cond_signal(&noempty);             // 通知非空
        pthread_mutex_unlock(&mutex);
    }
}

// 消费者同理，等待noempty，通知nofull
```

### P/V 操作

```c
// P操作（Proberen = 测试）：资源减1，资源不够则阻塞
// V操作（Verhogen = 增加）：资源加1，唤醒等待者

// 用共享内存+信号量实现
int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
semctl(semid, 0, SETVAL, 1);  // 初始化为1

struct sembuf p = {0, -1, 0};  // P操作
struct sembuf v = {0, 1, 0};   // V操作
```

---

## 第六章：静态库与动态库

### 静态库 (.a)

```bash
# 制作
gcc -c foo.c -o foo.o
ar -cr libfoo.a foo.o

# 使用
gcc main.c -L. -lfoo -o app
# 或直接将.a文件放到 /lib64 目录下
```

静态库在**链接时**被复制到可执行文件中。

### 动态库 (.so)

```bash
# 制作（-fpic 位置无关代码）
gcc -c -fpic foo.c -o foo.o
gcc -shared -o libfoo.so foo.o

# 使用
gcc main.c -L. -lfoo -o app
# 运行时需要能找到.so文件
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
```

动态库在**运行时**被加载，可多个程序共享。

### 动态加载

```c
#include <dlfcn.h>

void *handle = dlopen("./libfoo.so", RTLD_LAZY);
void (*func)(int) = dlsym(handle, "function_name");
func(42);
dlclose(handle);
```

**C++注意**：用 `extern "C"` 防止名称修饰(name mangling)导致的符号找不到。

---

## 第七章：系统管理

### systemd 服务管理

```bash
systemctl start/stop/restart 服务名
systemctl enable/disable 服务名       # 开机自启
systemctl status 服务名
systemctl list-units --type=service   # 列出所有服务
```

### 日志管理

```bash
# rsyslog 日志在 /var/log/ 下
tail -f /var/log/messages

# systemd journal
journalctl                    # 所有日志
journalctl -n 50              # 最后50条
journalctl -p err             # 错误级别
journalctl --since "2024-01-01"
```

### 计划任务 (cron)

```bash
crontab -e     # 编辑当前用户cron任务
crontab -l     # 列出当前用户cron任务

# 格式：分 时 日 月 周 命令
# 每天凌晨2点备份
0 2 * * * /home/user/backup.sh
```

### 时间管理

```bash
timedatectl                     # 查看时间状态
timedatectl set-timezone Asia/Shanghai
timedatectl set-time "2024-01-01 12:00:00"
```

### YUM 源配置

```bash
# RedHat: 配置本地仓库
mkdir /dvd
mount /dev/sr0 /dvd
vim /etc/yum.repos.d/rhel-dvd.repo
# [rhel-dvd]
# name=dvd
# baseurl=file:///dvd
# gpgcheck=0
# enable=1

yum install gcc -y
```

### 网络配置 (nmcli)

```bash
nmcli con show                  # 查看连接
nmcli con add con-name "static" type ethernet ifname eth0
nmcli con mod "static" ipv4.addresses 192.168.1.100/24
nmcli con mod "static" ipv4.gateway 192.168.1.1
nmcli con mod "static" ipv4.method manual
nmcli con up "static"
```

---

## 第八章：ELF文件与工具

### readelf

```bash
readelf -h a.out    # ELF头
readelf -S a.out    # 节头表
readelf -l a.out    # 段头表
readelf -s a.out    # 符号表
readelf -d a.out    # 动态链接信息
```

### nm

```bash
nm -C -n -l a.out   # 查看符号（-C demangle, -n 按地址排序）
```

### patchelf

```bash
patchelf --set-rpath /opt/lib my-program   # 修改RPATH
patchelf --set-interpreter /lib/ld.so prog # 修改动态链接器
```

### ldd

```bash
ldd a.out    # 查看动态库依赖
```

---

## 推荐阅读

- 《鸟哥的Linux私房菜》— Linux入门经典
- 《UNIX环境高级编程》(APUE) — 系统编程圣经
- 《程序员的自我修养—链接、装载与库》— 理解编译链接
- 《Linux内核精髓—精通Linux内核必会的75个绝技》


---
