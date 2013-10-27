#include "zserver.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"
#include "zpacket.hpp"
#include "zworld.hpp"
#include "zthread_module.hpp"

#include<signal.h>
#include "zepoll.hpp"

ZLog zlog;
bool ZServer::m_active = false;

ZServer::ZServer()
{
	m_active = false;
}

int ZServer::init()
{   
  	set_signal();
	ZPacket_factory::init();
	m_active = true;
	g_ModuleContainer = new ZModuleContainer;	
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::set_signal()
{
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	act.sa_flags &= ~SA_RESETHAND;
	sigaction(SIGPIPE, &act, NULL);
	
	signal(SIGINT, ZServer::shutdown);
	signal(SIGKILL, ZServer::shutdown);
	signal(SIGQUIT, ZServer::shutdown);
	signal(SIGTERM, ZServer::shutdown);
	
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::startup()
{
	zlog.log("server startup");

	g_ModuleContainer->startup();
	ZEpoll* epoll = (ZEpoll*)g_ModuleContainer->get_network_module();

	ZEpoll::accept_handler handler = boost::bind(&ZServer::accept_client, this, _1);
	epoll->set_accept_handler(handler);

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

bool ZServer::is_active()
{
	return m_active;
}

int ZServer::loop()
{                  
	while(is_active()){
		zlog.log("server loop");
		//g_ModuleContainer->loop();
		ZEpoll* epoll = (ZEpoll*)g_ModuleContainer->get_network_module();
		epoll->loop();
		//sleep(100);	
	}

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZServer::shutdown(int sig_num)
{
	g_ModuleContainer->exit();
	m_active = false;
	zlog.log("server shutdown[sig:%d]", sig_num);
}

ZConnection* ZServer::accept_client(int fd)
{
	zlog.log("server accept [fd:%d]", fd);
	ZClient* client = new ZClient(this);
	m_clients.push_back(client);
	m_sessions[fd] = client;	
	return  client->get_connection();
    //FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::close_client()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::load_config()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZClient* ZServer::get_client(int fd)
{
	return m_sessions[fd];	
}
