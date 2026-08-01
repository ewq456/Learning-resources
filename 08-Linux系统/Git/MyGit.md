## git 基本命令的使用
### 从 git 上 clone 一个项目仓库到本地
```bash
git clone https://192.168.6.160/zjaq_products/edp_group/edp_linux/edplinuxclient.git
```

```bash
git clone --depth 1 --branch main https://yuxiuyu:12345.com@192.168.6.160/zjaq_products/edp_group/edp_linux/edplinuxclient.git
```

### 切换分支
```bash
git checkout 分支名称
```

### 查看项目中的所有分支
```bash
git branch -a
```

### 更新分支代码
```bash
git pull
```

### 将代码文件或更新的文件添加暂存区
```bash
git add 代码文件
git add 目录名	-- 会将目录下的所有文件提交到暂存区
```

### 提交代码--只是暂时提交到本地仓库中
```bash
git commit -m 描述信息-- git commit -m "解决操作系统账户添加用户不上报审计问题"
```

### 提交代码到远程仓库
```bash
git push
```

### 查看当前所在分支和当前分支下的文件是否有更改
```bash
git status
```

### 查看系统config
```bash
git config --system --list
```

### 查看当前用户（global）配置
```cpp
git config --global --list
```

### git 保存密码
```cpp
git config --global credential.helper store
```

## git 常见命令
```bash
$ workspace：       # 工作区
$ staging area：    # 暂存区/缓存区
$ local repository：# 版本库或本地仓库
$ remote repository：# 远程仓库
```

### git help
```bash
$ git help <verb>  
$ git <verb> --help  
$ man git-<verb>  

# 查看 config 帮助手册
$ git help config
$ git config --help 
$ git git-config
```

### git config
```bash
# 设置提交代码时的用户信息
# 如果你希望在一个特定的项目中使用不同的名称或 e-mail 地址，你可以在该项目中运行该命令而不要 --global 选项
$ git config --global user.name "ewq456"  
$ git config --global user.email 2441542303@qq.com

# 列出配置文件中设置的所有变量及其值
$ git config -l 

# 查看特定关键字
$ git config <key>
$ git config user.name 
```

### git init
```bash
$ git init
```

### git clone 
```bash
# 从 url 远程拉取到本地目录 -- 空目录
$ git clone <url> [directory]

# 将历史记录截断为指定的提交次数, 检出一个分支, 分支名为 main
$ git clone --depth 1 --branch main <url> [directory]
```

### git add
```bash
# 跟踪所有改动过的文件
$ git add 

# 跟踪指定文件
$ git add <file>

# 添加所有修改文件（包括新文件/修改文件/删除文件）
$ git add -A
```

### git mv 
```bash
$ git mv <old file> <new file>
```

### git revert
```bash
$ git revert <commit_id>
```

### git reset
```bash
# --mixed 为默认，可以不用带该参数, 重置暂存区的文件与上一次的提交(commit)保持一致，工作区文件内容保持不变
############################# 撤销 commit，并且撤销 git add . 操作 #################################
$ git reset --mixed [HEAD]

# 实例
$ git reset HEAD^            # 回退所有内容到上一个版本  
$ git reset HEAD^ hello.php  # 暂存区文件 回退 hello.php 文件的版本到上一个版本 ,工作区不变化，与 git rm --cached 区别是工作区不变
$ git reset 052e             # 回退到指定版本

$ git reset HEAD^ # 撤消上一次的commit 不带参数默认是--mixed 例：git reset --mixed HEAD^  也可以写成git reset HEAD~1
$ git reset HEAD~2 # 如果你进行了2次commit，想都撤回，可以使用HEAD~2
$ git reset fdaeaf208f0e142ceba5766d17786d60fcebc1dd # 撤消至指定的commitId

--mixed（默认）：不删除工作空间改动代码，<< 撤销 commit，并且撤销 git add . 操作 >> ，重置位置的同时，只保留Working Tree工作目录的內容，但会将 Index暂存区 和 Repository 中的內容更改和reset目标节点一致，因此原节点和Reset节点之间的【差异变更集】会放入Working Tree工作目录中。所以效果看起来就是原节点和Reset节点之间的所有差异都会放到工作目录中。

----------------------------------------------------------------------------------------------------------------------

# --soft 参数用于回退到某个版本
############################# 撤销 commit，不撤销 git add . 操作 ##################################
$ git reset --soft HEAD

# 实例
$ git reset --soft HEAD~3   # 回退上上上一个版本 

--soft：不删除工作空间改动代码，<< 撤销 commit，不撤销 git add . 操作 >>，重置位置的同时，保留 working Tree 工作目录和 index 暂存区的内容，只让repository中的内容和 reset 目标节点保持一致，因此原节点和reset节点之间的【差异变更集】会放入index暂存区中(Staged files)。所以效果看起来就是工作目录的内容不变，暂存区原有的内容也不变，只是原节点和Reset节点之间的所有差异都会放到暂存区中。

----------------------------------------------------------------------------------------------------------------------

# --hard 参数撤销工作区中所有未提交的修改内容，将暂存区与工作区都回到上一次版本，并删除之前的所有信息提交
###################################### 清空暂存区和工作区 ########################################
$ git reset --hard HEAD

# 实例
$ git reset --hard HEAD~3           # 回退上上上一个版本  
$ git reset –hard fdaeaf208f0e1     # 回退到某个版本回退点之前的所有信息。 
$ git reset --hard origin/master    # 将本地的状态回退到和远程的一样 

# 注意：谨慎使用 –-hard 参数，它会删除回退点之前的所有信息。
# HEAD 说明：
# HEAD 表示当前版本
# HEAD^ 上一个版本
# HEAD^^ 上上一个版本
# HEAD^^^ 上上上一个版本
# 以此类推...

# 可以使用 ～数字 表示
# HEAD~0 表示当前版本
# HEAD~1 上一个版本
# HEAD^2 上上一个版本
# HEAD^3 上上上一个版本
# 以此类推...

--hard：删除工作空间改动代码，撤销commit，撤销git add . 操作，重置位置的同时，直接将 working Tree工作目录、 index 暂存区及 repository 都重置成目标Reset节点的內容,所以效果看起来等同于清空暂存区和工作区。
注意完成这个操作后，就恢复到了指定版本的commit状态。
----------------------------------------------------------------------------------------------------------------------
```

