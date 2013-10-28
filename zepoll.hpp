#ifndef _ZEPOLL_H__
#define _ZEPOLL_H__

#include "com_inc.hpp"
#include "com_def.hpp"
#include "zthread_module.hpp"
#include "zconnection.hpp"

class ZEpoll : public ZModule
{
public:
	typedef boost::function<ZConnection* (int)> accept_handler;

//	typedef boost::function<void (int, bool)> set_read_handler;
//	typedef boost::function<void (int, bool)> set_write_handler;

    ZEpoll();
    ~ZEpoll();
    virtual int init();
    virtual int startup();
    virtual int shutdown();
	virtual int exit();

	void set_read(epoll_event& event, bool flag);
	void set_write(epoll_event& event, bool flag);
	void del(int fd);

	void set_accept_handler(accept_handler handler);  
//	void set_read_handler(set_read_handler handler);  
//	void set_write_handler(set_write_handler handler);  

public:
    virtual int loop();

private:
    int m_epoll;		//epoll fd
    int m_listener;		//listen sock fd
	accept_handler m_accept_handler;
};
#endif //_ZEPOLL_H__
