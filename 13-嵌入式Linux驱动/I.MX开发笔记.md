# ALPHA I.MX开发笔记


## 4. ALPHA I.MX系统移植与使用

## ALPHA I.MX系统移植与使用 - HQ

[TOC]

------

#### 注意

- 系统移植注意的几个点
  - 开发板如果是通过tftp下载内核和设备树并进行启动的话，是将内核和设备树下载到RAM里面，断电丢失。
  - 无论是通过emmc还是sd卡的uboot启动，在执行 `setenv`后将保存更改
- 

------

# 内核移植步骤

<img src="assets/内核移植步骤.png" alt="内核移植步骤" style="zoom:67%;" />

# 阿尔法开发板使用

【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 

### 前期准备工作

【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 

1. 安装ssh，配置FileZilla   （4.2）

2. 安装交叉编译工具链及相关库  （4.3.1）

3. 安装烧写软件imxdownload  （8.4.3）

4. Ubuntu下NFS和SSH服务开启 （4.2）

   1. > ![image-20220320155159064](assets/image-20220320155159064.png)
      >
      > ![image-20220320155211514](assets/image-20220320155211514.png)


### 固化系统（初试）

【正点原子】I.MX6U用户快速体验V1.9.pdf

1. 安装CH340驱动，MobaXterm串口调试终端软件 （2.1）
2. 固化系统 - 2.2
   1. 使用mfgtool上位机固化系统（OTG方式）
      1. 固化系统到SD卡
      2. 固化系统到emmc
   2. 使用脚本固化系统（虚拟机内）
      1. 固化系统到SD卡
      2. 固化系统到emmc

### ATK I.MX6U 交叉编译（初试）

【正点原子】I.MX6U用户快速体验V1.9.pdf

1. 安装Poky交叉编译工具链（4.2）
2. 编译出厂源码U-boot  (4.3)
3. 编译出厂源码内核及模块 （4.4）

### 开发板网络环境搭建

参考教程【【正点原子】I.MX6U网络环境TFTP&NFS搭建手册V1.3.1】

### 其他模块使用

#### 配置wifi模块

【正点原子】I.MX6U用户快速体验V1.9 —— 第三章 ATK I.MX6U功能测试 3.24 SDIO WIFI测试

1. 模块型号  RTL8189_WIFI 版本 1.4

2. 按照教程步骤，初始化 —— 配置无线账号密码 —— 测试连接

   > <img src="assets/image-20220315110927157.png" alt="image-20220315110927157" style="zoom:67%;" />
   >
   > ![image-20220315110940085](assets/image-20220315110940085.png)
   >
   > ![image-20220315111017416](assets/image-20220315111017416.png)
   >
   > ![image-20220315111035231](assets/image-20220315111035231.png)
   >
   > ![image-20220315111312458](assets/image-20220315111312458.png)

3. 配置成功

   > <img src="assets/image-20220314172444206.png" alt="image-20220314172444206" style="zoom:67%;" />

4. ssh连接

   > <img src="assets/image-20220314173710857.png" alt="image-20220314173710857" style="zoom:50%;" />

5. 每次开机都要进行初始化配置，如，运行脚本（安装驱动模块，解锁射频，杀死后天运行的程序），开启SDIO WIFI，连接配置的无线网络。所以写了一个脚本如下（由于汉字乱码，没有加上注释）。

   > ![image-20220315111355308](assets/image-20220315111355308.png)

### 开机网络自启动设置

1. > ![image-20220320204243963](assets/image-20220320204243963.png)![image-20220320204319954](assets/image-20220320204319954.png)
   >
   > ![image-20220320204339958](assets/image-20220320204339958.png)
   >
   > ![image-20220320204352809](assets/image-20220320204352809.png)



### Linux内核挂载文件系统的几种方式

搭建NFS环境可另外参考教程【【正点原子】I.MX6U网络环境TFTP&NFS搭建手册V1.3.1】

#### 1. 启动系统时通过nfs方式挂载（挂载的为文件系统）

- 设置环境变量 bootargs 来挂载 nfs 共享目录下的 rootfs 文件系统到开发板内存中。

- `setenv bootargs 'console=ttymxc0,115200 root=/dev/nfs nfsroot=192.168.10.100:/home/alientek/linux/nfs/rootfs,proto=tcp rw ip=192.168.10.50:192.168.10.100:192.168.10.1:255.255.255.0::eth0:off'`

- > ![image-20220402205608958](assets/image-20220402205608958.png)

> `/mnt/rootfs/rootfs`文件夹路径
>
> `192.168.1.105`为客户端ip
>
> `192.168.1.88`  为ubootip

#### 2.启动系统时从块设备挂载（挂载的为文件系统）

- `bootargs=console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext2`

> `mmcblk0p2`代表0号mmc的2扇区
>
> `rootfstype=ext2`文件系统格式

#### 3.在系统中通过nfs挂载（挂载的为文件夹）

参考教程【【正点原子】I.MX6U网络环境TFTP&NFS搭建手册V1.3.1 - 第三章，第四章】

1. 虚拟机安装NFS服务

2. 虚拟机设置NFS共享目录

3. 虚拟机配置NFS服务

4. 开发板通过NFS挂载文件系统（实验成功）

   `mount -t nfs -o nolock,nfsvers=3 192.168.1.101:/home/hq/linux/nfs get/`

   挂载到的本地文件夹可使用绝对路径或相对路径   `../get/`   
   
   > ![image-20220402203359623](assets/image-20220402203359623.png)

**其他步骤**

1. 使用网络nfs给开发板挂载Ubuntu的文件系统

   ```cpp
   使用网络nfs给开发板挂载ubuntu的文件系统：
   
   ubuntu先安装nfs服务：sudo apt-get install nfs-kernel-server rpcbind
   配置相关文件夹为nfs文件夹：sudo vi /etc/exports
   在最后一行加上文件夹路径：/home/qing/work/nfs/rootfs_friendlycore-focal_4.14   *(rw,sync,no_root_squash)
   然后重启ubuntu服务：sudo /etc/init.d/nfs-kernel-server restart
   被挂载的文件夹最好 ：chmod 777  xxx/
   
   在开发板里面也要安装nfs服务：sudo apt-get install nfs-kernel-server rpcbind
   重启开发板的nfs服务:        sudo /etc/init.d/nfs-kernel-server restart
   然后挂载ubuntu配置好的文件夹到你想挂载到的目录了：sudo mount -t nfs 192.168.43.167:/home/qing/work/nfs/rootfs_friendlycore-focal_4.14/ /mnt/ -o nolock
   要退出挂载就：sudo umount /mnt/   要先退出这个挂载的目录，不然会提示你正busy
   ```

   > ![image-20220324095111711](assets/image-20220324095111711.png)





