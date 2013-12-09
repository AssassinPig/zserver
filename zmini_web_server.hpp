#ifndef _ZMINI_WEB_SERVER_H__ 
#define _ZMINI_WEB_SERVER_H__

#include "zconfig.hpp"
#include "zserver.hpp"
#include "zthread.hpp"
class ZSocket;
class ZMiniWebServer : public ZServer
{
    public:
        ZMiniWebServer(int child_num=5);
        ~ZMiniWebServer();
       
        enum child_process_status {
            child_process_status_available = 0,
            child_process_status_busy,
            child_process_status_terminated,
            child_process_status_max,
        };

        struct child_process_info {
            pid_t child_pid;
            int sockfd[2];
        };

        class AcceptThread : public ZThread 
        {
            public:
                virtual int ThreadFun(void* param);
            private:
            
        }; 

        virtual	int init();
        virtual	int startup(const char* bind_ip, int port);
        virtual	int loop();
        virtual int exit();

        child_process_info* GetChildInfo();
        ZSocket* GetSocket();
        sem_t* GetChildSem();
        int GetChildNum();
        child_process_status* GetChildStatus();

    private:
        child_process_info* m_childprocess;     
        child_process_status* m_childstatus;
        sem_t* m_childmutex; 
        int m_childnum;
        ZThread* m_thread;
        ZSocket* m_listensocket;  
};
#endif //_ZMINI_WEB_SERVER_H__