### git rm
```bash
# 删除文件
$ git rm <file>

# 强制删除
$ git rm -f <file>

# 从暂存区移出 保留在工作目录中
$ git rm --cached <file>
```

### git diff
```bash
# 查看工作区和暂存区之间的文件差异
$ git diff 文件名

# 工作区和版本库之间的文件差异
$ git diff HEAD 文件名

# 暂存区和版本库
$ git diff --cached 文件名

# 不同版本之间的文件差异
$ git diff 版本号1 版本号2 文件名
```

### git grep 
```bash
$ git grep <arg>

# 实例
# 查看这个仓库里每个使用'xmmap'函数的地方
$ git grep xmmap

# 显示行号
$ git grep -n xmmap

# 显示文件名
$ git grep --name-only xmmap

# 每一个文件里有多少行匹配内容
$ git grep -c xmmap

# 查找git仓库里某个特定版本里的内容
$ git grep xmmap v1.5.0   # 标签名(tag reference)

# 组合搜索
# 查找我们在仓库的哪个地方定义了'SORT_DIRENT'
$ git grep -e '#define' --and -e SORT_DIRENT

# 进行“与"(both)条件搜索操作，也可以进行"或"(either)条件搜索操作
$ git grep --all-match -e '#define' -e SORT_DIRENT

# 我们要找出名字中含有‘PATH'或是'MAX'的常量定义
$ git grep -e '#define' --and \( -e PATH -e MAX \) 
```

### git log
```bash
# 查看提交历史
$ git log

# 查看指定文件的提交历史
$ git log -p <file>

# 限制显示的提交数:
$ git log -n <number>

# 显示最近的 5 次提交：
$ git log -n 5

# 显示自指定日期之后的提交：
$ git log --since="2024-01-01"

# 显示指定日期之前的提交：
$ git log --until="2024-07-01"

# 只显示某个作者的提交：
$ git log --author="Author Name"

# 查看对版本库进行的所有操作获取哈希值
$ git reflog

$ git log [选项] [分支名/提交哈希]
$ -p：显示提交的补丁（具体更改内容）。
$ --oneline：以简洁的一行格式显示提交信息。
$ --graph：以图形化方式显示分支和合并历史。
$ --decorate：显示分支和标签指向的提交。
$ --author=<作者>：只显示特定作者的提交。
$ --since=<时间>：只显示指定时间之后的提交。
$ --until=<时间>：只显示指定时间之前的提交。
$ --grep=<模式>：只显示包含指定模式的提交消息。
$ --no-merges：不显示合并提交。
$ --stat：显示简略统计信息，包括修改的文件和行数。
$ --abbrev-commit：使用短提交哈希值。
$ --pretty=<格式>：使用自定义的提交信息显示格式。
```

