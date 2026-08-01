# Linux系统管理


## Linux日志_计划任务_主机名_系统时间

- [一、日志](#一日志)
  - [1、rsyslog日志文件](#1rsyslog日志文件)
  - [2、日志级别](#2日志级别)
  - [3、查看systemd日志](#3查看systemd日志)
  - [4、保存systemd日志](#4保存systemd日志)
- [二、Red Hat7中查看系统时间](#二red-hat7中查看系统时间)
- [三、计划任务](#三计划任务)
- [四、主机名](#四主机名)
- [五、说明](#五说明)

今天，来了解学习 Linux 下日志、计划任务、主机名、以及系统时间这些基础知识。

## 一、日志

进程和操作系统内核需要能够为发生的事情记录日志，这些日志可用于系统审核和问题的故障排除。按照管理，这些日志永久存储在/var/log。

在Red Hat7版本中，有两个日志服务，分别是rsyslog和systemd-journal。

systemd-journal是一种改进型的日志管理服务，可以收集来自内核、启动过程的早期阶段、标准输出、系统日志，以及守护进程启动和运行期间错误的消息。它将这些消息写入到一个结构化事件中，默认情况向下并不会持久化保存日志，每次重启之后，之前的日志都会丢失。另外，一些rsyslog无法收集的日志也会被写入systemd-journal。

### 1、rsyslog日志文件

**rsyslog把收集到的日志都记录在/var/log目录下的各个日志文件中。**
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsehyp13PialMAOgiaKUKF6RdUng6OTcxHNgOL8xFJ0YUvawaWa3Yb6um0Y4UWT2Q6paZ2e8taun5WA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(常见的日志文件)</p>

systemctl status rsyslog   查看rsyalog服务是否运行；其配置文件在  /etc/rsyslog.conf，每一个日志类型，记录某一类的日志到某个文件中。

### 2、日志级别

编号|优先级|严重性
|:--|:--|:--|
0|emerg|系统不可用
1|alert|必须立即采取措施
2|crit|严重状况
3|err|非常严重的错误状况
4|warning|警告
5|notice|正常但重要的事件
6|info|信息性事件
7|debug|调试级别消息

查看rsyslog配置文件：vim /etc/rsyslog.conf。

***凡是修改过配置文件的，都必须重启。***

### 3、查看systemd日志

查看systemd日志条目  专门的命令 journalctl。

journalctl 用来查看所有的日志

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsehyp13PialMAOgiaKUKF6RdAD4AGeGgpku7bau1PymSPLJn3Gxric2WFoIpvgu5vo9Fb3CLXmJD4ibQ/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看所有日志)</p>

journalctl -n [NUM] 默认显示最后10个日志条目

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsehyp13PialMAOgiaKUKF6Rd3q4b8ZqwaZf13jUgR3DNDJRcMPUHqAAuO7kkWCutNeNyWZNYU9rItQ/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看最后10条日志)</p>

journalctl -p err  过滤日志级别输出

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsehyp13PialMAOgiaKUKF6RdRiaWl4FF0WOx5lUxicoBMqRjXlCdSpZMQfuxyXStDwKVsdqeFvzibDRgg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(日志级别过滤输出)</p>

还可以输出具体时间范围，两个选项-since和-until，接受的时间格式为YYY-MM-DD hh:mm:ss,如果省略日期，则命令会假定为当天的日期；如果省略时间，则假定为00:00:00，除了具体的日期时间外，这两个选项还接受yesterday，today，tomorrow。

### 4、保存systemd日志

一般情况下保存在/etc/log/journal,这样就可以实现持久化systemd日志，但是默认情况下只会保存一个月的日志信息，可在配置文件/etc/systemd/journald.conf中调节。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsehyp13PialMAOgiaKUKF6RdcZXI8USfnFxTPGWQaN1DAic0pIRLibW8lVp8mcfCbTFZlnOEt7Zibz19g/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(默认保存一个月)</p>

## 二、Red Hat7中查看系统时间

配置文件在/etc/chrony.confz中。

命令|解释
|:--|:--|
timedatectl|查看系统时间
timedatectl list-timezones|列出时区信息
timedatectl set-timezone Asia/Shanghai|设置时区
timedatectl set-time 22:19:00[YYY-MM-DD hh:mm:ss]|设置时间日期
timedatectl set-ntp[true|false]|启动或禁用NTP(网络时间协议)同步

## 三、计划任务

1. 在未来的某个时间点执行一次某任务，相关命令：at  比较简单，不再多说。
2. 周期性的执行某任务
   - cron: 自身是一个不间断运行的服务；
   - 对cron任务来说，分两类：系统cron任务，与用户无关，是系统周期性的维护，格式：分钟 小时 日 月 周 用户 任务；

用户cron任务：通常定义在/var/spool/cron/USERNAME目录下，格式：分钟 小时 日 月 周 任务。

时间的有效值：
> 分钟   0-59
> 
> 小时   0-23
> 
> 日    1-31
> 
> 月    1-12
> 
> 周    0-7 :0和7都表示周日
> 

时间通配符：
- \*   对应的所有有效值
- \，  离散时间点取值
- \-   连续的时间点
- \/   对应取值范围内每多久一次

用户cron任务的管理，crontab该命令可以实现对语法的检测：

选项|解释
-l|列出当前用户的cron任务
-e|编辑当前用户的cron任务
-r|移除所有的cron任务
-u USERNAME|管理其他用户的cron,只有root可用

## 四、主机名

- hostname   查看主机名；
- hostname "HOSTNAME"   临时修改主机名；

静态主机名保存在/etc/hostname文件中，hostnamectl可以修改此文件。

hostnamectl set-hostname HOSTNAME   永久修改主机名；

有个名称解析：用于将主机名转换为IP地址，反之亦可。  

## 五、说明

原创文章链接：[Linux日志，计划任务，主机名，系统时间！](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483794&idx=1&sn=b375582a39bb05ca48d3dfa548f3e16f&chksm=f94c8bafce3b02b946ca69fb0465fe0d2984c1d5dc9ea88b6f68f029c26b9444340a88ed3ead&scene=21#wechat_redirect)


---


## Linux网络简单配置

- [一、ip](#一ip)
- [二、nmcli](#二nmcli)
- [三、nmcli创建新的连接](#三nmcli创建新的连接)
- [四、说明](#四说明)

Linux 网络简单配置是 Linux 基础之一。

TCP/IP四层模型、IPV4地址、IPV4路由、网络接口名称；

**Red Hat7之前的系统以eth0, eth1等名字来命名网卡，在rhel7系统中开始使用新的命名规范：基于固件、设备结构、设备类型。**

## 一、ip

- ip 命令可用于显示设备和地址信息
- ip命令也可用于显示关于网络性能的统计信息
- ip route 显示路由信息

## 二、nmcli

使用nmcli配置网络，一些常见的命令：

name|连接的名称
|:--|:--|
UUID|连接的UUID
TYPE|连接的类型
DEVIDE|连接绑定的设备

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdA1FR7XQ6iaOQO6MERnG1Fby30nSppIBOBhxqYehTSuBF9bicEIk3LABw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(仅显示活动的连接)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdDL57f7FsKxtcQLuXmVA6Qfia9GanOGgYHbmribfwiag9wy5icKG7ZNv3bg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(某特定连接)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdS5ibR553iaGn7os2NoF1jiaC7PyVHsSzicicHibIof5sCqB7srgZCVjNOqcA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(特定连接的详细信息)</p>

## 三、nmcli创建新的连接

使用nmcli创建新的连接，连接其实就是给一个物理网卡创建一个配置信息。

定义一个名字为default的连接，该连接会通过DHCP自动获取IP地址等信息。

命令：nmcli con add con-name "default" type ethernet ifname eth0

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdQViaHWAHD9ibk0QtyG5eVX3b1dmf8iaSAbblo8DpTpIY42DFo2vsGMkKA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdibiavK244I2O61IJicCd4ib9FqhEgwL2GUKJKrUL4TU947uwibxlTc16UFA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8Qdv0k6jibsbvib6rQMljKgSz9OdknAicc2ichlKEWW2WZib9mC2RV8CNzklSg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdnOcxjONmNtJpVBn9L6YzVVfZZkBSH55nOEpYF6ByOmic3yy9A9MicNMQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**通过nmcli修改网络接口，可以通过nmcli con mod 参数修改现有的连接。**

关闭static的自动连接功能：nmcli con mod "static" connection.autoconnect no

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdhBhhXNkw5O815ed196JicHRK6hWIJSRicoIg1ZibicSUrUwtbPic41yOPuw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(关闭static的自动连接功能)</p>

其他命令：
命令|解释
|:--|:--|
nmcli con del ""|删除一个连接
nmcli net off|关闭所有接口的连接
nmcli dev dis|关闭某个接口，并临时禁用自动连接
nmcli con down ""|断开某个连接

图形界面配置网络：nm-connection-editor

## 四、说明

原创文章链接：[Linux 网络简单配置](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483800&idx=1&sn=fbbd2dcaedb96473b9b22fe81cca4d27&chksm=f94c8ba5ce3b02b30daf49fe452ff850354705ab3e6044dfc323c87435d99d44ce5706fab83b&scene=21#wechat_redirect)


---


## RedHat7版本本地仓库yum源的配置

- [一、yum 配置](#一yum-配置)
- [二、yum命令](#二yum命令)
- [三、说明](#三说明)

对于 Linux 使用 Red Hat 版本的，需要学会 yum 源的配置，其后安装软件、配置开发环境相当方便。

## 一、yum 配置

- mkdir /dvd  :创建一个目录，因为挂载点必须是目录；
- mount /dev/sr0 /dvd：挂载；
- df -h：查看是否挂载上；

vim /etc/yum.repos.d/rhel-dvd.repo：写yum源的配置文件；

yum repolist :看一下本地仓库的信息。

写配置文件：

> [rhel-dvd]
> 
> name=dvd
> 
> baseurl=file:///dvd
> 
> gpgcheck = 0   : 不检查签名
> 
> enable = 1    ：启用当前仓库

注意：

1. **/dvd下必须有镜像，可以拿U盘拷一个镜像文件，或虚拟机->设置->CD/DVD->浏览->复制，粘贴，(从物理机上弄一个iOS镜像文件)：粘过来的存放在/tmp下，利用find命令找到即，再移到/dvd下。**
2. **每次重新进入终端时，必须重新挂载即可，便可安装软件包。**

## 二、yum命令

yum安装软件包：可以解决依赖关系；

yum install gcc 安装gcc开发工具；

yum install gcc -y / yum install -y gcc 安装过程中没有提示，直接安装；

yum remove gcc 移除gcc；

提示信息：-d 只下载不安装。

**在安装软件时最好使用 yum install *vnc* 匹配安装更好，相关的就全部装上了。**

**ubuntu 是开源的Linux操作系统，使用apt命令安装工具，不用配置本地仓库，在安装软件时但必须联网，直接从官网下载！**

## 三、说明

原创文章链接：[Red Hat7版本本地仓库yum源的配置](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483781&idx=1&sn=6f6b43140c1489b5d1daa70537d3d0ad&chksm=f94c8bb8ce3b02ae4435f82923ed53dcefc019a8548ed9649bdb9ac2da953173d241e670d9f5&scene=21#wechat_redirect)


---
