# Qt开发指南


## 00-Qt开发指南


> Qt 是跨平台的C++ GUI框架，广泛用于桌面应用和嵌入式HMI开发。

---

## 📖 学习资料

| 资料 | 路径 |
|------|------|
| Qt6讲义 | [Qt6讲义](../../My/C++/Qt6讲义.pdf) |
| Qt开发面试题汇总 | [面试题汇总](../../My/Qt/QT开发面试题汇总.pdf) |

---

## 🎯 Qt 核心概念

### 信号与槽（Signal & Slot）

Qt的核心通信机制，观察者模式的实现：

```cpp
// 连接信号与槽
connect(sender, SIGNAL(valueChanged(int)),
        receiver, SLOT(onValueChanged(int)));

// Qt5 新语法（编译期检查）
connect(sender, &Sender::valueChanged,
        receiver, &Receiver::onValueChanged);
```

### 父子对象树

Qt通过父子关系自动管理对象生命周期：

```cpp
QWidget *parent = new QWidget;
QPushButton *btn = new QPushButton("Click", parent);
// parent 销毁时会自动删除 btn
```

### 事件循环

```cpp
QApplication app(argc, argv);
// ... 创建窗口 ...
return app.exec();  // 进入事件循环
```

---

## 🌐 Qt + OpenHarmony 交叉编译

| 资料 | 路径 |
|------|------|
| 交叉编译搭建步骤 | > **Qt-OpenHarmony交叉编译**




## 1、安装Ubuntu-22.04