### git show
```bash
# 显示提交的详细信息，包括提交消息、作者、日期和更改的文件等：
$ git show <commit-hash>
$ git show 9a0d7b6

# 仅显示提交中包含的差异（补丁）：
$ git show --patch <commit-hash>
$ git show --patch 9a0d7b6

# 显示提交的文件列表
$ git show --name-only <commit-hash>
$ git show --name-only 9a0d7b6

# 显示提交的统计信息，包括更改的文件和行数：
$ git show --stat <commit-hash>

$ git show --stat 9a0d7b6

# 使用自定义格式显示提交信息
# 使用 --pretty=format: 自定义提交信息的输出格式：
$ git show --pretty=format:"%h - %an, %ar : %s" <commit-hash>
$ git show --pretty=format:"%h - %an, %ar : %s" 9a0d7b6

# 显示标签的详细信息
$ git show <tag>
$ git show v1.0
```

### git status
```bash
$ git status

# 简短输出
$ git status -s

# 显示分支信息
$ git status -b

# 显示未跟踪文件
$ git status -u

# 显示变更的文本文件
$ git status -v
```

### git branch
```bash
# 查看分支
$ git branch

# 查看远程分支
$ git branch -r

# 查看所有远程和本地分支
$ git branch -a

# 删除本地分支
$ git branch -d <branchname>

# 强制删除未合并的分支
$ git branch -D <branchname>

# 删除远程分支
$ git push origin --delete <branchname>
```

### git checkout 
```bash
# 切换分支
$ git checkout <branchname>

# 创建新分支并切换
$ git checkout -b <new-branch-name>

# 切换到前一个分支
$ git checkout -

# 检出文件，将当前文件恢复至最近一次提交的状态，丢弃所有未提交的更改
$ git checkout -- <file>

# 切换到标签
$ git checkout tags/<tag-name>
```

### git commit 
```bash
# 提交所有更新过的文件
$ git commit -m "commit message"

# 提交暂存文件至指定的仓库
$ git commit [file1] [file2] ... -m [message]

# 修改最近一次提交信息 相当于vim直接修改提交信息
$ git commit --amend
```

### 解决分支冲突
```bash
# 如果你暂时不想提交当前更改/或者与远程有冲突，可以使用 git stash 命令将本地更改暂存起来，避免被覆盖。执行以下命令：
$ git stash

# 将远程最新仓库文件拉取到本地
$ git pull

# 查看stash的文件
$ git stash list

# 将之前保存的文件合并到最新文件当中
$ git stash apply

# 将冲突的部分进行修改
# <<<<<<<<<<<
$ 本地文件
# ===========
$ 远程文件
# >>>>>>>>>>>

# 再次进行 暂存 提交 推送 操作
$ add 
$ commit 
$ push

# 一旦你应用了 stash 中的更改，并且确定不再需要这个 stash 了，可以使用以下命令来删除 stash
$ git stash drop
```

### git merge
```bash
# 合并分支
$ git merge <branchname>

# 将 dev 合并至 master
$ git checkout master
$ git merge dev

# 解决冲突
$ git status 
# 手动解决冲突后
$ git add <file>
$ git commit -m "resolved conflict"
```

### git tag
```bash
# -a 选项可以添加注解
$ git tag -a v1.0 

# 查看所有标签
$ gig tag 

# 推送标签到远程仓库, 认情况下，git push 不会推送标签，你需要显式地推送标签
$ git push origin <tagname>

# 删除本地标签
$ git tag -d <tagname>

# 删除远程标签
$ git push origin --delete <tagname>
```

### git remote
```bash
# 查看远程仓库
$ git remote

# 删除远程仓库
$ git remote rm <alias>

# 列出当前仓库中已配置的远程仓库，并显示它们的 URL
$ git remote -v

# 查看指定远程版本库信息
$ git remote show <remote>

# 添加一个新的远程仓库
$ git remote add <remote_name> <remote_url>

# 将已配置的远程仓库重命名
$ git remote rename <old_name> <new_name>

# 从当前仓库中删除指定的远程仓库
$ git remote remove <remote_name>
```

### git fetch
```bash
# 提取远程仓库的数据
$ git fetch <alias>
```

### git pull
```bash
$ git pull [远程仓库名] [分支名]

$ git pull
$ git pull origin

# 将远程主机 origin 的 master 分支拉取过来，与本地的 brantest 分支合并
$ git pull origin master:brantest

# 如果远程分支是与当前分支合并，则冒号后面的部分可以省略
$ git pull origin master
```

### git push
```bash
$ git push <alias> <branch>
```

### 本地生成密钥
```bash
$ ssh-keygen -t rsa -C "youremail.com"
```

