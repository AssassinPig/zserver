#include "zproxy_server.hpp"
#include "com_macro.hpp"
#include "zconnection.hpp"

#include "zthread_module.hpp"

#include "zlog.hpp"
#include "zepoll.hpp"
#include "zproxy_client.hpp"

ZProxyServer::ZProxyServer()
{
}

int ZProxyServer::init()
{
    ZServer::init();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZProxyServer::startup(const char* bind_ip, int port)
{
    ZDEBUG_LOG("server startup ip:%s port:%d", bind_ip, port);

    g_ModuleContainer->startup();

    m_network = new ZEpoll;
    ZEpoll* epoll = (ZEpoll*)m_network;
    
    ZEpoll::accept_handler handler = boost::bind(&ZProxyServer::accept_client, this, _1);
    epoll->set_accept_handler(handler);
    epoll->set_sockaddr(bind_ip, port);
    m_network->startup();

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZProxyServer::loop()
{
    return ZServer::loop();
}

int ZProxyServer::exit()
{
    ZServer::exit();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZConnection* ZProxyServer::accept_client(int fd)
{
    ZDEBUG_LOG("server accept [fd:%d]", fd);

    ZClient* client = new ZProxyClient(this); 
    client->set_connection(fd);
    m_clients.push_back(client);
    m_sessions[fd] = client;	
    return  client->get_connection();
}

ZSocket* ZProxyServer::GetSocket()
{
    return m_socket;
}

int ZProxyServer::NotifyStatusThread::ThreadFun(void* param)
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}
