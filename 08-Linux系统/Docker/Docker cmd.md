## 常用命令总结
### docker 命令列表
| `<font style="color:rgb(51, 51, 51);">docker run</font>` | <font style="color:rgb(51, 51, 51);">启动一个新的容器并运行命令</font><br/><font style="color:rgb(51, 51, 51);">保证 docker 一直运行，-i 保持输入打开，-t 分配伪终端，-d 后台运行</font> | `<font style="color:rgb(51, 51, 51);">docker run -d ubuntu</font>`<br/>`<font style="color:rgb(51, 51, 51);">docker run -itd --name 容器名 镜像:版本 /bin/bash</font>` |
| --- | --- | --- |
| `<font style="color:rgb(51, 51, 51);">docker ps</font>` | <font style="color:rgb(51, 51, 51);">列出当前正在运行的容器</font> | `<font style="color:rgb(51, 51, 51);">docker ps</font>` |
| `<font style="color:rgb(51, 51, 51);">docker ps -a</font>` | <font style="color:rgb(51, 51, 51);">列出所有容器（包括已停止的容器）</font> | `<font style="color:rgb(51, 51, 51);">docker ps -a</font>` |
| `<font style="color:rgb(51, 51, 51);">docker build</font>` | <font style="color:rgb(51, 51, 51);">使用 Dockerfile 构建镜像</font> | `<font style="color:rgb(51, 51, 51);">docker build -t my-image .</font>` |
| `<font style="color:rgb(51, 51, 51);">docker images</font>` | <font style="color:rgb(51, 51, 51);">列出本地存储的所有镜像</font> | `<font style="color:rgb(51, 51, 51);">docker images</font>` |
| `<font style="color:rgb(51, 51, 51);">docker pull</font>` | <font style="color:rgb(51, 51, 51);">从 Docker 仓库拉取镜像</font> | `<font style="color:rgb(51, 51, 51);">docker pull ubuntu</font>` |
| `<font style="color:rgb(51, 51, 51);">docker push</font>` | <font style="color:rgb(51, 51, 51);">将镜像推送到 Docker 仓库</font> | `<font style="color:rgb(51, 51, 51);">docker push my-image</font>` |
| `<font style="color:rgb(51, 51, 51);">docker exec</font>` | <font style="color:rgb(51, 51, 51);">在运行的容器中执行命令</font> | `<font style="color:rgb(51, 51, 51);">docker exec -it container_name bash</font>` |
| `<font style="color:rgb(51, 51, 51);">docker stop</font>` | <font style="color:rgb(51, 51, 51);">停止一个或多个容器</font> | `<font style="color:rgb(51, 51, 51);">docker stop container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker start</font>` | <font style="color:rgb(51, 51, 51);">启动已停止的容器</font> | `<font style="color:rgb(51, 51, 51);">docker start container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker restart</font>` | <font style="color:rgb(51, 51, 51);">重启一个容器</font> | `<font style="color:rgb(51, 51, 51);">docker restart container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker rm</font>` | <font style="color:rgb(51, 51, 51);">删除一个或多个容器</font> | `<font style="color:rgb(51, 51, 51);">docker rm container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker rmi</font>` | <font style="color:rgb(51, 51, 51);">删除一个或多个镜像</font> | `<font style="color:rgb(51, 51, 51);">docker rmi my-image</font>` |
| `<font style="color:rgb(51, 51, 51);">docker logs</font>` | <font style="color:rgb(51, 51, 51);">查看容器的日志</font> | `<font style="color:rgb(51, 51, 51);">docker logs container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker inspect</font>` | <font style="color:rgb(51, 51, 51);">获取容器或镜像的详细信息</font> | `<font style="color:rgb(51, 51, 51);">docker inspect container_name</font>` |
| `<font style="color:rgb(51, 51, 51);">docker exec -it</font>` | <font style="color:rgb(51, 51, 51);">进入容器的交互式终端</font><br/><font style="color:rgb(51, 51, 51);">直接进入 root 目录（指定进入容器后的工作目录）</font> | `<font style="color:rgb(51, 51, 51);">docker exec -it container_name /bin/bash</font>`<br/>`<font style="color:rgb(51, 51, 51);">docker exec -it -w  /root container_name /bin/bash</font>` |
| `<font style="color:rgb(51, 51, 51);">docker network ls</font>` | <font style="color:rgb(51, 51, 51);">列出所有 Docker 网络</font> | `<font style="color:rgb(51, 51, 51);">docker network ls</font>` |
| `<font style="color:rgb(51, 51, 51);">docker volume ls</font>` | <font style="color:rgb(51, 51, 51);">列出所有 Docker 卷</font> | `<font style="color:rgb(51, 51, 51);">docker volume ls</font>` |
| `<font style="color:rgb(51, 51, 51);">docker-compose up</font>` | <font style="color:rgb(51, 51, 51);">启动多容器应用（从</font><font style="color:rgb(51, 51, 51);"> </font>`<font style="color:rgb(51, 51, 51);">docker-compose.yml</font>`<br/><font style="color:rgb(51, 51, 51);"> </font><font style="color:rgb(51, 51, 51);">文件）</font> | `<font style="color:rgb(51, 51, 51);">docker-compose up</font>` |
| `<font style="color:rgb(51, 51, 51);">docker-compose down</font>` | <font style="color:rgb(51, 51, 51);">停止并删除由</font><font style="color:rgb(51, 51, 51);"> </font>`<font style="color:rgb(51, 51, 51);">docker-compose</font>`<br/><font style="color:rgb(51, 51, 51);"> </font><font style="color:rgb(51, 51, 51);">启动的容器、网络等</font> | `<font style="color:rgb(51, 51, 51);">docker-compose down</font>` |
| `<font style="color:rgb(51, 51, 51);">docker info</font>` | <font style="color:rgb(51, 51, 51);">显示 Docker 系统的详细信息</font> | `<font style="color:rgb(51, 51, 51);">docker info</font>` |
| `<font style="color:rgb(51, 51, 51);">docker version</font>` | <font style="color:rgb(51, 51, 51);">显示 Docker 客户端和守护进程的版本信息</font> | `<font style="color:rgb(51, 51, 51);">docker version</font>` |
| `<font style="color:rgb(51, 51, 51);">docker stats</font>` | <font style="color:rgb(51, 51, 51);">显示容器的实时资源使用情况</font> | `<font style="color:rgb(51, 51, 51);">docker stats</font>` |
| `<font style="color:rgb(51, 51, 51);">docker login</font>` | <font style="color:rgb(51, 51, 51);">登录 Docker 仓库</font> | `<font style="color:rgb(51, 51, 51);">docker login</font>` |
| `<font style="color:rgb(51, 51, 51);">docker logout</font>` | <font style="color:rgb(51, 51, 51);">登出 Docker 仓库</font> | `<font style="color:rgb(51, 51, 51);">docker logout</font>` |