# Linux系统移植学习

【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6  ——  第三章 系统移植篇 （P683）



## U-Boot使用实验（第三十章）

1. U-Boot初次编译（30.2）

2. U-Boot烧写与启动（30.3）

3. U-Boot命令使用（30.4）

   1. 环境变量操作命令

   2. 内存操作命令

   3. 网络操作命令

      1. ![image-20220320111117003](assets/image-20220320111117003.png)

      2. ```cpp
         //配置网络环境变量
         setenv ipaddr 192.168.3.140
         setenv ethaddr b8:ae:1d:02:00:00
         setenv gatewayip 192.168.3.1
         setenv serverip 192.168.3.138
         setenv netmask 255.255.255.0
         saveenv
         ```
      
      3. uboot网络常用命令
      
         1. `ping`    开发板的网络能否使用，是否可以和服务器(Ubuntu 主机)进行通信，通过 ping 命令就可
            以验证，直接 ping 服务器的 IP 地址即可
         2. `dhcp`   dhcp 用于从路由器获取 IP 地址，前提得开发板连接到路由器上的，如果开发板是和电脑
            直连的，那么 dhcp 命令就会失效。直接输入 dhcp 命令即可通过路由器获取到 IP 地址
      
      4. 使用tftp下载文件过程
      
         1. `sudo server tftpd-hpa start`   Ubuntu中启动tftp服务器
      
         2. ```cpp
            //设置 bootargs 和 bootcmd 这两个环境变量，开发板启动后将自动运行，下载
            setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p2 rootwait rw'
            setenv bootcmd 'tftp 80800000 zImage; tftp 83000000 imx6ull-alientek-emmc.dtb; bootz 80800000 - 83000000'`
            saveenv
            ```
      
         3. ```cpp
            //手动下载
            zImage 和 imx6ull-14x14-evk.dtb 下载到开发板中并启动：
            tftp 80800000 zImage   //开发板下载虚拟机tftpboot文件夹中的zImage文件到DRAM的0X80800000地址处
            tftp 83000000 imx6ull-14x14-evk.dtb   //下载设备树
            bootz 80800000 - 83000000  //启动内核
            ```
      
      5. nfs命令   （nfs 网络文件系统）
      
         1. 通过 nfs 可以在计算机之间通过网络来分享资源，比如我们将 linux 镜像和设备树文件放到 Ubuntu 中，然后在 uboot 中使用 nfs 命令将 Ubuntu 中的 linux 镜像和设备树下载到开发板的 DRAM 中。
      
         2. ```cpp
            使用前准备工作
            sudo apt-get install nfs-kernel-server  //安装nfs
            
            sudo vi /etc/exports  //修改nfs配置文件，将nfs运行挂载的目录在exports中定义
            //以后在后面添加如下所示内容： 
            /home/kennan/linux/nfs *(rw,sync,no_root_squash)
            
            //开发板使用命令
            nfs 80800000 192.168.3.140:/home/hq/linux/nfs/zImage
            ```
      
         3. ```cpp
            使用时，开发板一直连接不上
            重启NFS服务，使用如下命令： sudo service nfs-kernel-server restart
            此时可以运行以下命令来显示共享的目录：
            showmount -e
            在nfs运行的过程中，修改了/etc/exports配置文件，可以使用exportfs命令使改动生效，具体命令：
            sudo exportfs -rv
            上述方法试了之后还是不行的，又继续搜到如下方案，
            在host文件中将开发板的IP地址增加进去，
            host文件在/etc/hosts中
            sudo vi /etc/hosts
            打开后加入 10.0.0.5    /home/kennan/linux/nfs/    
            
            也可能是uboot中使用得NFS版本为V2版本，而ubuntu中的NFS版本为V3,V4及以上版本，从而导致uboot不能再NFS服务器中找到文件
            
            解决办法为：让buntu中得NFS兼容V2。修改/etc/default/nfs-kernel-server 文件。
            
            操作方法如下：
            
            （1）打开文件：sudo vim /etc/default/nfs-kernel-server (注意一定要sudo或者root权限)
            
            （2）修改如图：
                
            最后重启Ubuntu
            ```
      
         4. > ![image-20220320163919892](assets/image-20220320163919892.png)
            >
            > ![image-20220320163929420](assets/image-20220320163929420.png)
            >
            > ![image-20220320164007283](assets/image-20220320164007283.png)


   4. 其他格式文件系统操作命令
      1. EMMC和SD卡操作命令
      2. FAT格式文件系统操作命令
      3. EXT格式文件系统操作命令
   5. BOOT操作命令
      1. 通过bootz命令启动zImage镜像文件
   6. 其他常用命令



## U-Boot顶层Makefile详解（第三十一章）

分析正点原子提供的uboot源码，重点是分析uboot启动流程

1. U-Boot工程目录分析

   > ![image-20220319110357266](assets/image-20220319110357266.png)
   >
   > ![image-20220319110422896](assets/image-20220319110422896.png)

2. VScode工程搭建（便于阅读源码）

3. U-Boot顶层Makefile分析（在编译 uboot 之前一定要使用 defconfig 来配置 uboot）

   1. 版本号

   2. MAKEFLAGS变量

   3. 命令输出

   4. 静默输出

   5. 设置编译结果输出目录

   6. 代码检查

   7. 模块编译

   8. 获取主机架构和系统

   9. 设置目标架构、交叉编译器和配置文件

   10. 调用scripts/Kbuild.include

   11. 交叉编译工具变量设置

   12. 导出其他变量

   13. make xxx_defconfig过程

   14. Makefile.build脚本分析

   15. make过程

       > ![image-20220319110724910](assets/image-20220319110724910.png)




## U-Boot启动流程详解（第三十二章）

分析uboot的启动流程，理清uboot是如何启动的。通过对uboot启动流程的梳理，可以掌握一些外设是在哪里被初始化的，当我们需要修改这些外设驱动的时候就会心里有数。另外，通过分析uboot的启动流程可以了解Linux内核是如何被启动的。

1. 链接脚本u-boot.lds详解

2. U-Boot启动流程详解

   1. reset函数源码详解

   2. lowlevel_init函数详解

   3. s_init函数详解

   4. _main函数详解

   5. board_init函数详解

      - > ![image-20220319143901025](assets/image-20220319143901025.png)

   6. relocate_code函数详解

   7. relocate_vectors函数详解

      - 重定位向量表

   8. board_init_r函数详解

   9. run_main_loop函数详解

      - uboot启动后3秒倒计时，判断是否要进入uboot命令模式

   10. cli_loop函数详解

       - uboot的命令行处理函数

   11. cmd_process函数详解

3. bootz启动Linux内核过程

   >![image-20220319145158119](assets/image-20220319145158119.png)

   1. images全局变量
   2. do_bootz函数
   3. bootz_start函数
   4. do_bootm_states函数
   5. bootm_os_get_boot_func函数
      - do_bootm_states 会调用 bootm_os_get_boot_func 来查找对应系统的启动函数
   6. do_bootm_linux函数
      - do_bootm_linux 就是最终启动 Linux 内核的函数



## U-Boot移植（第三十三章）

学习如何将NXP官方的 uboot 移植到正点原子的 I.MX6ULL 开发板上，学习如何在 uboot 中添加我们自己的板子。

1. NXP官方开发板 uboot 编译测试

   1. 查找NXP官方的开发板默认配置文件

   2. 编译NXP官方开发板对于的uboot

      - 三种编译方式

        - 直接命令行编译

          - `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_evk_emmc_defconfig`
          - `make V=1 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j16`

        - 在顶层 Makefile 中直接给 ARCH 和CORSS_COMPILE 赋值

          - > ![image-20220319152025362](assets/image-20220319152025362.png)

          - `make mx6ull_14x14_evk_emmc_defconfig`

          - `make V=1 -j16`

        - 编写shell脚本

          - ```shell
            1 #!/bin/bash
            2 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
            3 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihfmx6ull_14x14_evk_emmc_defconfig
            4 make V=1 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j16 
            ```

          - `./mx6ull_14x14_evk_emmc.sh`

   3. 烧写验证与驱动测试

      - `./imxdownload u-boot.bin /dev/sdc`   //烧写到SD卡中，不能烧写到/dev/sda或sda1里面

2. 在U-Boot中添加自己的开发板 (参考 NXP 官方的 I.MX6ULL EVK 开发板，学习如何在 uboot 中添加我们的开发板或者开发平台。)

   1. 添加开发板默认配置文件
      - 我们一般做产品的时候就会参考原厂的开发板做硬件，然后在原厂提供的 BSP 包上做修改，将 uboot 或者 linux kernel 移植到我们的硬件上。这个就是uboot 移植的一般流程：
        ①、在 uboot 中找到参考的开发平台，一般是原厂的开发板。
        ②、参考原厂开发板移植 uboot 到我们所使用的开发板上。
   2. 添加开发板对应的头文件
   3. 添加开发板对应的板级文件夹
   4. 修改U-Boot图形界面配置文件
   5. 使用新添加的板子配置编译uboot
   6. LCD驱动修改
   7. 网络驱动修改
   8. 其他需要修改的地方

3. bootcmd和bootargs环境变量

   1. 环境变量bootcmd
      - bootcmd 保存着 uboot 默认命令，uboot 倒计时结束以后就会执行 bootcmd 中的命令。这些命令一般都是用来启动 Linux 内核的，比如读取 EMMC 或者 NAND Flash 中的 Linux 内核镜像文件和设备树文件到 DRAM 中，然后启动 Linux 内核。
      - 可以在 uboot 启动以后进入命令行设置 bootcmd 环境变量的值。如果 EMMC 或者 NAND 中没有保存 bootcmd 的值，那么 uboot 就会使用默认的值，板子第一次运行 uboot 的时候都会使用默认值来设置 bootcmd 环境变量。
   2. 环境变量bootargs
      - bootargs 保存着 uboot 传递给 Linux 内核的参数
      - 常用参数
        - console 用来设置Linux终端（控制台）
        - root 用来设置根文件系统的位置
        - rootfstype 用于指定根文件系统类型

4. uboot启动Linux测试

   1. 从EMMC启动Linux系统
   2. 从网络启动Linux系统



## U-Boot图形化配置及其原理（第三十四章）

在前两章中我们知道 uboot 可以**通过 mx6ull_alientek_emmc_defconfig 来配置**，或者**通过文**
**件 mx6ull_alientek_emmc.h 来配置 uboot**。还有另外一种配置 uboot 的方法，就是图形化配置，以前的 uboot 是不支持图形化配置，只有 Linux 内核才支持图形化配置。不过不知道从什么时候开始，uboot 也支持图形化配置了，本章我们就来学习一下如何**通过图形化配置 uboot**，并且学习一下图形化配置的原理，因为后面学习 Linux 驱动开发的时候可能要修改图形配置文件。

1. U-Boot图形化配置体验
2. menuconfig图形化配置原理
   1. make menuconfig 过程分析
   2. Kconfig 语法简介



## Linux内核顶层Makefile详解（第三十五章）

1. Linux内核获取

2. Linux内核初次编译

   - ```cpp
     顶层 Makefile 代码段
     252 ARCH ?= arm
     253 CROSS_COMPILE ?= arm-linux-gnueabihf
     ---------------------------------------------
     make xxx_defconfig //使用默认配置文件配置 Linux
     make menuconfig //启动图形化配置界面
     make -j16 //编译 Linux
     ```

   - ```cpp
     mx6ull_alientek_emmc.sh 文件内容
     1 #!/bin/sh
     2 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
     3 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- imx_v7_defconfig //配置工程
     4 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig  //打开图形化界面进行配置
     5 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16  //进行编译
     ```

3. Linux工程目录分析

   - >![image-20220320091726539](assets/image-20220320091726539.png)
     >
     >![image-20220320091751658](assets/image-20220320091751658.png)
     >
     >![image-20220320091804045](assets/image-20220320091804045.png)

4. VSCode工程创建

5. 顶层Makefile详解
   1. make xxx_defconfig过程
   2. Makefile.build脚本分析
   3. make过程
   4. built-in.o文件编译生成过程
   5. make zImage过程
      - vmlinux、Image、zImage、uImage的区别
        - vmlinux 是 ELF 格式的文件，但是在实际中我们不会使用 vmlinux，而是使用 zImage 或 uImage 这样的 Linux 内核镜像文件
        - vmlinux 是编译出来的最原始的内核文件，是未压缩的，比如正点原子提供的 Linux 源
          码编译出来的 vmlinux 差不多有 16MB
        - Image 是 Linux 内核镜像文件，但是 Image 仅包含可执行的二进制数据。Image 就是使
          用 objcopy 取消掉 vmlinux 中的一些其他信息，比如符号表什么的。但是 Image 是没有压缩过的，Image 保存在 arch/arm/boot 目录下，其大小大概在 12MB 左右
        - zImage 是经过 gzip 压缩后的 Image，经过压缩以后其大小大概在 6MB 左右
        - uImage 是老版本 uboot 专用的镜像文件，uImag 是在 zImage 前面加了一个长度为 64
          字节的“头”，这个头信息描述了该镜像文件的类型、加载位置、生成时间、大小等信息。但是新的 uboot 已经支持了 zImage 启动！所以已经很少用到 uImage 了，除非你用的很古老的 uboot。



## Linux内核启动流程（第三十六章）

Linux 内核启动流程就分析到这里，**Linux 内核最终是需要和根文件系统打交道的，需要挂载根文件系统，并且执行根文件系统中的 init 程序，以此来进去用户态。**这里就正式引出了根文件系统，根文件系统也是我们系统移植的最后一片拼图。Linux 移植三巨头：uboot、Linuxkernel、rootfs(根文件系统)。

1. 链接脚本vmlinux.lds
2. Linux内核启动流程分析
   1. Linux内核入口stext
   2. _mmap_switched函数
   3. start_kernel函数
   4. rest_init函数
   5. init进程





## Linux内核移植（第三十七章）

简单总结一下移植步骤：
①、在 Linux 内核中查找可以参考的板子，一般都是半导体厂商自己做的开发板。
②、编译出参考板子对应的 zImage 和.dtb 文件。
③、使用参考板子的 zImage 文件和.dtb 文件在我们所使用的板子上启动 Linux 内核，看能否启动。
④、如果能启动的话就万事大吉，如果不能启动那就悲剧了，需要调试 Linux 内核。不过一般都会参考半导体官方的开发板设计自己的硬件，所以大部分情况下都会启动起来。启动Linux 内核用到的外设不多，一般就 DRAM(Uboot 都初始化好的)和串口。作为终端使用的串口一般都会参考半导体厂商的 Demo 板。
⑤、修改相应的驱动，像 NAND Flash、EMMC、SD 卡等驱动官方的 Linux 内核都是已经提供好了，基本不会出问题。重点是网络驱动，因为 Linux 驱动开发一般都要通过网络调试代码，所以一定要确保网络驱动工作正常。如果是处理器内部 MAC+外部 PHY 这种网络方案的话，一般网络驱动都很好处理，因为在 Linux 内核中是有外部 PHY 通用驱动的。只要设置好复位引脚、PHY 地址信息基本上都可以驱动起来。
⑥、Linux 内核启动以后需要根文件系统，如果没有根文件系统的话肯定会崩溃，所以确定 Linux内核移植成功以后就要开始根文件系统的构建。

1. 创建VSCode工程

2. NXP官方开发板Linux内核编译
   1. 修改顶层Makefile
   
   2. 配置并编译Linux内核
   
      - `make dtbs`   在Linux内核源码根目录下输入，命令为只编译设备树
   
   3. Linux内核启动测试
   
      - 从EMMC启动Linux系统
   
        - 从 EMMC 启动也就是将编译出来的 Linux 镜像文件 zImage 和设备树文件保存在 EMMC
          中，uboot 从 EMMC 中读取这两个文件并启动，这个是我们产品最终的启动方式。
        - 检查一下 EMMC 的分区 1 中有没有zImage 文件和设备树文件，输入命令“ls mmc 1:1”
        - `setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblklp2 rootwait rw'`
        - `setenv bootcmd 'mmc dev 1; fatload mmc 1:1 80800000 zImage; fatload mmc 1:1 83000000 imx6ull-alientek-emmc.dtb; bootz 80800000 - 83000000;'`
        - `saveenv`
   
      - 从网络启动Linux系统
   
        - 我们可以设置 linux 从网络启动，也就是将 linux 镜像文件和根文件系统都放到 Ubuntu 下某个指定的文件夹中，这样每次重新编译 linux 内核或者某个 linux 驱动以后只需要使用 cp 命令将其拷贝到这个指定的文件夹中即可，这样就不用需要频繁的烧写 EMMC，这样就加快了开发速度。
   
        - 以通过 nfs 或者 tftp 从 Ubuntu 中下载 zImage 和设备树文件，根文件系统的话也可以通过 nfs 挂载。
   
        - 使用 tftp 从 Ubuntu 中下载 zImage 和设备树文件，前提是要将 zImage 和设备树文件放到 Ubuntu 下的 tftp 目录中
   
        - 使用tftp下载文件过程
   
          1. `sudo server tftpd-hpa start`   Ubuntu中启动tftp服务器
   
          2. ```cpp
             //设置 bootargs 和 bootcmd 这两个环境变量，开发板启动后将自动运行，下载
             setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p2 rootwait rw'
             setenv bootcmd 'tftp 80800000 zImage; tftp 83000000 imx6ull-alientek-emmc.dtb; bootz 80800000 - 83000000'`
             saveenv
             ```
   
          3. ```cpp
             //手动下载zImage 和 imx6ull-14x14-evk.dtb 下载到开发板中并启动：
             tftp 80800000 zImage   //开发板下载虚拟机tftpboot文件夹中的zImage文件到DRAM的0X80800000地址处
             tftp 83000000 imx6ull-14x14-evk.dtb   //下载设备树
             bootz 80800000 - 83000000  //启动内核
             ```
   
   4. 根文件系统缺失错误
   
3. 在Linux中添加自己的开发板
   1. 添加开发板默认配置文件
   2. 添加开发板对于的设备树文件
   3. 编译测试
   
4. CPU主频和网络驱动修改
   1. CPU主频修改
   2. 使能8线EMMC驱动
   3. 修改网络驱动
   4. 保持修改后的图形化配置文件



## 根文件系统构建（第三十八章）

 rootfs(根文件系统)。学习一下根文件系统的组成以及如何构建根文件系统。这是 Linux 移植的最后一步，根文件系统构建好以后就意味着我们已经拥有了一个完整的、可以运行的最小系统。以后我们就在这个最小系统上编写、测试 Linux 驱动，移植一些第三方组件，逐步的完善这个最小系统。最终得到一个功能完善、驱动齐全、相对完善的操作系统。

1. 根文件系统简介

   - Linux 中的根文件系统更像是一个文件夹或者叫做目录(在我看来就是一个文件夹，只不过是特殊的文件夹)，在这个目录里面会有很多的子目录。根目录下和子目录中会有很多的文件，这些文件是 Linux 运行所必须的，比如库、常用的软件和命令、设备文件、配置文件等等。以后我们说到文件系统，如果不特别指明，统一表示根文件系统。

   - 根文件系统首先是内核启动时所 mount(挂载)的第一个文件系统，内核代码映像文件保存在根文件系统中，而系统引导启动程序会在根文件系统挂载之后从中把一些基本的初始化脚本和服务等加载到内存中去运行。

   - 嵌入式 Linux 并没有将内核代码镜像保存在根文件系统中，而是保存到了其他地方。比如 NAND Flash 的指定存储地址、EMMC 专用分区中。根文件系统是 Linux 内核启动以后挂载(mount)的第一个文件系统，然后从根文件系统中读取初始化脚本，比如 rcS，inittab 等。根文件系统和 Linux 内核是分开的，单独
     的 Linux 内核是没法正常工作的，必须要搭配根文件系统。如果不提供根文件系统，Linux 内核在启动的时候就会提示内核崩溃(Kernel panic)的提示。

   - 常用子目录

     - > ![image-20220320154101247](assets/image-20220320154101247.png)
       >
       > ![image-20220320154115510](assets/image-20220320154115510.png)
       >
       > ![image-20220320154126325](assets/image-20220320154126325.png)

2. BusyBox构建根文件系统
   1. BusyBox简介
      1. BusyBox 是一个集成了大量的 Linux 命令和工具的软件，像 ls、mv、ifconfig 等命令 BusyBox 都会提供。BusyBox 就是一个大的工具箱，这个工具箱里面集成了 Linux 的许多工具和命令。一般下载 BusyBox 的源码，然后配置 BusyBox，选择自己想要的功能，最后编译即可。BusyBox 可以在其官网下载到，官网地址为：https://busybox.net/。
   2. 编译BusyBox构建根文件系统
   3. 向根文件系统添加lib库
   4. 创建其他文件夹

3. 根文件系统初步测试

   - ```cpp
     => setenv bootargs 'console=ttymxc0,115200 root=/dev/nfs nfsroot=192.168.3.140:/home/hq/linux/nfs/rootfs,proto=tcp rw ip =192.168.3.139:192.168.3.140:192.168.3.1:255.255.255.0::eth0:off
     
     ```

   - 

4. 完善根文件系统
   1. 创建/etc/init.d/rcS文件
   2. 创建/etc/fstab文件
   3. 创建/etc/inittab文件

5. 根文件系统其他功能测试
   1. 软件运行测试
   2. 中文字符测试
   3. 开机自启动测试
   4. 外网连接测试



## 系统烧写（第三十九章）

本章我们使用 NXP 提供的 MfgTool 工具通过 USB OTG 口向开发板的 EMMC 中烧写 uboot、Linux kernel、.dtb(设备树)和 rootfs 这四个文件。

1. MfgTool工具简介
2. MfgTool工具原理简介
3. 烧写NXP官方系统
4. 烧写自制的系统
5. 改造我们自己的烧写工具
















## 开发板信息

阿尔法 - 根目录

> <img src="assets/image-20220301155923179.png" alt="image-20220301155923179" style="zoom: 50%;" />

阿尔法 - BOOT

> <img src="assets/image-20220228223345256.png" alt="image-20220228223345256" style="zoom:67%;" />

虚拟机SD卡标识

> ![image-20220228223407208](assets/image-20220228223407208.png)
>
> <img src="assets/image-20220301155812277.png" alt="image-20220301155812277" style="zoom:50%;" />













































































































































---


## 5. ALPHA I.MX应用开发笔记

## ALPHA I.MX应用开发笔记 - HQ

[TOC]

------

#### 注意

- 

------

## ALPHA I.MX应用开发学习目录

【【正点原子】I.MX6U 嵌入式 Linux C 应用编程指南 V1.3】

> ![image-20220411111811796](assets/image-20220411111811796.png)





## 重要知识点记录



















## 开发板信息

阿尔法 - 根目录

> <img src="assets/image-20220301155923179.png" alt="image-20220301155923179" style="zoom: 50%;" />

阿尔法 - BOOT

> <img src="assets/image-20220228223345256.png" alt="image-20220228223345256" style="zoom:67%;" />

虚拟机SD卡标识

> ![image-20220228223407208](assets/image-20220228223407208.png)
>
> <img src="assets/image-20220301155812277.png" alt="image-20220301155812277" style="zoom:50%;" />















































































































































---


## 5. ALPHA I.MX驱动学习笔记

## ALPHA I.MX驱动学习笔记 - HQ

[TOC]

------

#### 注意

- 

------

## ALPHA I.MX驱动学习目录

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四篇 ARM Linux驱动开发篇 P1023】

### 重点学习章节：

其他章节根据需要查阅，这里只列出博主常用的内容。

> <img src="assets/正点原子驱动推荐学习章节.png" alt="正点原子驱动推荐学习章节" style="zoom:80%;" />





## 第四十章 字符设备驱动开发

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十章 字符设备驱动开发 P1024】

1. 字符设备驱动简介

   - 字符设备是 Linux 驱动中最基本的一类设备驱动，字符设备就是一个一个字节，按照字节
     流进行读写操作的设备，读写数据是分先后顺序的。比如我们最常见的点灯、按键、IIC、SPI，
     LCD 等等都是字符设备，这些设备的驱动就叫做字符设备驱动。

   - 应用程序运行在用户空间，而 Linux 驱动属于内核的一部分，因此驱动运行于内核空间。

   - > <img src="assets/image-20220323104708923.png" alt="image-20220323104708923" style="zoom:50%;" />

   - > ![image-20220323104947745](assets/image-20220323104947745.png)

2. 字符设备驱动开发步骤

   1. 驱动模块的加载和卸载

      - Linux 驱动有两种运行方式，第一种就是将驱动编译进 Linux 内核中，这样当 Linux 内核启
        动的时候就会自动运行驱动程序。第二种就是将驱动编译成模块(Linux 下模块扩展名为.ko)，在
        Linux 内核启动以后使用“insmod”命令加载驱动模块。

      - ```cpp
        insmod drv.ko  //加载驱动模块
        modprobe drv.ko  //加载驱动模块，并能够分析模块的依赖性，检查错误，更智能，推荐使用
        
        rmmod drv,ko  //卸载驱动模块，推荐使用
        modprobe -r drv.ko  //使用 modprobe 命令可以卸载掉驱动模块所依赖的其他模块，前提是这些依赖模块已经没有被其他模块所使用，否则就不能使用 modprobe 来卸载驱动模块
        ```

   2. 字符设备注册与注销

   3. 实现设备的具体操作函数

   4. 添加LICENSE和作者信息

3. Linux设备号

   1. 设备号的组成
   2. 设备号的分配

4. chrdevbase字符设备驱动开发实验

   1. 实验程序编写
   
      - 编译的时候要保证，使用的内核文件为正确的，即，自己移植成功的或者用官方移植成功的，否则会报错
   
      - ```cpp
        1 KERNELDIR := /home/zuozhongkai/linux/IMX6ULL/linux/temp/linux-imxrel_imx_4.1.15_2.1.0_ga_alientek
        2 CURRENT_PATH := $(shell pwd)
        3 obj-m := chrdevbase.o
        4 
        5 build: kernel_modules
        6 
        7 kernel_modules:
        8 $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
        9 clean:
        10 $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
        ```
   
      - 
   
   2. 编写测试APP
   
      - `arm-linux-gnueabihf-gcc chrdevbaseApp.c -o chrdevbaseApp`
   
   3. 编译驱动程序和测试APP
   
   4. 运行测试




## 第四十一章 嵌入式Linux LED 驱动开发实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十一章 嵌入式Linux LED 驱动开发实验 P1051】

1. Linux下LED灯驱动原理

   1. 地址映射

   2. I/O内存访问函数

      - > <img src="assets/image-20220323164741235.png" alt="image-20220323164741235" style="zoom:67%;" />

2. 硬件原理图分析

3. 实验程序编写

   1. LED灯驱动程序编写
   2. 编写测试APP

4. 运行测试

   1. 编译驱动程序和测试APP
      1. 从服务器挂载（注意，是挂载，而非下载，虚拟机里面的文件更改将同步到开发板）rootfs根文件系统
         - `setenv bootargs 'console=ttymxc0,115200 root=/dev/nfs rw nfsroot=192.168.3.140:/home/hq/linux/nfs/rootfs ip=192.168.3.9:192.168.3.140:192.168.3.1:255.255.255.0::eth0:off'`
      2. 从服务器下载内核及设备树，并启动
         - `setenv bootcmd 'tftp 80800000 zImage;tftp 83000000 imx6ull-alientek-emmc.dtb;bootz 80800000 - 83000000'`
      3. 启动开发板，新建 `lib/modules/4.1.15(内核版本号)`
      4. 将led.ko和ledAPP文件复制到`lib/modules/4.1.15`文件下
      4. `depmod`   第一次加载驱动的时候需要运行此命令
      5. `insmod led.ko`  加载驱动文件    /    `modprobe led.ko`  此指令更智能
         - `lsmod`  查看当前系统中存在的模块   /    `cat /proc/devices`  查看当前系统中有没有led这个设备
      6. `mknod /dev/led c 200 0`  创建设备节点文件，
         - 驱动加载成功需要在/dev 目录下创建一个与之对应的设备节点文件，应用程序就是通过操作这个设备节点文件来完成对具体设备的操作。
      7. `./ledApp /dev/led 1`    打开led灯
      8. `rmmod led.ko`   卸载驱动模块
   2. 运行测试



## 第四十二章 新字符设备驱动实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十二章 新字符设备驱动实验 P1064】

> 字符设备驱动开发重点是使用 register_chrdev 函数注册字符设备，当不再使用设备的时候就使用
> unregister_chrdev 函数注销字符设备，驱动模块加载成功以后还需要手动使用 mknod 命令创建设备节点。register_chrdev 和 unregister_chrdev 这两个函数是老版本驱动使用的函数，现在新的字符设备驱动已经不再使用这两个函数，而是使用Linux内核推荐的新字符设备驱动API函数。本节我们就来学习一下如何编写新字符设备驱动，并且在驱动模块加载的时候自动创建设备节点文件。

1. 新字符设备驱动原理
   1. 分配和释放设备号
   2. 新的字符设备注册方法
2. 自动创建设备节点
   1. mdev机制
   2. 创建和删除类
   3. 创建设备
   4. 参考示例
3. 设置文件私有数据
4. 硬件原理图分析
5. 实验程序编写
   1. LED灯驱动程序编写
   2. 编写测试APP
6. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试



## 第四十三章 Linux设备树

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十三章 Linux设备树 P1079】

> 因为在新版本的 Linux 中，ARM 相关的驱动全部采用了设备树(也有支持老式驱动
> 的，比较少)，最新出的 CPU 其驱动开发也基本都是基于设备树的，比如 ST 新出的 STM32MP157、
> NXP 的 I.MX8 系列等。我们所使用的Linux版本为 4.1.15，其支持设备树，所以正点原子 I.MX6UALPHA 开发板的所有 Linux 驱动都是基于设备树的。

1. 什么是设备树

   - 设备树(Device Tree)，将这个词分开就是“设备”和“树”，描述设备树的文件叫做 DTS(Device 
     Tree Source)，这个 DTS 文件采用树形结构描述板级设备，也就是开发板上的设备信息，比如
     CPU 数量、 内存基地址、IIC 接口上接了哪些设备、SPI 接口上接了哪些设备等等

   - > <img src="assets/image-20220324103533234.png" alt="image-20220324103533234" style="zoom:50%;" />

2. DTS、DTB和DTC

3. DTS语法

   1. `.dtsi`头文件

   2. 设备节点

   3. 标准属性

   4. 根节点compatible属性

      - > <img src="assets/image-20220324110133966.png" alt="image-20220324110133966" style="zoom:67%;" />

   5. 向节点追加或修改内容

4. 创建小型模板设备树

5. 设备树在系统中的体现

6. 特殊节点

   1. aliases子节点
   2. chosen子节点

7. Linux内核解析DTB文件

8. 绑定信息文档

9. 设备树常用OF操作函数

   1. 查找节点的OF函数
   2. 查找父/子节点的OF函数
   3. 提取属性值的OF函数
   4. 其他常用的OF函数



## 第四十四章 设备树下的LED驱动实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十四章 设备树下的LED驱动实验 P1120】

1. 设备树LED驱动原理
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. LED灯驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试
      - 点灯成功



## 第四十五章 pinctrl和gpio子系统实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十五章 pinctrl和gpio子系统实验 P1132】

1. pinctrl子系统
   1. pinctrl子系统简介
      - 传统的配置 pin 的方式就是直接操作相应的寄存器，但是这种配置方式比较繁琐、而且容易出问题(比如 pin 功能冲突)。pinctrl 子系统就是为了解决这个问题而引入的，pinctrl 子系统主要工作内容如下：
        ①、获取设备树中 pin 信息。
        ②、根据获取到的 pin 信息来设置 pin 的复用功能
        ③、根据获取到的 pin 信息来设置 pin 的电气特性，比如上/下拉、速度、驱动能力等。
   2. IMX6ULL的pinctrl子系统驱动
   3. 设备树中添加pinctrl节点模板
2. gpio子系统
   1. gpio子系统简介
   2. IMX6ULL的gpio子系统驱动
   3. gpio子系统API函数
   4. 设备树中添加gpio节点模块
   5. 与gpio相关的OF函数
3. 硬件原理图分析
4. 实验程序编写
   1. 修改设备树文件
   2. LED灯驱动程序编写
   3. 编写测试APP
5. 运行测试
   1. 编写驱动程序和测试APP
   2. 运行测试



## 第四十七章 Linux并发与竞争

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十七章 Linux并发与竞争 P1175】

Linux是一个多任务操作系统，肯定会存在多个任务共同操作同一段内存或者设备的情况，**多个任务甚至中断都能访问的资源叫做共享资源**，就和共享单车一样。在驱动开发中要注意对共享资源的保护，也就是要处理对共享资源的并发访问。比如共享单车，大家按照谁扫谁骑走的原则来共用这个单车，如果没有这个并发访问共享单车的原则存在，只怕到时候为了一辆单车要打起来了。在 Linux 驱动编写过程中对于**并发控制**的管理非常重要，本章我们就来学习一下如何在 Linux 驱动中处理并发。

1. 并发与竞争
2. 原子操作
   1. 原子操作简介
   2. 原子整形操作API函数
   3. 原子位操作API函数
3. 自旋锁
   1. 自旋锁简介
   2. 自旋锁API函数
   3. 其他类型的锁
   4. 自旋锁使用注意事项
4. 信号量
   1. 信号量简介
   2. 信号量API函数
5. 互斥体
   1. 互斥体简介
   2. 互斥体API函数





## 第四十八章 Linux并发与竞争实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十八章 Linux并发与竞争实验 P1188】

1. 原子操作实验
   1. 实验程序编写
   2. 运行测试
2. 自旋锁实验
   1. 实验程序编写
   2. 运行测试
3. 信号量实验
   1. 实验程序编写
   2. 运行测试
4. 互斥体实验
   1. 实验程序编写
   2. 运行测试





## 第四十九章 Linux按键输入实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第四十九章 Linux按键输入实验 P1212】

在前几章我们都是使用的 GPIO 输出功能，还没有用过 GPIO 输入功能，本章我们就来学习一下如果在 Linux 下编写 GPIO 输入驱动程序。I.MX6U-ALPHA 开发板上有一个按键，我们就使用此按键来完成 GPIO 输入驱动程序，同时利用第四十七章讲的原子操作来对按键值进行保护。

1. Linux下按键驱动原理
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. 按键驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十章 Linux内核定时器实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十章 Linux内核定时器实验 P1223】

定时器是我们最常用到的功能，一般用来完成定时功能，本章我们就来学习一下 Linux 内核提供的定时器 API 函数，通过这些定时器 API 函数我们可以完成很多要求定时的应用。Linux内核也提供了短延时函数，比如微秒、纳秒、毫秒延时函数，本章我们就来学习一下这些和时间有关的功能。

1. Linux时间管理和内核定时器简介
   1. 内核时间管理简介
   2. 内核定时器简介
   3. Linux内核短延时函数
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. 定时器驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十一章 Linux中断实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十一章 Linux中断实验 P1240】

不管是裸机实验还是 Linux 下的驱动实验，中断都是频繁使用的功能，关于 I.MX6U 的中断原理已经在第十七章做了详细的讲解，在裸机中使用中断我们需要做一大堆的工作，比如配置寄存器，使能 IRQ 等等。Linux 内核提供了完善的中断框架，我们只需要申请中断，然后注册中断处理函数即可，使用非常方便，不需要一系列复杂的寄存器配置。本章我们就来学习一下如何在 Linux 下使用中断。

1. Linux中断简介
   1. Linux中断API函数
   2. 上半部与下半部
   3. 设备树中断信息节点
   4. 获取中断号
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. 按键中断驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十二章 Linux阻塞和非阻塞IO实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十二章 Linux阻塞和非阻塞IO实验 P1264】

阻塞和非阻塞 IO 是 Linux 驱动开发里面很常见的两种设备访问模式，在编写驱动的时候一定要考虑到阻塞和非阻塞。本章我们就来学习一下阻塞和非阻塞 IO，以及如何在驱动程序中处理阻塞与非阻塞，如何在驱动程序使用等待队列和 poll 机制。

1. 阻塞和非阻塞IO
   1. 阻塞和非阻塞简介
   2. 等待队列
   3. 轮询
   4. Linux驱动下的poll操作函数
2. 阻塞IO实验
   1. 硬件原理图分析
   2. 实验程序编写
   3. 运行测试
3. 非阻塞IO实验
   1. 硬件原理图分析
   2. 实验程序编写
   3. 运行测试





## 第五十三章 异步通知实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十三章 异步通知实验 P1290】

在前面使用阻塞或者非阻塞的方式来读取驱动中按键值都是应用程序主动读取的，对于非阻塞方式来说还需要应用程序通过 poll 函数不断的轮询。最好的方式就是驱动程序能主动向应用程序发出通知，报告自己可以访问，然后应用程序在从驱动程序中读取或写入数据，类似于我们在裸机例程中讲解的中断。Linux 提供了异步通知这个机制来完成此功能，本章我们就来学习一下异步通知以及如何在驱动中添加异步通知相关处理代码。

1. 异步通知
   1. 异步通知简介
   2. 驱动中的信号处理
   3. 应用程序对异步通知的处理
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. 程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十四章 platform设备驱动实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十四章 platform设备驱动实验 P1303】

我们在前面几章编写的设备驱动都非常的简单，都是对IO进行最简单的读写操作。像I2C、SPI、LCD 等这些复杂外设的驱动就不能这么去写了，Linux 系统要考虑到驱动的可重用性，因此提出了驱动的分离与分层这样的软件思路，在这个思路下诞生了我们将来最常打交道的platform 设备驱动，也叫做平台设备驱动。本章我们就来学习一下 Linux 下的驱动分离与分层，以及 platform 框架下的设备驱动该如何编写。

1. Linux驱动的分离与分层
   1. 驱动的分隔与分离
   2. 驱动的分层
2. platform平台驱动模型简介
   1. platform总线
   2. platform驱动
   3. platform设备
3. 硬件原理图分析
4. 试验程序编写
   1. platform设备与驱动程序编写
   2. 测试APP编写
5. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十五章 设备树下的platform驱动编写

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十五章 设备树下的platform驱动编写 P1330】

上一章我们详细的讲解了 Linux 下的驱动分离与分层，以及总线、设备和驱动这样的驱动框架。基于总线、设备和驱动这样的驱动框架，Linux 内核提出来 platform 这个虚拟总线，相应的也有 platform 设备和 platform 驱动。上一章我们讲解了传统的、未采用设备树的 platform 设备和驱动编写方法。最新的 Linux 内核已经支持了设备树，因此在设备树下如何编写 platform驱动就显得尤为重要，本章我们就来学习一下如何在设备树下编写 platform 驱动。

1. 设备树下的platform驱动简介
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. platform驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试





## 第五十六章 Linux自带的LED灯驱动实验 

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十六章 Linux自带的LED灯驱动实验 P1340】

前面我们都是自己编写 LED 灯驱动，其实像 LED 灯这样非常基础的设备驱动，Linux 内核已经集成了。Linux 内核的 LED 灯驱动采用 platform 框架，因此我们只需要按照要求在设备树文件中添加相应的 LED 节点即可，本章我们就来学习如何使用 Linux 内核自带的 LED 驱动来驱动 I.MX6U-ALPHA 开发板上的 LED0。

1. Linux内核自带LED驱动使能
2. Linux内核自带LED驱动简介
   1. LED灯驱动框架分析
   2. module_platform_driver函数简介
   3. gpio_led_probe函数简介
3. 设备树节点编写
4. 运行测试





## 第五十八章 Linux INPUT子系统实验 

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第五十八章 Linux INPUT子系统实验  P1360】

按键、鼠标、键盘、触摸屏等都属于输入(input)设备，Linux 内核为此专门做了一个叫做 input子系统的框架来处理输入事件。输入设备本质上还是字符设备，只是在此基础上套上了 input 框架，用户只需要负责上报输入事件，比如按键值、坐标等信息，input 核心层负责处理这些事件。本章我们就来学习一下 Linux 内核中的 input 子系统。

1. input子系统
   1. input子系统简介
   2. input驱动编写流程
   3. input_even结构体
2. 硬件原理图分析
3. 实验程序编写
   1. 修改设备树文件
   2. 按键input驱动程序编写
   3. 编写测试APP
4. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试
5. Linux自带按键驱动程序的使用
   1. 自带按键驱动程序源码简析
   2. 自带按键驱动程序的使用



## 第六十一章 Linux I2C驱动实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第六十一章 Linux I2C驱动实验 P1417】

I2C 是很常用的一个串行通信接口，用于连接各种外设、传感器等器件，在裸机篇已经对I.MX6U 的 I2C 接口做了详细的讲解。本章我们来学习一下如何在 Linux 下开发 I2C 接口器件驱动，重点是学习 Linux 下的 I2C 驱动框架，按照指定的框架去编写 I2C 设备驱动。本章同样以 I.MX6U-ALPHA 开发板上的 AP3216C 这个三合一环境光传感器为例，通过 AP3216C 讲解一下如何编写 Linux 下的 I2C 设备驱动程序。

1. Linux I2C驱动框架简介
   1. I2C总线驱动
   2. I2C设备驱动
   3. I2C设备和驱动匹配过程
2. I.MX6U的I2C适配器驱动分析
3. I2C设备驱动编写流程
   1. I2C设备信息描述
   2. I2C设备数据收发处理流程
4. 硬件原理图分析
5. 实验程序编写
   1. 修改设备树
   2. AP3216C驱动编写
   3. 编写测试APP
6. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试



## 第六十二章 Linux SPI驱动实验 

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第六十二章 Linux SPI驱动实验  P1451】

上一章我们讲解了如何编写 Linux 下的 I2C 设备驱动，SPI 也是很常用的串行通信协议，本章我们就来学习如何在 Linux 下编写 SPI 设备驱动。本章实验的最终目的就是驱动 I.MX6UALPHA 开发板上的 ICM-20608 这个 SPI 接口的六轴传感器，可以在应用程序中读取 ICM-20608的原始传感器数据。

1. Linux下SPI驱动框架简介
   1. SPI主机驱动
   2. SPI设备驱动
   3. SPI设备和驱动匹配过程
2. I.MX6U SPI主机驱动分析
3. SPI设备驱动编写流程
   1. SPI设备信息描述
   2. SPI设备数据收发处理流程
4. 硬件原理图分析
5. 实验程序编写
   1. 修改设备树
   2. 编写ICM20680驱动
   3. 编写测试APP
6. 运行测试
   1. 编译驱动程序和测试APP
   2. 运行测试



## 第七十四章 Regmap API实验 

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第七十四章 Regmap API实验 P1769】

我们在前面学习 I2C 和 SPI 驱动的时候，针对 I2C 和 SPI 设备寄存器的操作都是通过相关的 API 函数进行操作的。这样 Linux 内核中就会充斥着大量的重复、冗余代码，但是这些本质上都是对寄存器的操作，所以为了方便内核开发人员统一访问 I2C/SPI 设备的时候，为此引入了 Regmap 子系统，本章我们就来学习一下如何使用 RegmapAPI 函数来读写 I2C/SPI 设备寄存器。

1. Regmap API简介
   1. 什么是Regmap
   2. Regmap驱动框架
   3. Regmap操作函数
   4. regmap_config掩码设置
2. 实验程序编写
3. 运行测试





## 第七十五章 Linux IIO驱动实验

【【正点原子】I.MX6U嵌入式Linux驱动开发指南V1.6 - 第七十五章 Linux IIO驱动实验 P1783】

工业场合里面也有大量的模拟量和数字量之间的转换，也就是我们常说的 ADC 和 DAC。而且随着手机、物联网、工业物联网和可穿戴设备的爆发，传感器的需求只持续增强。比如手机或者手环里面的加速度计、光传感器、陀螺仪、气压计、磁力计等，这些传感器本质上都是ADC，大家注意查看这些传感器的手册，会发现他们内部都会有个 ADC，传感器对外提供 IIC或者 SPI 接口，SOC 可以通过 IIC 或者 SPI 接口来获取到传感器内部的 ADC 数值，从而得到想要测量的结果。Linux 内核为了管理这些日益增多的 ADC 类传感器，特地推出了 IIO 子系统，本章我们就来学习如何使用 IIO 子系统来编写 ADC 类传感器驱动。

1. IIO子系统简介
   1. iio_dev
   2. iio_info
   3. iio_chan_spec
2. IIO驱动框架创建
   1. 基础驱动框架建立
   2. IIO设备申请与初始化
3. 实验程序编写
   1. 使能内核IIO相关配置
   2. ICM20608的IIO驱动框架搭建
   3. 完善icm20608_read_raw函数
   4. 完善icm20608_write_raw函数
4. 测试应用程序编写
   1. linux文件流读取
   2. 编写测试APP
   3. 运行测试





## 开发板信息

阿尔法 - 根目录

> <img src="assets/image-20220301155923179.png" alt="image-20220301155923179" style="zoom: 50%;" />

阿尔法 - BOOT

> <img src="assets/image-20220228223345256.png" alt="image-20220228223345256" style="zoom:67%;" />

虚拟机SD卡标识

> ![image-20220228223407208](assets/image-20220228223407208.png)
>
> <img src="assets/image-20220301155812277.png" alt="image-20220301155812277" style="zoom:50%;" />













































































































































---
