#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//socket
#include <sys/socket.h>

// poll
#include <sys/poll.h>
#include <sys/time.h>

// <= 1024
#define FDS_NUM 5
#define BUFF_SIZE 256

int main()
{
    int socketfd;
    struct pollfd pollfds[FDS_NUM];
    /*
    strcut pollfd
    {
        int fd;
        short events;
        short revents;
    } 
     * */
    struct sockaddr_in addr, client;
    fd_set rset;

    char buffer[BUFF_SIZE];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_in));
    // ip address protocol
    addr.sin_family = AF_INET;
    // port
    addr.sin_port = htons(9988);
    // which ip can connet this
    addr.sin_addr.s_addr = INADDR_ANY;
   
    bind(socketfd, (struct sockaddr*) &addr, sizeof(sockaddr_in));
    listen(socketfd,FDS_NUM);

    // set pollfds
    for(int i = 0; i < FDS_NUM ;i++){
        memset(&client, 0, sizeof(struct sockaddr_in));
        pollfds[i].fd = accept(socketfd, (struct sockaddr*) &client, sizeof(sockaddr_in));
        pollfds[i].events = POLLIN;
    }

    while(1){

        // block in kernel space
        poll(pollfds,5,50000);

        // O(n) serach
        for(int i = 0; i < FDS_NUM ;i++){
            if(pollfds[i].revents & POLLIN){
                memset(buffer, 0, BUFF_SIZE);
                read(pollfds[i].fd, buffer, BUFF_SIZE);
                puts(buffer);
            }
        }
    }

    return 0;
}
