# Markdown语法参考


## Markdown语法

## Markdown语法 - HQ

[TOC]

------

#### 注意

- 

------

### 超链接

#### 常规链接

```text
[描述](链接地址) ，例如1：[知乎](http://www.zhihu.com)，注意要使用英文符号
```

#### 绝对路径

打开H盘的mao文件夹：

```text
     例如2：[猫](file:///H:/mao)，注意要使用英文符号
```

打开H盘的mao文件夹里的va.mp4：

```text
     例如3：[猫](file:///H:/mao/va.mp4)，注意要使用英文符号
```

```cpp
> *引用: Readme4（原文链接: /User/root/Docs/Readme1.md）*
> *引用: Readme4（原文链接: C:/Develop/Docs/Readme1.md）*
> *引用: Readme4（原文链接: file:///User/root/Docs/Readme1.md）*
> *引用: 使用绝对路径链接到本地文件（原文链接: file:///Users/luomingyang/Desktop/link.md）*
```

#### 相对路径

我要在README.md引用其它的文件，则写法如下：

```text
[Readme2](../Docs/Readme2.markdown)
> *引用: 使用相对路径链接到本地文件（原文链接: ./link.md）*
[日刷leetcode（第三周）](../Users/Documents/日刷leetcode.md )
```

#### 其他例子

```python3
> *引用: Readme1（原文链接: Readme1.md）*

[Readme3](Readme3)
```

> 对于相对链接地址，根据Markdown的规范导出为HTML时，它不会转换为真正的绝对文件路径。































































































































































---
