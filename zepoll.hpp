#ifndef _ZEPOLL_H__
#define _ZEPOLL_H__

#include "com_inc.hpp"
#include "com_def.hpp"
#include "zthread_module.hpp"

class ZEpoll : public ZModule
{
public:
    ZEpoll();
    ~ZEpoll();
    virtual int init();
    virtual int startup();
    virtual int shutdown();
	virtual int exit();
	
	virtual int ready_process();
	virtual int process_input();
	virtual int process_output();
	virtual int process_except();
	
public:
    virtual int loop();

private:
    int m_epoll;
    int m_listener;
    epoll_event m_ev;
    struct epoll_event m_events[MAX_EPOLL_EVENT];
    int m_nfds;
};
#endif //_ZEPOLL_H__
