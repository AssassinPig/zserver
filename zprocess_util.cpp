#include "zprocess_util.hpp"
#include "com_inc.hpp"

#define CONTROLLEN sizeof (struct cmsghdr) + sizeof (int)

int ZLocalSocketpair(int fd[2])
{
    int ret = -1;
    if( (ret = socketpair(AF_INET, SOCK_STREAM, 0, fd)) < 0) {
        perror("socketpair create failed");
    }

    return ret;
}

int ZRecvFD(int fromFD, int* recvfd)
{
    char tmpbuf[CONTROLLEN];
    struct cmsghdr *cmptr = (struct cmsghdr *) tmpbuf;
    struct iovec iov[1];
    struct msghdr msg;
    char buf[1];
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof (buf);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    int ret = -1;
    if ((ret = recvmsg(fromFD, &msg, 0)) < 0) {
        perror("recvmsg failed");
    } else {
        *recvfd = *(int *) CMSG_DATA (cmptr);
    }

    return ret;
}

int ZSendFD(int toFD, int sendfd)
{
    char tmpbuf[CONTROLLEN];
    struct cmsghdr *cmptr = (struct cmsghdr *) tmpbuf;
    struct iovec iov[1];
    struct msghdr msg;
    char buf[1];
    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    *(int *)CMSG_DATA (cmptr) = sendfd;

    int ret = -1;
    if ( (ret = sendmsg(toFD, &msg, 0)) != 1) {
        perror("sendmsg failed");
    }

    return ret;
}

