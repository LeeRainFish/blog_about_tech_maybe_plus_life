#!/usr/bash

# variables
NGINX_INSTALL_DIR=/usr/local/nginx
NGINXD=$NGINX_INSTALL_DIR/sbin/nginx
PID_FILE=$NGINX_INSTALL_DIR/logs/nginx.pid

# Shell 文件包含
# source function library
if [ -f /etc/init.d/functions ];then
    . /etc/init.d/functions
else
    echo "not found file /etc/init.d/functions"
    exit
fi

# function
start(){

}

stop(){

}

restart(){

}

reload(){

}

status(){

}

# callale main
case $1 in
    start) start;;
    stop) stop;;
    restart) restart;;
    reload) reload;;
    status) status;;
    *) echo "USAGE: $0 start|stop|restart|reload|status";;
esac
