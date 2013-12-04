#ifndef _ZSOCKET_UTIL_H__ 
#define _ZSOCKET_UTIL_H__

int ZSetsockopt(int fd, int level, int optname, const void* optval, socklen_t optlen)
{
    if(-1 == setsockopt(fd, level, optname, optval, optlen)) {
        perror("setsocketopt failed");
        return -1;
    } 

    return 0;
}

int ZBind(int fd, const struct sockaddr* sockaddr, socklen_t addlen) 
{
    if(-1 == bind(fd, sockaddr, addlen)) {
        perror("bind failed");
        return -1;
    } 

    return 0;
}

int ZListen(int fd, int backlog)
{
    if(-1 == listen(fd, backlog)) {
        perror("listen failed");
        return -1;
    }

    return 0;
}

int TCPSocket() 
{
    int sockfd = -1; 
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket tcp failed");
        return -1;
    }

    return sockfd;
}

int ZFcntl(int fd, int cmd, ...)
{
    return -1;
}

#endif
