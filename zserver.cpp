#include "zserver.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"
#include "zpacket.hpp"
#include "zthread_module.hpp"

#include "zepoll.hpp"

ZLog zlog;
bool ZServer::m_active = false;

ZServer::ZServer()
{
    m_active = false;
}

ZServer::~ZServer()
{

}

int ZServer::init()
{   
    set_signal();
    //ZPacket_factory::init();
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

int ZServer::startup(const char* bind_ip, int port)
{
    zlog.log("server startup ip:%s port:%d", bind_ip, port);

    g_ModuleContainer->startup();

    m_network = new ZEpoll;
    ZEpoll* epoll = (ZEpoll*)m_network;
    
    ZEpoll::accept_handler handler = boost::bind(&ZServer::accept_client, this, _1);
    epoll->set_accept_handler(handler);
    epoll->set_sockaddr(bind_ip, port);
    m_network->startup();

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

bool ZServer::is_active()
{
    return m_active;
}

int ZServer::exit()
{
    m_network->exit();
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::loop()
{                  
    while(is_active()){
        zlog.log("server loop");
        g_ModuleContainer->loop();
        ZEpoll* epoll = (ZEpoll*)m_network;
        epoll->loop();
    }

    exit();

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZServer::shutdown(int sig_num)
{
    m_active = false;
    g_ModuleContainer->exit();
    zlog.log("server shutdown[sig:%d]", sig_num);
}

ZConnection* ZServer::accept_client(int fd)
{
    zlog.log("server accept [fd:%d]", fd);
    ZClient* client = new ZClient(this);
    client->set_connection(fd);
    m_clients.push_back(client);
    m_sessions[fd] = client;	
    return  client->get_connection();
}

int ZServer::close_client(ZClient* client)
{
    for(CLIENT_LIST::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
        if((*it) == client) {
            delete *it;
            m_clients.erase(it);	
            FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
        }
    }
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
