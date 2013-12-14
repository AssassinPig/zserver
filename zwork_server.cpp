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
    g_ModuleContainer = new ZModuleContainer;
    g_ModuleContainer->init();
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
    //ZConnection* connection = (ZConnection*)epoll->add_fd(m_socket->GetFD());
    //ZStream& outstream = connection->get_outstream();
    //int times = 0;
    //outstream.input((char*)&times, sizeof(int));
    
    m_thread = new NotifyStatusThread;
    m_thread->Startup(this);  

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZWorkServer::loop()
{
    return ZServer::loop();
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

int ZWorkServer::NotifyStatusThread::ThreadFun(void* param)
{
    ZWorkServer* server = (ZWorkServer*)param; 
    ZSocket* socket = server->GetSocket();
    //ZFcntl(socket->GetFD(), F_SETFL, fcntl(socket->GetFD(), F_GETFL)|O_NONBLOCK);

    int i=0;
    while(Status() == ZThread::zthread_status_idle) {
        int thissend = ZWrite(socket->GetFD(), (char*)&i, sizeof(int)); 
        ZDEBUG_LOG("notify status thread send times:%d, thissend:%d", i, thissend);

        int thisrecv = ZRead(socket->GetFD(), (char*)&i, sizeof(int)); 
        ZDEBUG_LOG("notify status thread recv times:%d, thisread:%d", i, thisrecv);
        sleep(5);
    }

    ZClose(socket->GetFD());
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZSocket* ZWorkServer::GetSocket()
{
    return m_socket;
}
