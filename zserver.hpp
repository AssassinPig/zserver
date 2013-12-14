#ifndef _ZSERVER_H__
#define _ZSERVER_H__

#include "zthread_module.hpp"
#include "zepoll.hpp"
#include "zclient.hpp"

class ZModule;

class ZServer
{
public:
	ZServer();
        virtual ~ZServer();

        virtual int init();
        virtual int startup(const char* bind_ip, int port);
        virtual int loop();
        virtual int exit();

	bool is_active();

	static void shutdown(int sig_num);

	ZConnection* accept_client(int fd); 
	int close_client(ZClient* client);
	int load_config();

	//lock the client 
	ZClient* get_client(int fd);

protected:
	int set_signal();

protected:
	static bool m_active;
	typedef std::map<ZFD_T, ZClient*> SESSION_MAP;
	typedef std::vector<ZClient*> CLIENT_LIST;
	CLIENT_LIST	m_clients;
	SESSION_MAP     m_sessions;

        ZModule* m_network;
};
#endif //_ZSERVER_H_
