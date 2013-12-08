#include "zthread.hpp"
#include "com_inc.hpp" 

void* thread_fun(void* param)
{
   ZThread* thread = (ZThread*)param; 
   if(thread) {
        thread->ThreadFun(thread->GetThreadParam());
   }

   return NULL;
}

ZThread::ZThread(): m_status(ZThread::zthread_status_unknown), m_threadparam(NULL) 
{
}

ZThread::~ZThread()
{
    if(m_status != zthread_status_termined){
        Exit();
    }
}

int ZThread::Startup(void* param)
{
   m_status = zthread_status_idle; 
   m_threadparam = param;
   int ret=-1;
   if( (ret=pthread_create(&m_threadid, NULL, thread_fun, (void*)this)) < 0) {
        perror("zthread start thread failed");
   }
    return ret;
}

int ZThread::Join()
{
    int ret=-1;
    if( (ret = pthread_join(m_threadid, NULL)) < 0) {
        perror("zthread join failed");
    }
    return ret;
}

int ZThread::Detach()
{
    return pthread_detach(m_threadid); 
}

int ZThread::Suspend()
{
    //to be continue
    return -1;
}

int ZThread::Exit()
{
    m_status = zthread_status_termined;
    int ret = 0;
    if( (ret = pthread_join(m_threadid, NULL)) < 0) {
        perror("zthread exit join failed");
    }
    return ret;
}

ZThread::zthread_status ZThread::Status()
{
    return m_status;
}

void* ZThread::GetThreadParam()
{
    return m_threadparam;
}
