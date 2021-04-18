
进程    process
线程    thread

Fiber       协程
Coroutine

```cpp
// select
int select();

// poll
int poll();

// epoll
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);


```

```cpp
// epoll data structure

struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};

typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;



```

由于epoll的监听对象是红黑树，所以检索速度很快，且有事件产出，
不需要遍历判断就绪状态

io multiplexing + coroutine  = best match

