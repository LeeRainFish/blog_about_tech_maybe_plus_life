#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>

//socket
#include <sys/socket.h>

// epoll
#include <sys/epoll.h>
#include <sys/time.h>

// <= 1024
#define FDS_NUM 5
#define BUFF_SIZE 256

// Example from man epoll
//
int couruntine_read(int fd){
    // while (notfinish) {
    //     yield();

    //     read(fd);
    // }
    // close();
}

int couruntine_write(int fd){
    // while (notfinish) {
    //     yield();

    //     write(fd);
    // }
    // close();
}


int setnonblocking(int sockfd)  
{  
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1)  
    {  
        return -1;  
    }  
    return 0;  
} 

int main()
{
    int socketfd, connfd, nfds, epfd;
    struct sockaddr_in addr, client;
    char buffer[BUFF_SIZE];
    int addrlen;

    static struct epoll_event ev; // 临时事件
    struct epoll_event events[FDS_NUM];

    // servet socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9988);

    bind(socketfd,
            (struct sockaddr*) &addr, sizeof(struct sockaddr_in));
    listen(socketfd,FDS_NUM);

    // epoll init fd
    // epfd = epoll_create1();
    // 创建所有epoll的fd
    epfd = epoll_create(10);

    // epoll_ctl 添加删除fd(注册fd)
    // 每次只需要传入一个操作的fd，而且只需要注册一次。不需要像select和poll那样全部传入
    memset(&client,0,sizeof(struct sockadd_in));
    ev.data.fd = socketfd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1){
        perror("epoll ctl add socketfd to epfd fail");
        exit(EXIT_FAILURE);
    }


    // still serial but no cost of thread swithing
    // the way to read/write can be modified by coroutine;
    while(1){

        // events 数组是变动的，前返回值n个都是可响应事件
        // 通过epoll_wait得到的fd事件集合都是已经就绪的
        nfds = epoll_wait(epfd, events, FDS_NUM, -1);

        for(int i = 0; i < nfds; i++){
            // socketfd 
            if(events[i].data.fd == socketfd){
                //connfd = accept(socketfd,
                //       (struct sockaddr*) &client, &addrlen); 
                connfd = accept(socketfd, NULL, NULL); 
                // what is that ?
                // 如果将文件设置成非阻塞，即便发现内容为空，也不会阻塞等待而是会直接返回，
                // 但是由于没有内容因此只能返回一个特殊数字-1
                setnonblocking(connfd);

                // fd can be written and event is edge trigger
                // 新fd注册
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
            }else{
                //do_use_fd

                    // 可读事件
                if(events[i].events & EPOLLIN){
                    memset(buffer, 0, BUFF_SIZE);
                    read(events[i].data.fd, buffer, BUFF_SIZE);
                    puts(buffer);
                    // 对每个fd 做一个协程
                    // 恢复现场
                    // 接着读

                    // if(hasnext){
                        // 保存现场
                        // 等待可读
                    // }
                } else if(events[i].events & EPOLLOUT){
                    // 可写事件
                    // memcpy();
                    // write()
                }
            }
        }
    }

    return 0;
}
