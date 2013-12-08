#ifndef _ZTHREAD_H__ 
#define _ZTHREAD_H__

#include <pthread.h>

class ZThread 
{
public:

    enum zthread_status {
        zthread_status_unknown = 0, 
        zthread_status_idle , 
        zthread_status_halt, 
        zthread_status_termined, 
        zthread_status_max, 
    };

    ZThread();
    ~ZThread();

    int Startup(void* param=NULL);
    int Join();
    int Detach();
    int Suspend();
    int Exit();

    virtual int ThreadFun(void* param) = 0; 

    zthread_status Status(); 
    void* GetThreadParam();

protected:
    zthread_status m_status;
    pthread_t m_threadid;
    void* m_threadparam;
private:
};

#endif
