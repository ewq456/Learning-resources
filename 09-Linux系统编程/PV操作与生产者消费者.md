# PV操作与生产者消费者模型


## P_V操作

- [一、P-V操作原理](#一p-v操作原理)
- [二、P-V操作的实现](#二p-v操作的实现)

## 一、P-V操作原理

P-V操作利用信号量的阻塞，也相当于一种锁机制。

P操作和V操作是不可中断的程序段，称为原语。

P原语操作的动作：

1. sem减1；
2. 若sem减1后仍大于或等于0，则进程继续执行；
3. 若sem减1后小于0，则该进程被阻塞后进入与该信号相对应的队列中，然后转进程调度。

V原语操作的动作：

1. sem加1；
2. 若相加结果大于0，则进程继续执行；
3. 若相加结果小于或等于0，则从该信号的等待队列中唤醒一等待进程，然后转进程调度。

**注意：P、V操作对于每一个进程来说，都只能进行一次，而且必须是成对使用，且在P、V原语执行期间不允许有中断发生。**

## 二、P-V操作的实现

思路：根据共享内存和信号量的知识，进行P、V操作的实现，目的：实现服务器端和客户端一问一答的对话模式？

1、服务器端代码：

```cpp
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(void){

    key_t shm_key = ftok("tmp", 7); 
    if(shm_key == -1){
        perror("ftok shm");
        return -1; 
    }   
    int shmid = shmget(shm_key, 1024, IPC_CREAT | IPC_EXCL | 0755);
    if(shmid == -1){
        perror("shmget");
        return -1; 
    }   
    char *ch = (char *)shmat(shmid, NULL, 0); 
    if(ch == (void *)-1){
        perror("shmat");
        return -1;
    }

    key_t sem_key;
    sem_key = ftok("tmp", 2);
    int semid = semget(sem_key, 2, IPC_CREAT | IPC_EXCL | 0755); //申请2个共享资源
    if(semid == -1){
        perror("semget");
        shmdt(ch);
        shmctl(shmid, IPC_RMID, 0);
        return -1;
    }

    union semun init;
    init.val = 0;
    semctl(semid, 0, SETVAL, init);  //初始化信号量，下标为0的初始化为0个
    semctl(semid, 1, SETVAL, init);  //下标为1的初始化为0个 
    struct sembuf p = {0, -1, 0};
    struct sembuf v = {1, 1, 0};

    while(1){
        printf("Ser :>");
        scanf("%s", ch);
        if(strncmp(ch, "quit", 4) == 0){
            shmdt(ch);   
           break;
        }
        semop(semid, &v, 1);

        semop(semid, &p, 1);
        printf("Cli :>%s\n", ch);
    }

    int res = shmctl(shmid, IPC_RMID, 0);
    if(res == -1){
        printf("Remove shm Fail\n");
        return -1;
    }
    printf("Remove shm OK\n");

    return 0;
}
```

2、客户端代码：

```cpp
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(void){
    key_t shm_key = ftok("tmp", 7);
    if(shm_key == -1){
        perror("ftok shm");
        return -1;
    }
    int shmid = shmget(shm_key, 0, 0);  //获取已有的共享内存id；
    if(shmid == -1){
        perror("shmget");
        return -1;
    }
    char *ch = (char *)shmat(shmid, NULL, 0);
    if(ch == (void *)-1){
        perror("shmat");
        return -1;
    }

    key_t sem_key;
    sem_key = ftok("tmp", 2);
    int semid = semget(sem_key, 0, 0);  //获取已有的信号量id；
    if(semid == -1){
        perror("semget");
        shmdt(ch);
        return -1;
    }

    union semun init;
    struct sembuf p = {1, -1, 0};
    struct sembuf v = {0, 1, 0};

    while(1){
        semop(semid, &p, 1);
        printf("Ser :>%s\n", ch);
        printf("Cli :>");
        scanf("%s", ch);
        if(strncmp(ch, "quit", 4) == 0){
            shmdt(ch);
            break;    
        }
        semop(semid, &v, 1);

    }

    return 0;
}
```

3、运行结果

服务器端运行结果：

<div align=center><img src='./picture/pv_1.png' width="50%" height="50%"></div>

客户端运行结果：

<div align=center><img src='https://s2.51cto.com/wyfs02/M00/87/C3/wKioL1fhFxGSp5xNAAA4cJAcQpQ290.png-wh_500x0-wm_3-wmp_4-s_1964790139.png' width="50%" height="50%"></div>

</br>

这样就实现了服务器端和客户端的一问一答的模式。

**利用共享内存开辟空间，信号量进行资源控制，达成一问一答模式。**


---


## 生产者与消费者

- [一、生产者与消费者问题](#一生产者与消费者问题)
- [二、代码实现](#二代码实现)

## 一、生产者与消费者问题

- 空间满：生产者不能生产数据；
- 空间空：消费者不能取出数据；

在这种模型下，将会有(生产者：消费者)为：一对一、一对多、多对一、多对多。

为了简化问题，在这里就只实现一个生产者和一个消费者的问题。

模型如下：

<div align=center><img src='https://s4.51cto.com/wyfs02/M00/87/D8/wKiom1fjAGbwvJgJAAAjtPima4g711.png-wh_500x0-wm_3-wmp_4-s_1575229629.png' width="50%" height="50%"></div>

注意：

1. **线程阻塞时，用条件变量来解决。唤醒并运行其后的语句是在遇到阻塞之后；**
2. **临界区模式；**

```cpp
pthread_mutex_lock(&mutex);
//临界区
pthread_cond_wait(&cond, &mutex); //该函数将自动解锁，此处将会发生阻塞。

......

pthread_mutex_unlock(&mutex);
```

3. **本题还可以采用双缓冲区；**

## 二、代码实现

```cpp
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define BUF_SIZE    8   //一个开辟8个数组元素空间
#define MAX_NUM     20   //将一共产生20个数据

struct PC{   //生产者与消费者结构体
    pthread_mutex_t mutex;  //互斥量
    pthread_cond_t noempty;  //条件变量，数组不空
    pthread_cond_t nofull;   //条件变量，数组不满
    int buf[BUF_SIZE];  //开辟空间
    int nput;  //数组下标
    int nval;  //要存放的数据
    int size;  //统计当前数组空间大小
}shared = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

void* producer(void *arg){
    for(;;){
        pthread_mutex_lock(&shared.mutex);
        if(shared.nval > MAX_NUM){
            pthread_mutex_unlock(&shared.mutex);
            break;
        }
        shared.buf[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        shared.size++;

        if(shared.nput >= BUF_SIZE){
            shared.nput = 0;  //下标始终在0-7
        }
        if(shared.size >= BUF_SIZE){ 
            pthread_cond_wait(&shared.nofull, &shared.mutex);
        }else{
            pthread_cond_signal(&shared.noempty);
        }
        pthread_mutex_unlock(&shared.mutex);
    }
}

void *customer(void *arg){
    int value;
    int i = 0;
    for(;;){
        pthread_mutex_lock(&shared.mutex);
        value = shared.buf[i];
        i++;
        printf("value = %d\n", value);   
        if(value >= MAX_NUM){
            pthread_mutex_unlock(&shared.mutex);
            break;
        }
        sleep(1);

        if(i >= BUF_SIZE){
            i = 0;
        }
        shared.size--;
        if(shared.size == 0){
            pthread_cond_wait(&shared.noempty, &shared.mutex);
        }else{
            pthread_cond_signal(&shared.nofull);
        }

        pthread_mutex_unlock(&shared.mutex);
    }
}

void initPc(void){  //对结构体成员初始化
    memset(shared.buf, 0, BUF_SIZE);   
    shared.nput = 0;  //下标从0开始
    shared.nval = 1;  //存放的数据从1开始
    shared.size = 0;  //数组空间大小为0
}

int main(void){
    initPc();
    pthread_t pid, cid;
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, customer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
```

运行结果：

<div align=center><img src='./picture/生产者.png' width="50%" height="50%"></div>

</br>

对以上的代码模式解读：首先是生产者生产，在空间满了之后，阻塞等待，此时，消费者在读取数据，等到读取为空的时候，唤醒生产者生产，最后，在生产完了的时候，消费者读取完成，将一起退出for循环。

**这里的同步就是利用了锁机制完成的(通过互斥量和条件变量)。**


---