### 启动临时容器
```dockerfile
docker run -it --name <name> <image>
```

### 在运行中的容器执行命令
```dockerfile
docker exec -it <container> <command> 
```

### 保存容器为镜像
```dockerfile
docker commit <container> <new-image> 
```

### 查看容器文件变更
```dockerfile
docker diff <container>
```

### 查看镜像列表
```dockerfile
docker images
```

### 添加镜像标签
```dockerfile
docker tag <image> <new-tag>
```

### 推送镜像到仓库
```dockerfile
docker push <image> 
```

## Docker 概念
:::info
**Docker 是一种容器技术，是解决软件跨环境迁移问题**

:::

    - Docker 是一个开源的应用容器引擎
    - 基于 Go 语言实现
    - Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中,然后发布到任何流行的 Linux 机器上
    - 容器是完全使用沙箱机制，相互隔离
    - 容器性能开销极低

## Docker 架构
#### 镜像（image）：
        * Docker 镜像（image）就相当于是一个 root 文件系统
        * 比如官方镜像 Ubuntu 16.04 就包含了一个完整的一套 Ubuntu 16.04 最小系统的 root 文件系统

#### 容器 （container）:
        * 镜像（image）和容器（container）的关系，就像是面向对象程序设计中的类和对象的一样
        * 镜像是静态的定义，容器是镜像运行时的实体
        * 容器可以被创建、启动、停止、暂停、删除等

#### 仓库（Repository）：
仓库可看成一个代码控制中心，用来保存镜像

## 配置镜像加速器
## Docker 镜像相关命令
+ 查看镜像
    - 
+ 搜索镜像
+ 拉取镜像
+ 删除镜像

