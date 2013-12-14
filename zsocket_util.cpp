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

int zread(int fd, const void* buf, size_t len)
{
    size_t  nleft;                                            
    ssize_t nread;  
    char *ptr;   

    ptr = (char*)buf;                                               
    nleft = len;
    while (nleft > 0) {                                       
        if ( (nread = read(fd, ptr, nleft)) < 0) {        
            if (errno == EINTR)
                nread = 0;              /* and call read() again */            
            else    
                return(-1);                       
        } else if (nread == 0)                            
            break;                          /* EOF */

        nleft -= nread;                                   
        ptr   += nread;                                   
    }       
    return(len - nleft);              /* return >= 0 */    
}

int zwrite(int fd, const void* buf, size_t len)
{
    size_t          nleft;                                    
    ssize_t         nwritten;
    const char      *ptr;

    ptr = (const char*)buf;                                               
    nleft = len;
    while (nleft > 0) {                                       
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {   
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;           /* and call write() again */           
            else    
                return(-1);                     /* error */
        } 

        nleft -= nwritten;
        ptr   += nwritten;                                
    }       
    return(len);
}

int ZRead(int sockfd, const void* buf, size_t len)
{
    ssize_t size;
    if( (size = zread(sockfd, buf, len)) < 0) {
        perror("ZRead failed");        
    }

    return size;
}

int ZWrite(int sockfd, const void* buf, size_t len)
{
    ssize_t size;
    if( (size = zwrite(sockfd, buf, len)) < 0) {
        perror("ZRead failed");        
    }

    return size;
}