[Unbun-22.04 下载路径](https://releases.ubuntu.com/24.04/ubuntu-24.04-desktop-amd64.iso)



## 2、部署gitlab服务器

以便于合并ohos标准提供patch包



### 2.1 安装gitlab，配置ip，端口



#### （1）安装gitlab及依赖		

```bash
$ sudo apt-get update
$ sudo apt-get install -y curl openssh-server ca-certificates postfix 
$ sudo apt-get install gitlab-ce
```

> 若 ”E: 无法定位软件包 gitlab-ce“
>
> 执行以下操作：
>
> ```bash
> # 若没有curl 自行安装
> $ apt install curl
> 
> # deb脚本安装
> $ curl -s https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.deb.sh | sudo bash
> 
> # 重新执行
> $ apt-get install gitlab-ce
> ```
>
> 即可解决此问题

#### （2）信任GitlLab的GPG公钥

```bash
$ curl https://packages.gitlab.com/gpg.key 2>/dev/null | sudo apt -key add - &>/dev/null
```

#### （3）配置IP

```bash
$ sudo vim /etc/gitlab/gitlab.rb

# 修改为gitlab服务器网址
# external_url ' http://127.0.0.1'  
```

#### （4）更改服务器端口

```bash
$ sudo vim /etc/gitlab/gitlab.rb
            
# 找到端口修改，端口号相同不同改
# nginx['listen_port' ]=8090

# 此端口不一定需要
# unicorn['port'] = 8070  
```

#### （5）启动服务

```bash
# 启动 ssh 服务器
$ service sshd start

# 启动 postfix 邮件传输代理
$ service postfix start

# 重新配置gitlab
$ sudo gitlab-ctl reconfigure

# 重启 gitlab 服务
$ sudo gitlab-ctl restart

# 查看 gitlab 服务
$ gitlab-ctl status
```



### 2.2 执行管理员操作



### （1）修改 root 管理员密码

```bash
$ sudo passwd root
```

### （2）添加一行 group 组，dev

```bash
$ sudo groupadd dev 
```

### （3）添加一个 user 账户，指定用户组，修改用户密码

```bash
$ sudo useradd -m ohos -G dev
$ sudo passwd ohos
```

### （4）分配用户权限

```bash
$ sudo vim /etc/sudoers

# 添加权限
$ ohos    ALL=(ALL:ALL) ALL
```

### （5）设置用户命令解释器

```bash
$ sudo vim /etc/passwd

$ ohos:x:1001:1002::/home/ohos:/bin/sh -->
$ ohos:x:1001:1002::/home/ohos:/bin/bash
```



### 2.3 qt 源码补丁应用



### （1）创建一个project项目，比如qt5base， 指定project的组

```bash
# 此种方式只是切换了root身份，但Shell环境仍是普通用户的Shell,此步骤关系到后面 root权限下使用 sdk ohos的环境变量问题
$ su root

$ mkdir /opt/qt5base
$ chown -R root:dev /opt/qt5base
$ chmod -R 775 /opt/qt5base
```

### <font color='red'>（2）下载 qt-5.15.12 提供的补丁包</font>

> [qt-master.zip](https://gitee.com/openharmony-sig/qt)

### <font color='red'>（3）qt官网下载 qt-5.15.12</font>

> [qt-5.15.12](https://download.qt.io/archive/qt/5.15/5.15.12/single/qt-everywhere-opensource-src-5.15.12.tar.xz) 
>
> [qtbase-5.15.12](https://download.qt.io/archive/qt/5.15/5.15.12/submodules/qtbase-everywhere-opensource-src-5.15.12.tar.xz)

> qt-5.15.12是完整源码包
>
> qtbase-5.15.12是基础库模块
>
> 可按需求下载，本次编译使用的是 qt-5.15.12

### （4）解压缩 qt-master.zip qt-ereywhere-src-5.5.12.tar.xz

```bash
$ cp qt-master.zip qt-ereywhere-src-5.5.12.tar.xz /opt/qt5base
$ cd /opt/qt5base
$ tar -xvf qt-ereywhere-src-5.5.12.tar.xz
$ unzip qt-master.zip
```

### （5）使用 git 保存第一次源码提交。不需要 push 到服务器

```bash
$ cd qt-ereywhere-src-5.5.12
$ git init .
$ git add .
$ git commit -m "add original qt-source-5.15.12" 
```

### （6）在本地执行补丁，合并代码

#### 	方法一：

```bash
# 转到qtbase路径下
$ cd /opt/qt5base/qt-ereywhere-src-5.5.12/qtbase

$ git apply  ../../qt-master/qtbase.patch --check  
$ git apply  ../../qt-master/qtbase.patch -v
```

#### 	方法二：

```bash
# 转到qtbase路径下
$ cd /opt/qt5base/qt-ereywhere-src-5.5.12/qtbase

# 应用补丁到多个文件
$ cat ../../qt-master/qtbase.patch | patch -p1
```



## 3、部署openhomeny sdk交叉编译工具



### （1）解压缩

```bash
$ cd /opt/
$ tar -xvf Master_OpenHarmony_4.0.10.5-20230824_120941-ohos-sdk-full_monthly.tar.gz
# 目标路径为/opt/ohos-sdk
```

> [参考网址](https://gitee.com/openharmony-sig/tpc_c_cplusplus/blob/master/lycium/doc/ohos_use_sdk/OHOS_SDK-Usage.md)

### （2）修改ohos账户的 ~/.bashrc 文件，导出环境变量

```bash
# OHOS_SDK_PATH 路径一定与解压缩路径一致才可以
export OHOS_SDK_PATH=/opt/ohos-sdk/linux
export AS=${OHOS_SDK_PATH}/native/llvm/bin/llvm-as
export CC="${OHOS_SDK_PATH}/native/llvm/bin/clang --target=aarch64-linux-ohos"
export CXX="${OHOS_SDK_PATH}/native/llvm/bin/clang++ --target=aarch64-linux-ohos"
export LD=${OHOS_SDK_PATH}/native/llvm/bin/ld.lld
export STRIP=${OHOS_SDK_PATH}/native/llvm/bin/llvm-strip
export RANLIB=${OHOS_SDK_PATH}/native/llvm/bin/llvm-ranlib
export OBJDUMP=${OHOS_SDK_PATH}/native/llvm/bin/llvm-objdump
export OBJCOPY=${OHOS_SDK_PATH}/native/llvm/bin/llvm-objcopy
export NM=${OHOS_SDK_PATH}/native/llvm/bin/llvm-nm
export AR=${OHOS_SDK_PATH}/native/llvm/bin/llvm-ar
export CFLAGS="-fPIC -D__MUSL__=1"
export CXXFLAGS="-fPIC -D__MUSL__=1"
```

### （3）执行文件，让环境变量生效

```bash
$ source ~/.bashrc
```



## 4、编译安装



### （1）复制应用补丁后的qtbase模块，到编译路径

```bash
$ cp /op/qt5base/qt-everywhere-src-5.15.12/qtbase /opt/qt5/qt5-base
$ cd /opt/qt5/qt5-base
```

### （2）修改 qt5-base/mkspec/oh-clang/qmake.conf ，增加宏定义

```bash
OHOS_ARCH=arm64-v8a
```

### （3）配置Qt5的编译选项

```bash
$ ./configure -prefix /opt/qt5/qt5-lib -opensource -confirm-license -release -strip -shared -nomake examples -nomake tests -xplatform oh-clang  
```

> you don‘t seem to have ‘make‘ or ‘qmake‘ in your PATH
>
> ```bash
> $ sudo apt-get install build-essential
> ```
>
> Ubuntu缺省情况下，并没有提供C/C++的编译环境，因此还需要手动安装。但是如果单独安装gcc以及g++比较麻烦，幸运的是，Ubuntu提供了一个build-essential软件包。

### （3）包含OpenHarnony头文件路径

```bash
# 修改corelib、network、 gui工程INCLUDE_PATH, 包含\corelib\kernel路径，以便包含openharmoney的头文件

$ vim qt5-base/src/corelib/text/text.pri 
$ openharmony {
    INCLUDEPATH += ./kernel/
    SOURCES += text/qlocale_harmony.cpp
  }

$ vim  qt5-base/src/corelib/corelib.pro
$ INCLUDE_PATH += ./kernel
 
$ vim qt5-base/src/network/network.pro
$ INCLUDE_PATH += ../corelib/kernel

$ vim qt5-base/src/gui/gui.pro
$ INCLUDE_PATH += ../corelib/kernel
```

### （4）头文件名被截断，重新改名

```bash

# ***************************本次操作未遇到，仅供参考***********************************

# 修改/src/3rdparty/double-conversion/include/double-conversion/double-con 
# 修改\include\QtNetwork\5.15.12\QtNetwork\private下头文件h, 有7、8个文件名被截断
# 修改\include\QtGui\5.15.12\QtGui\private, 有2个文件名被截断
# 修改\include\QtGui\5.15.12\QtWidget\private, 有7、8个文件名被截断

$ cd /src/3rdparty/double-conversion/include/double-conversion
$ mv double-con double-conversion.h

$ cd /include/QtNetwork/5.15.12/QtNetwork/private/
$ mv qsharednetworksession_p qsharednetworksession_p.h
$ mv qabstractnetworkcache_p qabstractnetworkcache_p.h
$ mv qhttpnetworkconnectionc qhttpnetworkconnectionchannel_p.h
$ mv qhttpnetworkconnection_ qhttpnetworkconnection_p.h
$ mv qabstractprotocolhandle qabstractprotocolhandler_p.h
$ mv qhttp2protocolhandler_p qhttp2protocolhandler_p.h
$ mv qabstractsocketengine_p qabstractsocketengine_p.h
$ mv qhttpprotocolhandler_p_ qhttpprotocolhandler_p.h
$ mv qspdyprotocolhandler_p_ qspdyprotocolhandler_p.h
$ mv qnetworkconfiguration_p qnetworkconfiguration_p.h

$ cd /include//QtGui/5.15.12/QtGui/private/
$ mv qopenglversionfunctionsfactory_  qopenglversionfunctionsfactory_p.h
$ vim /src/gui/util/qopenharmonywindowadapter.cpp

$ cd /include/QtWidgets/5.15.12/QtWidgets/private/ 
$ mv qaccessiblewidgetfactor qaccessiblewidgetfactory_p.h
$ mv qwidgetrepaintmanager_p qwidgetrepaintmanager_p.h
$ mv qgraphicsproxywidget_p_ qgraphicsproxywidget_p.h
$ mv qwidgetresizehandler_p_ qwidgetresizehandler_p.h
$ mv qabstractitemdelegate_p qabstractitemdelegate_p.h
$ mv qtreewidgetitemiterator qtreewidgetitemiterator_p.h
$ mv qgraphicsscenebsptreein qgraphicsscenebsptreeindex_p.h
$ mv qgraphicsscenelinearind qgraphicsscenelinearindex_p.h
```

### （5）编译

```bash
$ gmake
```

### （6）报错

```c
/* 
kernel/qopenharmonyjsobject.h:8:10: fatal error: 'QtCore/qopenharmonyjsfunction.h' file not found
#include <QtCore/qopenharmonyjsfunction.h>
*/
```

```bash
$ cp qt5-base/src/corelib/kernel/qopenharmony* include/QtCore/
```





```c
/*
	util/qopenharmonywindowadapter.cpp:2:10: error: 'adapter_c.h' file not found with <angled> include; 	use "quotes" instead
	#include <adapter_c.h>
         	^~~~~~~~~~~~~
         	"adapter_c.h"
*/
```

```bash
"adapter_c.h"
```





```c
/*
	qopenharmonyplatformforeignwindow.cpp:1:10: fatal error: 'adapter_c.h' file not found
	#include <adapter_c.h>
*/
```

```bash
$ cp src/gui/util/adapter_c.* include/QtGui/
$ cp src/gui/util/qopenharmonywindowadapter.* include/QtGui/
```





```c
/*
	qopenharmonymain.cpp:18:10: fatal error: 'QtCore/private/qopenharmonyhelpers_p.h' file not found
	#include <QtCore/private/qopenharmonyhelpers_p.h>
*/
```

```bash
 #include <QtCore/qopenharmonyhelpers_p.h>
```





```c
/*
	./qopenharmonyplatformservices.h:5:10: fatal error: 'QOpenHarmonyJsObject' file not found
	#include <QOpenHarmonyJsObject>
	
*/
```

```bash
$ cd  qt5-base
$ cp  include/QtCore/qopenharmonyjsobject.h include/QtCore/QOpenHarmonyJsObject
$ cp  include/QtCore/qopenharmonyjsenvironment.h include/QtCore/QOpenHarmonyJsEnvironment

$ cp  include/QtCore/qopenharmonyjsobjectloader.h include/QtCore/QOpenHarmonyJsObjectLoader
```

```bash
/*
	qopenharmonyplatformforeignwindow.cpp:1:10: fatal error: 'adapter_c.h' file not 	found
	#include <adapter_c.h>
*/
```



### （7）安装

```bash
$ gmake install
```



--- |

---

## 📁 常用Qt模块

| 模块 | 用途 |
|------|------|
| Qt Widgets | 传统桌面UI组件 |
| Qt Quick/QML | 现代触摸UI |
| Qt Network | 网络通信 |
| Qt SQL | 数据库操作 |
| Qt Multimedia | 音视频播放 |
| Qt SerialPort | 串口通信（嵌入式常用）|


---
