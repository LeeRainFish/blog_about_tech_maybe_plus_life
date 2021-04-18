#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//socket
#include <sys/socket.h>

// select
#include <sys/select.h>
#include <sys/time.h>

// <= 1024
#define FDS_NUM 5


int main()
{
    int socketfd;
    int fds[FDS_NUM];
    int max_fd;
    struct sockaddr_in addr, client;
    fd_set rset;

    char buffer[256];

    max_fd = -1;
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

    // set fds
    for(int i = 0; i < FDS_NUM ;i++){
        memset(&client, 0, sizeof(struct sockaddr_in));
        fds[i]= accept(socketfd, (struct sockaddr*) &client, sizeof(sockaddr_in));
        if(max_fd < fds[i]){
            max_fd = fds[i];
        }
    }

    while(1){
        FD_ZERO(&rset);
        for(int i = 0; i < FDS_NUM ;i++){
            FD_SET(fds[i],&rset);
        }

        // block in kernel space
        seletc(max_fd + 1, &rset, NULL,NULL,NULL);

        // O(n) serach
        for(int i = 0; i < FDS_NUM ;i++){
            if(FD_ISSET(fds[i], &rset)){
                memset(buffer,0,256);
                read(fds[i],buffer,256);
                puts(buffer);
            }
        }

    }

    return 0;
}

