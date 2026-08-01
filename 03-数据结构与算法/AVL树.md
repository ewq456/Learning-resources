# AVL平衡树


## 从零开始学习数据结构_AVL树之旋转算法

- [一、AVL树](#一avl树)
- [二、四种旋转](#二四种旋转)
  - [2.1 单旋转 --> 直线型](#21-单旋转----直线型)
  - [2.2 双旋转 --> 折线型](#22-双旋转----折线型)
- [三、画平衡树](#三画平衡树)
- [四、四种旋转的实现](#四四种旋转的实现)
  - [4.1 右单旋](#41-右单旋)
  - [4.2 左单旋](#42-左单旋)
  - [4.3 先左后右单旋](#43-先左后右单旋)
  - [4.4 先右后左单旋](#44-先右后左单旋)
- [五、说明](#五说明)

AVL（平衡二叉查找树），其新增/删除核心思路：通过树旋转算法来进行树的平衡，提高查找效率。

## 一、AVL树

AVL树首先是一颗二叉搜索树，满足其所有性质，AVL树又叫做高度平衡的二叉搜索树；

AVL: 动态搜索树；

平衡因子bf: 右树高度 — 左树高度; bf的取值只能是1, 0, -1；

左右子树都得符合平衡因子, 若不符, 的通过旋转来调整平衡因子。

## 二、四种旋转

### 2.1 单旋转 --> 直线型

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjMDMg3xOXUA2Z4h3aKw9iciaUWErPt0XcLZ4b0ClMS3ece4DzZyozAqibA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

### 2.2 双旋转 --> 折线型

**要进行两次旋转的调整，判断折线，看哪边突出(就是三个结点中有一个突出的方向)，就先向哪边旋转。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjcR42J990QNeAD4boaTfbNPsMY1MNmibgibt16OcveHxED5dZ5QXRVCkw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

**四种旋转，每次就只针对两个结点(要进行旋转的2个结点)；然后将上面的分支挂到旋转后的L/R上即可。**

## 三、画平衡树

根据一组数字，画出其AVL树：16 3 7 11 9 26 18 14 15。

**画AVL树，首先其实是一颗搜索二叉树; 按照其比左孩子大，比右孩子小画就行; 有了平衡因子，不满足时在旋转调整即可。**

画法三步走：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjGYsTSZKNzibbUFibRFUVa97ibSsJ5vVl4t8uiaCfAyVZSicZ3OzLiasNKiatg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(第一步)</p>
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjwWUEouiau0VzZfYAFlM9ZJiankAYqXMUq70gEHY2azxWpwoWuupuCiaYQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(第二步)</p>
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjlfmyENz159GngI3yfFQUSy4647MDwKD0eXkqicpqiasQcad9fiaGMCXuA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(第三步)</p>

## 四、四种旋转的实现

**永远只考虑三层以内结点的旋转。**

C++实现其所有代码。

### 4.1 右单旋

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjRtFEFuWnb5NnaXMVXk1gOTzdqkk3MTh917VHb3dPq3ictq2jJstAdTw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

代码如下(**代码中 ptr 代表的是要 bf 不为平衡处，指向要进行旋转的结点**)：

```cpp
void RotateR(AVLNode<Type> *&ptr){
    AVLNode<Type> *subR = ptr;
    ptr = ptr->leftChild;  //通过引用直接修改指向1的指针(可能是上一个的左孩子/右孩子)
    subR->leftChild = ptr->rightChild;
    ptr->rightChild = subR;
    ptr->bf = subR->bf = 0;
}
```

### 4.2 左单旋

左单旋与右单旋的代码是镜像的，并且想法是一致的; 所以代码如下：

```cpp
void RotateL(AVLNode<Type> *&ptr){
    AVLNode<Type> *subL = ptr;
    ptr = subL->rightChild;  //同样是经过引用修改
    subL->rightChild = ptr->leftChild;
    ptr->leftChild = subL;
    subL->bf = ptr->bf = 0;
}
```

**在进行单旋转时，因为是在插入，其自身的 bf 不用调整，初始化为0;修改的是根和另一个结点的 bf。**

### 4.3 先左后右单旋

**在进行双旋转时，首先明确左/右孩子，根结点的最终情况, 在进行调整;并且在双旋转时每个结点的bf都得改变。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjZzU9AHgIx6Sh1rYjVvjKPBy2njydNHUPE9HOxPPvFBBn1bFLRUk3iag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

平衡因子在这不好考虑，有点复杂，具体分析如下：

**平衡因子的考虑关键在：ptr 有左树/右树，对应上去则 subL/sunR 原先必有一个分支结点; ptr 没有孩子结点，对应 subR/subL原先也没有分支结点。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXj6yqEtwMTGIaZVYrbegZW5AcZg8Cf6ukunZKJDUNRvgwbGRiczfFHsZQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(第一种情况)</p>
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQIp2yMxltM0oFHibFI34ibXjKKTw6GQt3ic2uMwRN5Q5xbnjSVCyfG1kveNMPK6LoVicQRN0Dic9SKMjg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(第二种情况)</p>

代码如下：

```cpp
void RotateLR(AVLNode<Type> *&ptr){
    AVLNode<Type> *subR = ptr;    //最终右孩子
    AVLNode<Type> *subL = ptr->leftChild; //最终左孩子
    ptr = subL->rightChild;  //最终根节点,因为引用,最终这个修改了指向根结点，完成了连接;

    subL->rightChild = ptr->leftChild;
    ptr->leftChild = subL;
    if(ptr->bf <= 0){
        subL->bf = 0;  //此时的情况就是,自己ptr原先没有挂结点或者是左树挂上结点，而满足这种情况下，sunL原先必有左树，此时在挂上右树，所以为0;
    }else{
        subL->bf = -1;  //此时的情况是ptr有右孩子，而sunL有左孩子，满足这种情况，所以bf只能是-1;
    }

    subR->leftChild = ptr->rightChild;
    ptr->rightChild = subR;
    if(ptr->bf == -1){  //当结点ptr其只有左孩子时，
        subR->bf = 1;  //sunR必定有右孩子,所以此时为1
    }else{
        subR->bf = 0; //当ptr没有孩子结点或有一个右孩子时(此时subR必有右树)，所以此时为0;
    }

    ptr->bf = 0;   //调整后根的bf永远是0;
}
```

### 4.4 先右后左单旋

与上一个双旋的代码是镜像的, 并且想法是一致的; **平衡因子的修改有点不一样，注意一下就行**，所以代码如下:

```cpp
void RotateRL(AVLNode<Type> *&ptr){
    AVLNode<Type> *subL = ptr;
    AVLNode<Type> *subR = ptr->rightChild;
    ptr = subR->leftChild;

    subR->leftChild = ptr->rightChild;
    ptr->rightChild = subR;
    if(ptr->bf >=0){
        subR->bf = 0;
    }else{
        subR->bf = 1;
    }

    subL->rightChild = ptr->leftChild;
    ptr->leftChild = subL;
    if(ptr->bf == 1){
        subL->bf = -1;
    }else{
        subL->bf = 0;
    }

    ptr->bf = 0;
}
```

## 五、说明

原创文章链接：[从零开始学习数据结构-->AVL树之旋转算法](https://mp.weixin.qq.com/s?__biz=MzU4MjQ3NzEyNA==&mid=2247485402&idx=1&sn=a2590144c7cc6f10008056f4ddd0a94f&chksm=fdb6f3f1cac17ae7a1ea1967820f730b3b5edb5465585e308e91f25b59ad611fe1725f452a1a&token=1129091266&lang=zh_CN#rd)


---


## 从零开始学习数据结构_AVL树之插入算法

- [一、AVL树的插入](#一avl树的插入)
- [二、AVL树的插入算法](#二avl树的插入算法)
- [三、完整代码+测试代码+运行结果](#三完整代码测试代码运行结果)
  - [3.1 完整代码](#31-完整代码)
  - [3.2 测试代码](#32-测试代码)
  - [3.3 测试结果](#33-测试结果)
- [四、说明](#四说明)

## 一、AVL树的插入

1. 必须追踪插入路径，要对bf进行调整，此时不能用递归；
2. 用栈保留路径信息，每次插入均是以叶子结点插入的;
3. **插入一个新结点，自身的 bf 不用调整，其初始化为 0；要调整的是栈中的平衡因子，关键在双旋时，平衡因子的调整要小心，还是调整栈中结点的平衡因子。**

## 二、AVL树的插入算法

思路：

1. 按照二叉搜索树的非递归实现插入数据；
2. 有一个父节点，记录信息，并且入栈；
3. 栈非空，出栈，判断插入是左/右，此时给栈顶的结点平衡因子++/--；
4. 判断bf的值，进行不同情况的处理，针对bf不满足平衡，将根据情况调用4个旋转函数进行调整；
5. 最后实行连接工作，看栈，空的话，直接给root，否则读栈顶，比较数据大小，连接在左/右孩子。

**代码均由 C++ 实现，要记住的是：栈中只保存的是插入结点的路径，其余结点的信息不在保存。**

如何判断写出要用4个旋转函数，并且此时情形如何？

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQADAAicS3iamhwXyDIBc1icF5c3eGUboDuOm73TTwDTJib4nmaby2TSmAjv6eKib3qek6ibBiaNQUSyHtow/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

以上仅仅是一种情况，但是 parent 和 p 的指向我们已经理解了，其他的情形就可以看出来了。

代码如下：

```cpp
template<typename Type>
bool AVLTree<Type>::insert(AVLNode<Type> *&t, const Type &x){
    AVLNode<Type> *p = t;
    AVLNode<Type> *parent = NULL; // 记录前驱结点，方便连接和调整平衡因子
    stack<AVLNode<Type> *> st; //用栈记录插入的路径，方便调整栈中结点的平衡因子;
    int sign;

    while(p != NULL){
        if(x == p->data){ //要插入的数据和AVL树中的数字相同,则返回失败！
            return false;
        }

        parent = p;
        st.push(parent); //找过的入栈
        if(x < p->data){
            p = p->leftChild;
        }else if(x > p->data){
            p = p->rightChild;
        }
    } // 找插入位置,不用递归，就是为了记录路径信息
    
    p = new AVLNode<Type>(x);
    if(parent == NULL){
        t = p;    //判断是不是第一个结点，进行root的连接;
        return true;
    }

    if(x < parent->data){ //此时通过父节点的数据判断插入的是左还是右
        parent->leftChild = p;
    }else{
        parent->rightChild = p;
    }
    //新插入点的bf为0,关键是栈中的平衡因子的调整
/////////////////////////////////////////////////////// 以上完成插入工作
    while(!st.empty()){  //栈不空，出栈顶元素
        parent = st.top();
        st.pop();

        if(p == parent->leftChild){   //判断插入的是父节点的左/右孩子,
            parent->bf--;           //让其bf++/--;
        }else{
            parent->bf++;
        }

        //以下判断栈中的平衡因子，看是否需要进行旋转调整
        if(parent->bf == 0){  //bf=0，直接跳出循环
            break;
        }
        if(parent->bf==1 || parent->bf==-1){ 
            p = parent;  //此时在向上走，判断bf;
        }else{  //以下的bf为2/-2;利用标志判断左右旋;
            sign = parent->bf > 0 ? 1 : -1;
            if(p->bf == sign){  //符号相同为单旋
                if(sign == 1){  //为1左旋
                    RotateL(parent);  
                }else{
                    RotateR(parent); //右旋
                }
            }else{  //符号不同，为双旋
                if(sign == 1){  
                    RotateRL(parent); //为1右左
                }else{
                    RotateLR(parent);
                }
            }
/*
    以下方法也可以判断左右旋
        else
        {
            if(parent->bf < 0)  //左边
            {
                if(p->bf<0 && p==parent->leftChild)    //    / 只能是左孩子
                {
                    //RotateR(parent);
                }
                else if(p->bf>0 && p == parent->leftChild)  //   <
                {
                    //RotateLR(parent);
                }
            }
            else
            {
                if(p->bf>0 && p==parent->rightChild)   //   \ 
                {
                    //RotateL(parent);
                }
                else if(p->pf<0 && p==parent->rightChild)  //      >
                {
                    //RotateRL(parent);
                }
            }
        }

*/
    break;
        }
    }

    if(st.empty()){  //通过旋转函数，此时parent指向当前根节点;
        t = parent;  //此时调到栈底了，旋转后将更改root的指向
    }else{
        AVLNode<Type> *tmp = st.top();  //当前的栈顶结点
        if(parent->data < tmp->data){  
            tmp->leftChild = parent;
        }else{
            tmp->rightChild = parent;
        }
    }

    return true;
}
```

## 三、完整代码+测试代码+运行结果

### 3.1 完整代码

```cpp
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include<iostream>  //引入头文件
#include<stack>    //要用栈保存路径信息
using namespace std;

template<typename Type>
class AVLTree;

template<typename Type>
class AVLNode{   //AVL树的结点
    friend class AVLTree<Type>;
public:
    AVLNode() : data(Type()), leftChild(NULL), rightChild(NULL), bf(0){}
    AVLNode(Type d, AVLNode *left = NULL, AVLNode *right = NULL) 
        : data(d), leftChild(left), rightChild(right), bf(0){}
    ~AVLNode(){}
private:
    Type data;
    AVLNode *leftChild;
    AVLNode *rightChild;
    int bf;  //多了一个平衡因子
};

template<typename Type>
class AVLTree{   //AVL树的类型
public:
    AVLTree() : root(NULL){}
public:
    bool insert(const Type &x){
        return insert(root, x);
    }
    void inOrder()const{
        inOrder(root);
    }
protected:
    void inOrder(AVLNode<Type> *t)const{
        if(t != NULL){
            inOrder(t->leftChild);
            cout<<t->data<<" : "<<t->bf<<endl;;
            inOrder(t->rightChild);
        }
    }
    bool insert(AVLNode<Type> *&t, const Type &x); //插入函数
    void RotateR(AVLNode<Type> *&ptr){  //右旋
        AVLNode<Type> *subR = ptr;
        ptr = ptr->leftChild;
        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        ptr->bf = subR->bf = 0;
    }
    void RotateL(AVLNode<Type> *&ptr){  //左旋
        AVLNode<Type> *subL = ptr;
        ptr = subL->rightChild;
        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        subL->bf = ptr->bf = 0;
    }
    void RotateLR(AVLNode<Type> *&ptr){  //先左后右旋转
        AVLNode<Type> *subR = ptr;
        AVLNode<Type> *subL = ptr->leftChild;
        ptr = subL->rightChild;

        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        if(ptr->bf <= 0){
            subL->bf = 0;
        }else{
            subL->bf = -1;
        }

        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        if(ptr->bf == -1){
            subR->bf = 1;
        }else{
            subR->bf = 0;
        }

        ptr->bf = 0;
    }
    void RotateRL(AVLNode<Type> *&ptr){  //先右后左旋转
        AVLNode<Type> *subL = ptr;
        AVLNode<Type> *subR = ptr->rightChild;
        ptr = subR->leftChild;

        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        if(ptr->bf >=0){
            subR->bf = 0;
        }else{
            subR->bf = 1;
        }

        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        if(ptr->bf == 1){
            subL->bf = -1;
        }else{
            subL->bf = 0;
        }
        ptr->bf = 0;
    }
private:
    AVLNode<Type> *root;
};

template<typename Type>
bool AVLTree<Type>::insert(AVLNode<Type> *&t, const Type &x){
    AVLNode<Type> *p = t;
    AVLNode<Type> *parent = NULL; // 记录前驱结点，方便连接和调整平衡因子
    stack<AVLNode<Type> *> st; //用栈记录插入的路径，方便调整栈中结点的平衡因子;
    int sign;

    while(p != NULL){
        if(x == p->data){ //要插入的数据和AVL树中的数字相同,则返回失败！
            return false;
        }

        parent = p;
        st.push(parent); //找过的入栈
        if(x < p->data){
            p = p->leftChild;
        }else if(x > p->data){
            p = p->rightChild;
        }
    } // 找插入位置,不用递归，就是为了记录路径信息
    
    p = new AVLNode<Type>(x);
    if(parent == NULL){
        t = p;    //判断是不是第一个结点，进行root的连接;
        return true;
    }

    if(x < parent->data){ //此时通过父节点的数据判断插入的是左还是右
        parent->leftChild = p;
    }else{
        parent->rightChild = p;
    }
    //新插入点的bf为0,关键是栈中的平衡因子的调整
/////////////////////////////////////////////////////// 以上完成插入工作
    while(!st.empty()){  //栈不空，出栈顶元素
        parent = st.top();
        st.pop();

        if(p == parent->leftChild){   //判断插入的是父节点的左/右孩子,
            parent->bf--;           //让其bf++/--;
        }else{
            parent->bf++;
        }

        //以下判断栈中的平衡因子，看是否需要进行旋转调整
        if(parent->bf == 0){  //bf=0，直接跳出循环
            break;
        }
        if(parent->bf==1 || parent->bf==-1){ 
            p = parent;  //此时在向上走，判断bf;
        }else{  //以下的bf为2/-2;利用标志判断左右旋;
            sign = parent->bf > 0 ? 1 : -1;
            if(p->bf == sign){  //符号相同为单旋
                if(sign == 1){  //为1左旋
                    RotateL(parent);  
                }else{
                    RotateR(parent); //右旋
                }
            }else{  //符号不同，为双旋
                if(sign == 1){  
                    RotateRL(parent); //为1右左
                }else{
                    RotateLR(parent);
                }
            }
/*
    以下方法也可以判断左右旋
        else
        {
            if(parent->bf < 0)  //左边
            {
                if(p->bf<0 && p==parent->leftChild)    //    / 只能是左孩子
                {
                    //RotateR(parent);
                }
                else if(p->bf>0 && p == parent->leftChild)  //   <
                {
                    //RotateLR(parent);
                }
            }
            else
            {
                if(p->bf>0 && p==parent->rightChild)   //   \ 
                {
                    //RotateL(parent);
                }
                else if(p->pf<0 && p==parent->rightChild)  //      >
                {
                    //RotateRL(parent);
                }
            }
        }

*/
    break;
        }
    }

    if(st.empty()){  //通过旋转函数，此时parent指向当前根节点;
        t = parent;  //此时调到栈底了，旋转后将更改root的指向
    }else{
        AVLNode<Type> *tmp = st.top();  //当前的栈顶结点
        if(parent->data < tmp->data){  
            tmp->leftChild = parent;
        }else{
            tmp->rightChild = parent;
        }
    }

    return true;
}
#endif
```

### 3.2 测试代码

```cpp
#include"avlTree.h"

int main(void){
    int ar[] = {16, 3, 7, 11, 9, 26, 18, 14, 15,};
    int n = sizeof(ar) / sizeof(int);
    AVLTree<int> avl;

    for(int i = 0; i < n; i++){
        avl.insert(ar[i]);
    }

    avl.inOrder();
    return 0;
}
```

### 3.3 测试结果

测试最终形成的 AVL 树如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQADAAicS3iamhwXyDIBc1icF5gysCygsS15zmuItr17ycugyodsiadNDnJFJiaopxNwf60kU9c6wKoT4g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtQADAAicS3iamhwXyDIBc1icF5R6yCDuqCLQjWiaLsbxsVgpaW6pFcrna8dugozIrHmXuWMFds0qbLTiaw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

## 四、说明

原创文章链接：[从零开始学习数据结构-->AVL树之插入算法](https://mp.weixin.qq.com/s?__biz=MzU4MjQ3NzEyNA==&mid=2247485445&idx=1&sn=308097bdf1dc20122af766298deded56&chksm=fdb6fc2ecac175384522398f3f2b04be483c47048d56ccf7d08cd0a96e0b45123e0cae269e97&token=1129091266&lang=zh_CN#rd)


---


## 从零开始学习数据结构_AVL树之删除算法

- [一、AVL树删除](#一avl树删除)
- [二、AVL树删除代码](#二avl树删除代码)
- [三、完整代码+测试代码+运行结果](#三完整代码测试代码运行结果)
  - [3.1 完整代码](#31-完整代码)
  - [3.2 测试代码](#32-测试代码)
  - [3.3 运行结果](#33-运行结果)
- [四、说明](#四说明)

## 一、AVL树删除

思路：

1. 首先找到要删除的结点；没找到，直接false返回退出即可；
2. 将其转化为只有一个分支的结点，前面的路径都要入栈；
3. 其父节点(parent)的平衡因子(根据父的左/右=p(要删除的结点)，修改父的bf)，有几种情况：
   1. 父节点的bf=1/-1，代表原先有两个结点，现在剩下一个了，直接退出循环，不用再往上寻找更改bf了；
   2. 父节点的bf=0；
   3. 代表此时的往上更改爷爷结点(在此出栈即可，栈中保存了路径信息)的bf，看情况(bf=2/-2)是否进行旋转，和要进行相应的旋转方式；
4. 判断栈空，进行相应的连接操作；
5. 最后删除这个结点。

相应部分情况：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtTHQeMxDNOOznCYibpaHhAENgt4LKDcU2nrDedGx5LWAtq0J8kxSXzY5vD5QHJatsG9SBf8gDoic4aA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(情况1)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtTHQeMxDNOOznCYibpaHhAENnQUBxvZmia9I08GETI1wWtoMchibhItvCZ82q5CfjMhXib6qaneKa0uiaw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>
<p align=center>(情况2)</p>

## 二、AVL树删除代码

```cpp
template<typename Type>
bool AVLTree<Type>::remove(AVLNode<Type> *&t, const Type &x){
    AVLNode<Type> *p = t;
    AVLNode<Type> *parent = NULL;  //父结点
    AVLNode<Type> *q = NULL;  //删除结点的辅助结点
    stack<AVLNode<Type> *> st;

    AVLNode<Type> *ppr; //爷爷结点

    int flag = 0;
    while(p != NULL){
        if(p->data == x){
            break;
        }
        parent = p;
        st.push(parent);
        if(x < p->data){
            p = p->leftChild;
        }else{
            p = p->rightChild;
        }
    } //以上是：查找删除点
    if(p == NULL){  //没有要删除的结点
        return false;
    }
    if(p->leftChild!= NULL && p->rightChild!=NULL){
        parent = p;
        st.push(parent);

        q = p->leftChild;
        while(q->rightChild != NULL){
            parent = q;
            st.push(parent);
            q = q->rightChild;
        }

        p->data = q->data;
        p = q;
    }
    
    if(p->leftChild != NULL){
        q = p->leftChild;
    }else{
        q = p->rightChild;
    }
//以上是：使其要删除的转化为只有一个分支的
    if(parent == NULL){  //删除的是根结点，并且无入栈，代表只有一个分支，并没有寻找
        t = q;  
    }else{
        if(parent->leftChild == p){
            flag = 0;
            parent->leftChild = q;
        }else{
            flag = 1;
            parent->rightChild = q;
        }

        while(!st.empty()){
            parent = st.top();
            st.pop();
            if(parent->leftChild==q){ //对要删除的父节点更改bf;
                parent->bf++;
            }else{
                parent->bf--;
            }
            if(!st.empty()){
                ppr = st.top();
                if(ppr->leftChild == parent){
                    flag = 0;
                }else{
                    flag = 1;
                }
            }
            if(parent->bf==-1 || parent->bf==1 ){
                break; //删除前的平衡因子为0，此时不用再调整其它平衡因子,直接退出循环;
            }

            if(parent->bf == 0){  //原先只有左孩子/右孩子
                q = parent; //往上回溯更改爷爷结点的bf；
            }else{  //此时到达2,已经不平衡了，的进行旋转化的调整
                if(parent->bf < 0){
                    flag = -1;
                    q = parent->leftChild;
                }else{
                    flag = 1;
                    q = parent->rightChild;
                }
                if(q->bf == 0){
                    if(flag == -1){
                        
                    }
                }
                if(parent->bf > 0){
                    q = parent->rightChild;
                    if(q->bf == 0){
                        RotateL(parent);
                    }else if(q->bf > 0){
                        RotateL(parent);
                    }else{
                        RotateRL(parent);
                    }
                }else{
                    q = parent->leftChild;
                    if(q->bf == 0){
                        RotateR(parent);
                    }else if(q->bf < 0){
                        RotateR(parent);
                    }else{
                        RotateLR(parent);
                    }
                }
            }
        }
        if(st.empty()){
            t = parent;  //直接更改root
        }else{
            AVLNode<Type> *tmp = st.top();  //当前的栈顶结点使其的左/右指向parent(是旋转化后的根);
            if(parent->data < tmp->data){  
                tmp->leftChild = parent;
            }else{
                tmp->rightChild = parent;
            }
        }

    }

    delete p;  //删除结点;
    return true;
}
```

## 三、完整代码+测试代码+运行结果

### 3.1 完整代码

```cpp
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include<iostream>  //引入头文件
#include<stack>    //要用栈保存路径信息
using namespace std;

template<typename Type>
class AVLTree;

template<typename Type>
class AVLNode{   //AVL树的结点
    friend class AVLTree<Type>;
public:
    AVLNode() : data(Type()), leftChild(NULL), rightChild(NULL), bf(0){}
    AVLNode(Type d, AVLNode *left = NULL, AVLNode *right = NULL) 
        : data(d), leftChild(left), rightChild(right), bf(0){}
    ~AVLNode(){}
private:
    Type data;
    AVLNode *leftChild;
    AVLNode *rightChild;
    int bf;  //多了一个平衡因子
};

template<typename Type>
class AVLTree{   //AVL树的类型
public:
    AVLTree() : root(NULL){}
public:
    bool insert(const Type &x){
        return insert(root, x);
    }
    bool remove(const Type &x){
        return remove(root, x);
    }
    void inOrder()const{
        inOrder(root);
    }
protected:
    void inOrder(AVLNode<Type> *t)const{
        if(t != NULL){
            inOrder(t->leftChild);
            cout<<t->data<<" : "<<t->bf<<endl;;
            inOrder(t->rightChild);
        }
    }
    bool insert(AVLNode<Type> *&t, const Type &x); //插入函数
    bool remove(AVLNode<Type> *&t, const Type &x);
    void RotateR(AVLNode<Type> *&ptr){  //右旋
        AVLNode<Type> *subR = ptr;
        ptr = ptr->leftChild;
        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        ptr->bf = subR->bf = 0;
    }
    void RotateL(AVLNode<Type> *&ptr){  //左旋
        AVLNode<Type> *subL = ptr;
        ptr = subL->rightChild;
        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        subL->bf = ptr->bf = 0;
    }
    void RotateLR(AVLNode<Type> *&ptr){  //先左后右旋转
        AVLNode<Type> *subR = ptr;
        AVLNode<Type> *subL = ptr->leftChild;
        ptr = subL->rightChild;

        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        if(ptr->bf <= 0){
            subL->bf = 0;
        }else{
            subL->bf = -1;
        }

        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        if(ptr->bf == -1){
            subR->bf = 1;
        }else{
            subR->bf = 0;
        }

        ptr->bf = 0;
    }
    void RotateRL(AVLNode<Type> *&ptr){  //先右后左旋转
        AVLNode<Type> *subL = ptr;
        AVLNode<Type> *subR = ptr->rightChild;
        ptr = subR->leftChild;

        subR->leftChild = ptr->rightChild;
        ptr->rightChild = subR;
        if(ptr->bf >=0){
            subR->bf = 0;
        }else{
            subR->bf = 1;
        }

        subL->rightChild = ptr->leftChild;
        ptr->leftChild = subL;
        if(ptr->bf == 1){
            subL->bf = -1;
        }else{
            subL->bf = 0;
        }
        ptr->bf = 0;
    }
private:
    AVLNode<Type> *root;
};

template<typename Type>
bool AVLTree<Type>::insert(AVLNode<Type> *&t, const Type &x){
    AVLNode<Type> *p = t;
    AVLNode<Type> *parent = NULL; // 记录前驱结点，方便连接和调整平衡因子
    stack<AVLNode<Type> *> st; //用栈记录插入的路径，方便调整栈中结点的平衡因子;
    int sign;

    while(p != NULL){
        if(x == p->data){ //要插入的数据和AVL树中的数字相同,则返回失败！
            return false;
        }

        parent = p;
        st.push(parent); //找过的入栈
        if(x < p->data){
            p = p->leftChild;
        }else if(x > p->data){
            p = p->rightChild;
        }
    } // 找插入位置,不用递归，就是为了记录路径信息
    
    p = new AVLNode<Type>(x);
    if(parent == NULL){
        t = p;    //判断是不是第一个结点，进行root的连接;
        return true;
    }

    if(x < parent->data){ //此时通过父节点的数据判断插入的是左还是右
        parent->leftChild = p;
    }else{
        parent->rightChild = p;
    }
    //新插入点的bf为0,关键是栈中的平衡因子的调整
/////////////////////////////////////////////////////// 以上完成插入工作
    while(!st.empty()){  //栈不空，出栈顶元素
        parent = st.top();
        st.pop();

        if(p == parent->leftChild){   //判断插入的是父节点的左/右孩子,
            parent->bf--;           //让其bf++/--;
        }else{
            parent->bf++;
        }

        //以下判断栈中的平衡因子，看是否需要进行旋转调整
        if(parent->bf == 0){  //bf=0，直接跳出循环
            break;
        }
        if(parent->bf==1 || parent->bf==-1){ 
            p = parent;  //此时在向上走，判断bf;
        }else{  //以下的bf为2/-2;利用标志判断左右旋;
            sign = parent->bf > 0 ? 1 : -1;
            if(p->bf == sign){  //符号相同为单旋
                if(sign == 1){  //为1左旋
                    RotateL(parent);  
                }else{
                    RotateR(parent); //右旋
                }
            }else{  //符号不同，为双旋
                if(sign == 1){  
                    RotateRL(parent); //为1右左
                }else{
                    RotateLR(parent);
                }
            }
/*
    以下方法也可以判断左右旋
        else
        {
            if(parent->bf < 0)  //左边
            {
                if(p->bf<0 && p==parent->leftChild)    //    / 只能是左孩子
                {
                    //RotateR(parent);
                }
                else if(p->bf>0 && p == parent->leftChild)  //   <
                {
                    //RotateLR(parent);
                }
            }
            else
            {
                if(p->bf>0 && p==parent->rightChild)   //   \ 
                {
                    //RotateL(parent);
                }
                else if(p->pf<0 && p==parent->rightChild)  //      >
                {
                    //RotateRL(parent);
                }
            }
        }

*/
    break;
        }
    }

    if(st.empty()){  //通过旋转函数，此时parent指向根节点;
        t = parent;  //此时调到栈底了，旋转后将更改root的指向
    }else{
        AVLNode<Type> *tmp = st.top();  //当前的栈顶结点
        if(parent->data < tmp->data){  
            tmp->leftChild = parent;
        }else{
            tmp->rightChild = parent;
        }
    }

    return true;
}

template<typename Type>
bool AVLTree<Type>::remove(AVLNode<Type> *&t, const Type &x){
    AVLNode<Type> *p = t;
    AVLNode<Type> *parent = NULL;  //父结点
    AVLNode<Type> *q = NULL;  //删除结点的辅助结点
    stack<AVLNode<Type> *> st;

    AVLNode<Type> *ppr; //爷爷结点

    int flag = 0;
    while(p != NULL){
        if(p->data == x){
            break;
        }
        parent = p;
        st.push(parent);
        if(x < p->data){
            p = p->leftChild;
        }else{
            p = p->rightChild;
        }
    } //以上是：查找删除点
    if(p == NULL){  //没有要删除的结点
        return false;
    }
    if(p->leftChild!= NULL && p->rightChild!=NULL){
        parent = p;
        st.push(parent);

        q = p->leftChild;
        while(q->rightChild != NULL){
            parent = q;
            st.push(parent);
            q = q->rightChild;
        }

        p->data = q->data;
        p = q;
    }
    
    if(p->leftChild != NULL){
        q = p->leftChild;
    }else{
        q = p->rightChild;
    }
//以上是：使其要删除的转化为只有一个分支的
    if(parent == NULL){  //删除的是根结点，并且无入栈，代表只有一个分支，并没有寻找
        t = q;  
    }else{
        if(parent->leftChild == p){
            flag = 0;
            parent->leftChild = q;
        }else{
            flag = 1;
            parent->rightChild = q;
        }

        while(!st.empty()){
            parent = st.top();
            st.pop();
            if(parent->leftChild==q){ //对要删除的父节点更改bf;
                parent->bf++;
            }else{
                parent->bf--;
            }
            if(!st.empty()){
                ppr = st.top();
                if(ppr->leftChild == parent){
                    flag = 0;
                }else{
                    flag = 1;
                }
            }
            if(parent->bf==-1 || parent->bf==1 ){
                break; //删除前的平衡因子为0，此时不用再调整其它平衡因子
            }

            if(parent->bf == 0){  //原先只有左孩子/右孩子
                q = parent; //往上回溯更改爷爷结点的bf；
            }else{  //此时到达2,已经不平衡了，的进行旋转化的调整
                if(parent->bf < 0){
                    flag = -1;
                    q = parent->leftChild;
                }else{
                    flag = 1;
                    q = parent->rightChild;
                }
                if(q->bf == 0){
                    if(flag == -1){
                        
                    }
                }
                if(parent->bf > 0){
                    q = parent->rightChild;
                    if(q->bf == 0){
                        RotateL(parent);
                    }else if(q->bf > 0){
                        RotateL(parent);
                    }else{
                        RotateRL(parent);
                    }
                }else{
                    q = parent->leftChild;
                    if(q->bf == 0){
                        RotateR(parent);
                    }else if(q->bf < 0){
                        RotateR(parent);
                    }else{
                        RotateLR(parent);
                    }
                }
            }
        }
        if(st.empty()){
            t = parent;  //直接更改root
        }else{
            AVLNode<Type> *tmp = st.top();  //当前的栈顶结点使其的左/右指向parent(是旋转化后的根);
            if(parent->data < tmp->data){  
                tmp->leftChild = parent;
            }else{
                tmp->rightChild = parent;
            }
        }

    }

    delete p;  //删除结点;
    return true;
}
#endif
```

### 3.2 测试代码

```cpp
#include"avlTree.h"

int main(void){
    int ar[] = {16, 3, 7, 11, 9, 26, 18, 14, 15,};
    int n = sizeof(ar) / sizeof(int);
    AVLTree<int> avl;

    for(int i = 0; i < n; i++){
        avl.insert(ar[i]);
    }

    cout<<"删除前: "<<endl;
    avl.inOrder();
    avl.remove(16);
    cout<<"删除后: "<<endl;
    avl.inOrder();
    return 0;
}
```

### 3.3 运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/iaumSdLKJXtTHQeMxDNOOznCYibpaHhAEN52N3YAdl1ALujMsic4CibAB9HAuqd0IA9T6WDdRtlibSqHOvJ5TkLcU6A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1'></div>

<div align=center><img src='./picture/avl.jpeg'></div>

## 四、说明

原创文章链接：[从零开始学习数据结构-->AVL树之删除算法](https://mp.weixin.qq.com/s?__biz=MzU4MjQ3NzEyNA==&mid=2247485492&idx=1&sn=33cbd977c0561954cef05cc5cfec94eb&chksm=fdb6fc1fcac175099cb77513edde1c6276e455e50dc85de5694fdb2360e40738f27c8a78a373&token=1129091266&lang=zh_CN#rd)


---
