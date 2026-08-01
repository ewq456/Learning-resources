# Linux命令速查表


## 01-Linux命令速查


> 日常开发中最常用的Linux命令，按功能分类。

---

## 📋 文件操作

```bash
ls -la              # 列出所有文件（含隐藏）
ls -lh              # 人性化显示文件大小
cd -                # 回到上一个目录
pwd                 # 显示当前路径
mkdir -p a/b/c      # 递归创建目录
rm -rf dir/         # 递归强制删除（慎用）
cp -r src/ dst/     # 递归复制
mv old new          # 移动/重命名
find . -name "*.cpp"  # 查找文件
```

## 📋 文本处理

```bash
cat file            # 查看文件
head -n 10 file     # 前10行
tail -f file        # 追踪文件末尾（日志）
grep -r "keyword" . # 递归搜索
grep -v "exclude"   # 排除匹配
sed 's/old/new/g'   # 替换文本
awk '{print $1}'    # 打印第1列
wc -l file          # 统计行数
sort file           # 排序
uniq                # 去重
```

## 📋 进程管理

```bash
ps aux              # 查看所有进程
ps -eLf             # 查看所有进程+线程
top                 # 动态进程监控
kill -9 PID         # 强制杀进程
killall 进程名       # 按名称杀进程
bg / fg             # 后台/前台切换
nohup cmd &         # 后台运行不挂断
```

## 📋 权限与用户

```bash
chmod 755 file      # rwxr-xr-x
chown user:group f  # 修改所有者
chgrp group file    # 修改所属组
sudo cmd            # 以root执行
su - user           # 切换用户
```

## 📋 网络

```bash
ping host           # 测试连通性
netstat -tlnp       # 查看监听端口
ss -tlnp            # 同上（更快）
ifconfig            # 网络接口信息
ip addr             # 同上（新版）
curl url            # HTTP请求
wget url            # 下载文件
scp file user@host:path  # 远程拷贝
```

## 📋 磁盘与内存

```bash
df -h               # 磁盘使用情况
du -sh dir/         # 目录大小
free -h             # 内存使用情况
mount / umount      # 挂载/卸载
```

## 📋 压缩与归档

```bash
tar -czf dst.tar.gz src/     # 打包压缩
tar -xzf src.tar.gz          # 解压缩
zip -r dst.zip src/          # zip压缩
unzip src.zip                # zip解压
```

## 📋 系统信息

```bash
uname -a            # 系统信息
cat /etc/os-release # 发行版信息
lscpu               # CPU信息
lsmem               # 内存信息
dmesg               # 内核日志
journalctl -xe      # systemd日志
```


---
