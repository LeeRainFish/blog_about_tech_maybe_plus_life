/********************************************************************************
* @File name: main.c
* @Author: Rain Lee
* @Version: 1.0
* @Date: 2020-11-17
* @Description: Homework 1 for Linux Lesson(did not write error handling code)
* @reference: "Unix Network Programming Volume 2:Interprocess Communications"
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NBUFF 2 // A 与 B 两个进程数
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

struct shared
{
    int len[NBUFF];             //进程数
    sem_t   n_empty, n_stored;  //模仿生产者消费者信号量
} shared;

// 判断是否为小写字母
int is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

// 转换为大写字母
char to_upper(char c)
{
    return c - 32;
}

int main(int argc, char **argv )
{
    int     fd_in,fd_out;
    struct  stat f_info;
    unsigned long filesize;
    unsigned int page_size,buffer_size;
    struct shared *ptr;
    char *addr[2];                  //匿名共享区域 A B

    if(argc < 3)
        return 0;

    // mmap 要求 len 与 offset为pagesize倍数
    page_size = sysconf(_SC_PAGE_SIZE);  
    buffer_size = page_size * 2;

    // 打开读取的文件和要写入的文件（无则创建）
    fd_in= open(argv[1], O_RDWR, FILE_MODE);
    fd_out= open(argv[2], O_RDWR | O_CREAT, FILE_MODE);

    // 使用匿名共享内存区保存信号量等需要共享的数据机构
    ptr = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANON, 0, 0);            

    // 创建A B 两个匿名共享内存区
    for(int i = 0; i < NBUFF; i++){
        addr[i] = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE,
                MAP_ANON | MAP_SHARED, 0, 0);
        ptr->len[i] = buffer_size;
    }

    // 根据输入文件设置输出文件大小
    fstat(fd_in,&f_info);
    filesize = f_info.st_size;
    printf("filesize :%ld \n",filesize);
    ftruncate(fd_out, filesize);

    // create, initialize and unlink semaphore
    sem_init(&ptr->n_empty, 1, NBUFF);
    sem_init(&ptr->n_stored, 1, 0); 
    setbuf(stdout,NULL);

    // 使用父子进程模拟 X 和 Y 进程
    if(fork() == 0){
        // child process read file
        printf("X read process\n");
        off_t rf_offset = 0;
        int i,j = 0;
        void *temp = NULL;

        for(i = 0; ; ){
            sem_wait(&ptr->n_empty);
            // preantf("[%d]-rf_offset :%ld\n",i,rf_offset);
            if(rf_offset + buffer_size > filesize){
                ptr->len[i] = filesize % buffer_size;
            }
            temp = mmap(NULL, ptr->len[i], PROT_READ | PROT_WRITE, 
                    MAP_SHARED, fd_in, rf_offset);

            // 读
            memcpy(addr[i], temp, ptr->len[i]);
            munmap(temp, ptr->len[i]);

            rf_offset = (++j) * buffer_size; 

            // 读完退出
            if(ptr->len[i] < buffer_size){
                sem_post(&ptr->n_stored);
                close(fd_in);
                exit(0);
            }
            if (++i >= NBUFF)
                i = 0;
            sem_post(&ptr->n_stored);
        }
    }else{
        // parent  process compute and write  file
        printf("Y write process\n");
        int i ;
        off_t wf_offset = 0;
        unsigned char *wptr = NULL;

        for(i = 0; ; ){
            sem_wait(&ptr->n_stored);
            // printf("wf_offset :%ld \n",wf_offset);
            // 转换和写
            wptr = mmap(NULL, ptr->len[i], PROT_READ | PROT_WRITE,
                    MAP_SHARED, fd_out, wf_offset);        

            for(int k = 0; k < ptr->len[i]; k++){
                if(is_lower((char )addr[i][k]))
                    wptr[k] = to_upper((char) addr[i][k]);
                else 
                    wptr[k] = (char) addr[i][k];
            }

            munmap(wptr, ptr->len[i]);

            // 写完退出 释放资源
            if(ptr->len[i] < buffer_size){
                munmap(addr[0], buffer_size);
                munmap(addr[1], buffer_size);
                munmap(ptr, sizeof(struct shared));

                close(fd_out);
                exit(0);
            }

            wf_offset = wf_offset + buffer_size;
            if(++i >= NBUFF)
                i = 0 ;
            sem_post(&ptr->n_empty);
        }
    }
}
