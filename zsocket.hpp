#ifndef _ZSOCKET_H__
#define _ZSOCKET_H__

#include "com_inc.hpp"

class ZSocket
{
    public:
        ZSocket(int fd = -1); 
        ~ZSocket(); 

        void AttachFD(int fd);
        void DetachFD();
        int Close();
        int GetFD();

        int Bind(const sockaddr* sockaddr, socklen_t len);
        int Bind(const char* bind_ip, int port);
        int Listen(int fd, int backlog=512);
        int Connect(int fd, const sockaddr* sockaddr, socklen_t len);
        int Accept(struct sockaddr* sockaddr, socklen_t* len);
        int Setsockopt(int fd, int level, int optname, void* optvalue, socklen_t optlen);

    private:
        int m_sockfd;
};

#endif//_ZSOCKET_H__ 
