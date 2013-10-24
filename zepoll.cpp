#include "zepoll.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "com_inc.hpp"
#include "zlog.hpp"
#include "zworld.hpp"
#include "zmutex.hpp"

int epoll_thread_fun(void* data)
{
	ZEpoll* module = (ZEpoll*)data;
	while(1)
	{
		if(module->status() == ZMT_EXIT)
		{
			break;				
		}
		
		module->loop();
	}

	//clean 
	zlog.log("epoll thread exit then close epoll");
	module->shutdown(); 
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

//ZNETWORK_MODUL_INIT
//bool ZEpoll::ms_exit = false;
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

    m_ev.events = EPOLLIN;
    m_ev.data.fd = m_listener;
    if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, m_listener, &m_ev) == -1) {
        perror("epoll_ctl");
        return -1;
    }

	//boost::function<int(void*)> fun = boost::bind(epoll_thread_fun, (void*)this);
	m_thread = make_thread<int(void*)>(epoll_thread_fun, (void*)this);

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::shutdown()
{
	zlog.log("epoll shutdown");
	//ms_exit = true;
    close(m_epoll);
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::exit()
{
	zlog.log("epoll exit");
	m_status = ZMT_EXIT;
    //close(m_epoll);
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZEpoll::ready_process()
{
	//static struct epoll_event events[MAX_EPOLL_EVENT];
    //int nfds;
//   m_nfds = epoll_wait(m_epoll, m_events, MAX_EPOLL_EVENT, 1000);
//	zlog.log("ready_process with nfds[%d]", m_nfds);
}

int ZEpoll::process_except() 
{
}

int ZEpoll::process_input() 
{
//    for (int i = 0; i < m_nfds; ++i) {
//    	if (m_events[i].data.fd == m_listener) {
//		}
//	}
}

int ZEpoll::process_output()
{
//    for (int i = 0; i < m_nfds; ++i) { 
//	
//	}
}

void ZEpoll::add_send_event(int fd)
{
    epoll_event ev;
	ev.events = EPOLLOUT|EPOLLET;
	ev.data.fd = fd;

	if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &m_ev) == -1) {
		perror("add send event epoll_ctl");
		return;
	}
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
				while( client_fd = accept(m_listener, (struct sockaddr *)&in, &len)) {
					printf("accpet client %s:%d\n", inet_ntoa(in.sin_addr), ntohs(in.sin_port));
					if (client_fd < 0){
						perror("accept");
						continue;
					}
					
					//add session
					gWorld.add_session(client_fd);
						
					zlog.log("accpet client %s:%d", inet_ntoa(in.sin_addr), ntohs(in.sin_port));
					fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL)|O_NONBLOCK);
					m_ev.events = EPOLLIN|EPOLLOUT|EPOLLET;
					m_ev.data.fd = client_fd;
					if (epoll_ctl(m_epoll, EPOLL_CTL_ADD, client_fd, &m_ev) == -1) {
						perror("epoll_ctl");
						return -1;
					}
				}
            } else {
                if (events[i].events & EPOLLIN) {
                    //printf("EPOLLIN:\n");
                    char buf[MAX_RECV];
                    memset(buf, 0, sizeof(buf));
                    int n = recv(events[i].data.fd, buf, sizeof(buf), 0);
                    if (n > 0) {
						gWorld.dispatch(buf, n, events[i].data.fd);
                    } else if (n == 0) {
                        printf("client linkdown\n");
                        close(events[i].data.fd);
						
						//kick player
						//gWorld.kick_player();
                        continue;
                    } else { 
                        if (errno == EAGAIN || errno == EINTR) {
                            continue;
                        } else {
                            printf("client linkdown\n");
                            close(events[i].data.fd);

							//kick player
							//gWorld.kick_player();
                            continue;
                        }
                    }
                }

                if (events[i].events & EPOLLOUT) {
                    //printf("EPOLLOUT:\n");
					/*
						packet* packet = world->get_client_response(fd);
						packet->get_data();
						
						int n = send(events[i].data.fd, buf, strlen(buf), 0);
						world->finish_send_packet(seq);
					*/

                char buf[MAX_SEND];
                memset(buf, 0, sizeof(buf));
				sprintf(buf, "send\n");
				int n = send(events[i].data.fd, buf, strlen(buf), 0);

					if (n > 0) {
						printf("server send_size:%d\n", n);
						//puts(buf);
					} else if (n == 0) {
                        printf("client linkdown\n");
                        close(events[i].data.fd);
                        continue;
					} else {
                        if (errno == EAGAIN || errno == EINTR) {
                            continue;
                        } else {
                            printf("client linkdown\n");
                            close(events[i].data.fd);
                            continue;
                        }
					}
                }

                if (events[i].events & (EPOLLERR|EPOLLHUP|EPOLLPRI)) {
                    printf("EPOLLERR|EPOLLHUP|EPOLLPRI: client linkdown\n");
                    zlog.log("EPOLLERR|EPOLLHUP|EPOLLPRI: client linkdown");
                    close(events[i].data.fd);
                    continue;
                }
            }
        } //loop for
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

