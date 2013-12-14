#ifndef _ZPROXY_SERVER_H__
#define _ZPROXY_SERVER_H__

#include "zserver.hpp"
#include "zthread.hpp"
class ZConnection;
class ZSocket;
class ZThread;

class ZProxyServer : public ZServer
{
    public:
        ZProxyServer();

        virtual int init();
        virtual int startup(const char* bind_ip, int port);
        virtual int loop();
        virtual int exit();

	ZConnection* accept_client(int fd); 
        
        class NotifyStatusThread : public ZThread
        {
            public:
                virtual int ThreadFun(void* param);
            private:

        };

        ZSocket* GetSocket();

    private:
        ZThread* m_thread;
        ZSocket* m_socket;
};

#endif//_ZPROXY_SERVER_H__ 
