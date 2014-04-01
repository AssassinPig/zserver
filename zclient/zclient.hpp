#ifndef _ZCLIENT_H__ 
#define _ZCLIENT_H__

class ZSocket;

class ZClient
{
    public:
        ZClient();
        virtual ~ZClient();

        int Init();
        int Startup(const char* ip, int port); 

        int Connect();
        int Disconnect();

        int Exit();
        int Loop();

    private:
        ZSocket* m_socket;
};

#endif// 
