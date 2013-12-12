#ifndef _ZWORK_SERVER_H__
#define _ZWORK_SERVER_H__

#include "zserver.hpp"

class ZConnection;
class ZModule;
class ZSocket;

class ZWorkServer : public ZServer
{
    public:
        ZWorkServer();

        virtual int init();
        virtual int startup(const char* bind_ip, int port);
        virtual int loop();
        virtual int exit();

	ZConnection* accept_client(int fd); 

    private:
        ZModule* m_network;
        ZSocket* m_socket;
};

#endif //_ZWORK_SERVER_H__
