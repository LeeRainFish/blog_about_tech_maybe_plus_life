#include <uinstd.h>
#include <fcntl.h>
#include <errno.h>


// 初始化的时候
    int fl; 
    fl = fcntl(fd,F_GETFL); fcntl(fd,F_SETFL, fl | O_NONBLOCK);

void callback(int fd, void *data)
{
    char buf[BUFSIZ];
    int n;
    n = read(fd, buf, BUFSIZ);
    if(n < 0){
        if(errno == EAGAIN) // EAGAIN 缓冲区为空
            return 1;
        else
            return -1
    }

    if(n == 0){ // EOF
        return 0;
    }
    output();


}

int main()
{



}



