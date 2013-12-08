#include "zepoll.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "com_inc.hpp"
#include "zlog.hpp"
#include "zmutex.hpp"
#include "zsocket_util.hpp"

int epoll_thread_fun(void* data)
{
    ZEpoll* epoll= (ZEpoll*)data;
    while(1) {
        if(epoll->status() == ZMT_EXIT) {
            break;				
        }

        epoll->loop();
    }

    //clean 
    zlog.log("epoll thread exit then close epoll");
    epoll->shutdown(); 
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZEpoll::ZEpoll()
{
}

ZEpoll::~ZEpoll()
{
}

void ZEpoll::set_sockaddr(const char* bind_ip, int port)
{
    //bind ip and port
    m_sockaddr.sin_family = AF_INET;
    m_sockaddr.sin_addr.s_addr = inet_addr(bind_ip);
    m_sockaddr.sin_port = htons(port);
}

int ZEpoll::init()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::startup()
{
    //set max fd num
    m_epoll = epoll_create(MAX_FD_NUM);
    if (m_epoll <= 0) {
        return -1;
    }

    //m_listener = socket(AF_INET, SOCK_STREAM, 0);
    m_listener = ZTCPSocket();

    fcntl(m_listener, F_SETFL, fcntl(m_listener, F_GETFL)|O_NONBLOCK);

    int f = 1;
    if (ERR == ZSetsockopt(m_listener, SOL_SOCKET, SO_REUSEADDR, (char*)&f, sizeof(f))) {
        return -1;
    }

    if (ERR == ZBind(m_listener, (sockaddr*)&m_sockaddr, sizeof(m_sockaddr))) {
        return -1;
    }

    if (ERR == ZListen(m_listener, LISTENER_MAX)) {
        return -1;
    }

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = m_listener;
    if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, m_listener, &ev) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    zlog.log("epoll startup");
    m_status = ZMT_RUNNING;

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::shutdown()
{
    zlog.log("epoll shutdown");
    close(m_epoll);
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::exit()
{
    zlog.log("epoll exit");
    shutdown();
    m_status = ZMT_EXIT;
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZEpoll::set_read(epoll_event& ev, bool flag)
{
    if(flag) {
        ev.events |= EPOLLIN;
    } else {
        ev.events &= ~EPOLLIN;
    }

    ZConnection* connection = (ZConnection*)ev.data.ptr;
    if (epoll_ctl(m_epoll, EPOLL_CTL_MOD, connection->get_fd(), &ev) == -1) {
        perror("set read event epoll_ctl");
        return;
    }
}

void ZEpoll::set_write(epoll_event& ev, bool flag)
{
    if(flag) {
        ev.events |= EPOLLOUT;
    } else {
        ev.events &= ~EPOLLOUT;
    }

    ZConnection* connection = (ZConnection*)ev.data.ptr;
    if (epoll_ctl(m_epoll, EPOLL_CTL_MOD, connection->get_fd(), &ev) == -1) {
        perror("set write event epoll_ctl");
        return;
    }
}

void ZEpoll::del(int fd)
{
    if (epoll_ctl(m_epoll, EPOLL_CTL_DEL, fd, NULL) == -1) {
        perror("delete event epoll_ctl");
    }
}

void ZEpoll::set_accept_handler(accept_handler handler) { 
    m_accept_handler = handler;
}

int ZEpoll::loop()
{
    zlog.log("zepoll::loop()");
    std::vector<ZConnection*> closelist;
    struct epoll_event events[MAX_EPOLL_EVENT];
    int nfds;
    nfds = epoll_wait(m_epoll, events, MAX_EPOLL_EVENT, 1000);
    if(m_status == ZMT_EXIT) //maybe kick all connection
        return 0;

    for (int i = 0; i < nfds; ++i) {
        if (events[i].data.fd == m_listener) {
            sockaddr_in in;
            socklen_t len;
            len = sizeof(in);

            int client_fd;
            while( (client_fd = accept(m_listener, (struct sockaddr *)&in, &len)) > 0) {
                zlog.log("accpet client %s:%d", inet_ntoa(in.sin_addr), ntohs(in.sin_port));
                if (client_fd < 0){
                    perror("accept");
                    break;;
                }

                //add session
                void* ptr_connection = m_accept_handler(client_fd);

                fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL)|O_NONBLOCK);
                epoll_event ev;
                ev.events = EPOLLIN |EPOLLET;
                ev.data.ptr = ptr_connection; 

                if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                    perror("epoll_ctl");
                    return -1;
                }
            }
            continue;
        } else {
            ZConnection* connection = (ZConnection*)events[i].data.ptr;
            if(!connection || connection->status() == ZCS_CLOSE) {
                continue;		
            }

            if (events[i].events & EPOLLIN) {
                int n = connection->on_network_read();
                if(n==0){
                    closelist.push_back(connection);
                } 
                else if(n>0){
                    set_write(events[i], true);
                } else {
                    zlog.log("epoll read failed");
                }

                continue;
            }

            if (events[i].events & EPOLLOUT) {
                int n = connection->on_network_write();
                if(n==0){
                    closelist.push_back(connection);
                }
                else if(n > 0) {
                    zlog.log("epoll write [fd:%d] len=%d", connection->get_fd(), n);
                    set_read(events[i], true);
                } else {
                    zlog.log("epoll write failed");
                }

                continue;
            }

            if (events[i].events & (EPOLLERR|EPOLLHUP|EPOLLPRI)) {
                zlog.log("EPOLLERR|EPOLLHUP|EPOLLPRI: client linkdown");
                close(connection->get_fd());
                continue;
            }
        }
    } //loop for

    for(std::vector<ZConnection*>::iterator it = closelist.begin();
            it != closelist.end();
            ++it) {
        del((*it)->get_fd());
        close((*it)->get_fd());
        (*it)->on_close();
    }

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

