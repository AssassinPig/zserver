#ifndef _ZPROXY_SERVER_H__
#define _ZPROXY_SERVER_H__

#include "zserver.hpp"
class ZConnection;

class ZProxyServer : public ZServer
{
    public:
        ZProxyServer();

        virtual int init();
        virtual int startup(const char* bind_ip, int port);
        virtual int loop();
        virtual int exit();

	ZConnection* accept_client(int fd); 
    private:
        ZModule* m_network;
};

#endif//_ZPROXY_SERVER_H__ 
