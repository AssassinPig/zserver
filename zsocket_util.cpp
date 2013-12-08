#include "zsocket_util.hpp"

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

int ZTCPSocket() 
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

int ZClose(int fd)
{
    int ret = 0;
    if( (ret = close(fd)) < 0) {
        perror("close fd failed");
    }
    return ret;
}

int ZAccept(int sockfd, struct sockaddr* sockaddr, socklen_t* len)
{
    int sock_ret = -1;
    if( (sock_ret = accept(sockfd, sockaddr, len))<0) {
        perror("accept socket failed"); 
    }

    return sock_ret;
}

int ZConnect(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
{
    int ret = -1;
    if( (ret = connect(sockfd, addr, addrlen)) < 0) {
        perror("connect failed");
    }

    return ret;
}
