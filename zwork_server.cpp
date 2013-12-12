#include "zwork_server.hpp"
#include "zwork_client.hpp"
#include "com_macro.hpp"
#include "zsocket.hpp"
#include "zsocket_util.hpp"
#include "zlog.hpp"

ZWorkServer::ZWorkServer()
{

}

int ZWorkServer::init()
{
    ZServer::init();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZWorkServer::startup(const char* bind_ip, int port)
{
    g_ModuleContainer->startup();

    m_network = new ZEpoll;
    ZEpoll* epoll = (ZEpoll*)m_network;
    
    ZEpoll::accept_handler handler = boost::bind(&ZWorkServer::accept_client, this, _1);
    epoll->set_accept_handler(handler);
    epoll->set_sockaddr(bind_ip, port);
    m_network->startup();

    m_socket = new ZSocket;
    m_socket->AttachFD(ZTCPSocket());
    m_socket->Connect(bind_ip, 99998);
    epoll->add_fd(m_socket->GetFD());

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZWorkServer::loop()
{
    while(is_active()){
        ZDEBUG_LOG("server loop");
        g_ModuleContainer->loop();
        ZEpoll* epoll = (ZEpoll*)m_network;
        epoll->loop();
    }

    exit();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZWorkServer::exit()
{
    m_socket->Close();
    ZServer::exit();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZConnection* ZWorkServer::accept_client(int fd)
{
    ZDEBUG_LOG("server accept [fd:%d]", fd);

    ZClient* client = new ZWorkClient(this); 
    client->set_connection(fd);
    m_clients.push_back(client);
    m_sessions[fd] = client;	
    return  client->get_connection();
}
