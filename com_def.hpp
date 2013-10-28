#ifndef _COM_DEF_H__
#define _COM_DEF_H__

#ifndef MAX_FD_NUM 
#define MAX_FD_NUM 1024
#endif //MAX_FD_NUM 

#ifndef ERR 
#define ERR -1
#endif  //ERR

#ifndef SUCC
#define SUCC 0
#endif //SUCC

#ifndef USER_ID 
#define USER_ID uint32_t 
#endif  //USER_ID

#define BIND_IP "127.0.0.1"
#define BIND_PORT 27149
#define LISTENER_MAX 1024

#define MAX_EPOLL_EVENT 64 

#define MAX_SEND 1024
#define MAX_RECV 1024 

#define ZFD_T int 

#endif   //_COM_DEF_H_

