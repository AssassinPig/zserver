#include "zsocket.hpp"
#include "zsocket_util.hpp"
#include "com_inc.hpp"
ZSocket::ZSocket(int fd)
{
    m_sockfd = fd;
}
 
ZSocket::~ZSocket()
{
}

void ZSocket::AttachFD(int fd)
{
    m_sockfd = fd;
}

void ZSocket::DetachFD()
{
    m_sockfd = -1;
}

int ZSocket::Close()
{
    return ZClose(m_sockfd);   
}

int ZSocket::GetFD()
{
    return m_sockfd;
}

int ZSocket::Bind(const sockaddr* sockaddr, socklen_t len)
{
    return ZBind(m_sockfd, sockaddr, len);
}

int ZSocket::Bind(const char* bind_ip, int port)
{
    //bind ip and port
    sockaddr_in addr;               //only ipv4 
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(bind_ip);
    addr.sin_port = htons(port);
    return Bind((sockaddr*)&addr, sizeof(sockaddr_in));
}

int ZSocket::Listen(int fd, int backlog)
{
    return ZListen(fd, backlog);
}

int ZSocket::Connect(int fd, const sockaddr* sockaddr, socklen_t len)
{
    return ZConnect(fd, sockaddr, len);
}

int ZSocket::Accept(struct sockaddr* sockaddr, socklen_t* len)
{
    return ZAccept(m_sockfd, sockaddr, len);
}

int ZSocket::Setsockopt(int fd, int level, int optname, void* optval, socklen_t optlen)
{
   return ZSetsockopt(fd, level, optname, optval, optlen);  
}



