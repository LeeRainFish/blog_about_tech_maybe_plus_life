

进程原语    线程原语
fork        pthread_create
exit        pthread_exit
waitpid     pthread_join
atexit      pthread_cancel_push
getpid      pthread_self
abort       pthread_cancel
