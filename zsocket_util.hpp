#ifndef _ZSOCKET_UTIL_H__ 
#define _ZSOCKET_UTIL_H__

#include "com_inc.hpp"

int ZSetsockopt(int fd, int level, int optname, const void* optval, socklen_t optlen);
int ZBind(int fd, const struct sockaddr* sockaddr, socklen_t addlen); 
int ZListen(int fd, int backlog);
int ZTCPSocket(); 
int ZFcntl(int fd, int cmd, ...);
int ZClose(int fd);
int ZAccept(int sockfd, struct sockaddr* sockaddr, socklen_t* len);
int ZConnect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
#endif
