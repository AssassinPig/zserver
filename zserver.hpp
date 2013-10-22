#ifndef _ZSERVER_H__
#define _ZSERVER_H__

#include "zthread_module.hpp"
#include "zepoll.hpp"

class ZServer
{
public:
	ZServer();
	int init();
	int startup();
	int base_loop();
	bool is_active();
	int process_input();
	int process_output();
	int process_cmd();

	int uninit();
	static void shutdown(int sig_num);

	static void recv_thread_fn(void* args);
	static void send_thread_fn(void* args); 
	static void admin_thread_fn(void* args);
protected:
	int set_signal();
	int start_thread();  
protected:
	static ZEpoll m_epoll;
	pthread_t m_admin_tid;
	pthread_t recv_thd_tid;
	pthread_t send_thd_tid;

private:
	int load_config();
	static bool ms_active;

};
#endif //_ZSERVER_H_
