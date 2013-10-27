#include "zepoll.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "com_inc.hpp"
#include "zlog.hpp"
#include "zworld.hpp"
#include "zmutex.hpp"

int epoll_thread_fun(void* data)
{
	ZEpoll* epoll= (ZEpoll*)data;
	while(1)
	{
		if(epoll->status() == ZMT_EXIT)
		{
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

    m_listener = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(m_listener, F_SETFL, fcntl(m_listener, F_GETFL)|O_NONBLOCK);

    sockaddr_in ip;
    ip.sin_family = AF_INET;
	//bind ip and port
    ip.sin_addr.s_addr = inet_addr(BIND_IP);
    ip.sin_port = htons(BIND_PORT);

    int f = 1;
    if (ERR == setsockopt(m_listener, SOL_SOCKET, SO_REUSEADDR, (char*)&f, sizeof(f))) {
        perror("setsockopt");    
        return -1;
    }

    if (-1 == bind(m_listener, (sockaddr*)&ip, sizeof(ip))) {
        perror("bind");
        return -1;
    }

    if (-1 == listen(m_listener, LISTENER_MAX)) {
        perror("listen");
        return -1;
    }

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = m_listener;
    if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, m_listener, &ev) == -1) {
        perror("epoll_ctl");
        return -1;
    }

	//m_thread = make_thread<int(void*)>(epoll_thread_fun, (void*)this);
	zlog.log("epoll startup");

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
	m_status = ZMT_EXIT;
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZEpoll::set_read(int fd)
{
    epoll_event ev;
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = fd;

	if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &ev) == -1) {
		perror("add read event epoll_ctl");
		return;
	}
}

void ZEpoll::set_write(int fd)
{
    epoll_event ev;
	ev.events = EPOLLOUT|EPOLLET;
	ev.data.fd = fd;

	if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &ev) == -1) {
		perror("add send event epoll_ctl");
		return;
	}
}

void ZEpoll::set_accept_handler(accept_handler handler) { 
	m_accept_handler = handler;
}

int ZEpoll::loop()
{
        zlog.log("zepoll::loop()");
        static struct epoll_event events[MAX_EPOLL_EVENT];
        int nfds;
        nfds = epoll_wait(m_epoll, events, MAX_EPOLL_EVENT, 1000);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == m_listener) {
                sockaddr_in in;
                socklen_t len;
                len = sizeof(in);

                int client_fd;
				while( (client_fd = accept(m_listener, (struct sockaddr *)&in, &len)) > 0) {
					//printf("accpet client %s:%d\n", inet_ntoa(in.sin_addr), ntohs(in.sin_port));
					zlog.log("accpet client %s:%d", inet_ntoa(in.sin_addr), ntohs(in.sin_port));
					if (client_fd < 0){
						perror("accept");
						break;;
					}
					
					//add session
					void* connection =  m_accept_handler(client_fd);

					fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL)|O_NONBLOCK);
					epoll_event ev;
					ev.events = EPOLLIN|EPOLLOUT|EPOLLET;
					ev.data.fd = client_fd;
					ev.data.ptr = (void*)connection; 

					if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
						perror("epoll_ctl");
						return -1;
					}
				}
            } else {
                if (events[i].events & EPOLLIN) {
                    //char buf[MAX_RECV];
                    //memset(buf, 0, sizeof(buf));
                    //int n = recv(events[i].data.fd, buf, sizeof(buf), 0);
					ZConnection* connection = (ZConnection*)events[i].data.ptr;
					int n = connection->on_network_read();

                   // if (n > 0) {
				   // 	//gWorld.dispatch(buf, n, events[i].data.fd);
                   // } else if (n == 0) {
                   //     //printf("client linkdown\n");
                   //     close(events[i].data.fd);
				   // 	//kick player
				   // 	//gWorld.kick_player();
                   //     continue;
                   // } else { 
                   //     if (errno == EAGAIN || errno == EINTR) {
                   //         continue;
                   //     } else {
                   //         //printf("client linkdown\n");
                   //         close(events[i].data.fd);

				   // 		//kick player
				   // 		//gWorld.kick_player();
                   //         continue;
                   //     }
                   // }
                }

                if (events[i].events & EPOLLOUT) {
					ZConnection* connection = (ZConnection*)events[i].data.ptr;
					int n = connection->on_network_write();
				//	char buf[MAX_SEND];
				//	memset(buf, 0, sizeof(buf));
				//	sprintf(buf, "send\n");
				//	int n = send(events[i].data.fd, buf, strlen(buf), 0);

				//	if (n > 0) {
				//		//printf("server send_size:%d\n", n);
				//	} else if (n == 0) {
                //        //printf("client linkdown\n");
                //        close(events[i].data.fd);
                //        continue;
				//	} else {
                //        if (errno == EAGAIN || errno == EINTR) {
                //            continue;
                //        } else {
                //            printf("client linkdown\n");
                //            close(events[i].data.fd);
                //            continue;
                //        }
				//	}
                }

                if (events[i].events & (EPOLLERR|EPOLLHUP|EPOLLPRI)) {
                    zlog.log("EPOLLERR|EPOLLHUP|EPOLLPRI: client linkdown");
                    close(events[i].data.fd);
                    continue;
                }
            }
        } //loop for
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

