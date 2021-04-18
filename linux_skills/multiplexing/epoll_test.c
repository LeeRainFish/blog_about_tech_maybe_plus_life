#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//socket
#include <sys/socket.h>

// epoll
#include <sys/epoll.h>
#include <sys/time.h>

// <= 1024
#define FDS_NUM 5
#define BUFF_SIZE 256

int main()
{
    int socketfd, nfds, epfd;
    struct sockaddr_in addr, client;
    char buffer[BUFF_SIZE];

    struct epoll_event events[FDS_NUM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_in));
    // ip address protocol
    addr.sin_family = AF_INET;
    // port
    addr.sin_port = htons(9988);
    // which ip can connet this
    addr.sin_addr.s_addr = INADDR_ANY;
   
    bind(socketfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));
    listen(socketfd,FDS_NUM);
    // bind -> listen-> accept

    epfd = epoll_create(10);

    for(int i = 0; i < FDS_NUM; i++){
        static struct epoll_event ev;
        memset(&client,0,sizeof(struct sockadd_in));
        ev.data.fd = accpet(socketfd,(struct sockaddr*)&client, sizeof(struct sockaddr_in));
        ev.events = EPOLLIN;
        // set
        epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
    }

    while(1){
        // return num of ready events
        // it resort epfd  so that ready events will always in the front;
        nfds = epoll_wait(epfd, events, FDS_NUM, -1);

        for(int i = 0; i < nfds; i++){
            memset(buffer, 0, BUFF_SIZE);
            read(events[i].data.fd, buffer, BUFF_SIZE); 
            puts(buffer);
        }
    }

    return 0;
}
