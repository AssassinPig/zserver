#ifndef _ZPROCESS_UTIL_H__ 
#define _ZPROCESS_UTIL_H__

int ZLocalSocketpair(int fd[2]);
int ZRecvFD(int fromFD, int* recvfd);
int ZSendFD(int toFD, int sendfd);

#endif//_ZPROCESS_UTIL_H__
