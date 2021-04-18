#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>


// if use a unix function and it return intenger>0 as file description
// return <0 such as -1, as error code
// use this function
int guard(int n, char *err_info)
{ 
    if (n == -1) { 
        perror(err_info); 
        exit(1); 
    }

    return n; 
}

int guard_ptr(void *ptr, char *err_info)
{ 
    if (!ptr) { 
        perror(err_info); 
        exit(1); 
    }

    return 0; 
}

int main()
{
    // such as 
    int listen_socket_fd = guard(socket(AF_INET, SOCK_STREAM, 0), 
            "could not create TCP listening socket");

    int flags = guard(fcntl(listen_socket_fd, F_GETFL), 
            "could not get flags on TCP listening socket");

    guard(fcntl(listen_socket_fd, F_SETFL, flags | O_NONBLOCK), 
            "could not set TCP listening socket to be non-blocking");
}
