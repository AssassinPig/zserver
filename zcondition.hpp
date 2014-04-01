#ifndef _ZCONDITION_H__ 
#define _ZCONDITION_H__

#include <pthread.h>

#include "zmutex.hpp"
#include "zmutex_guard.hpp"

class ZCondition
{
    public:
        ZCondition(const ZMutex& mutex)
            : m_mutex(mutex)
        {
            m_cond = PTHREAD_COND_INITIALIZER; 
        }

        ~ZCondition()
        {
           pthread_cond_destory(&m_cond); 
        }

        void Wait()
        {
           pthread_cond_wait(&m_cond, m_mutex.GetRawMutex()); 
        }

        void Notify()
        {
            pthread_cond_signal(&m_cond);
        }

        void NotifyAll()
        {
           pthread_cond_broadcast(&m_cond);  
        }

    private:
        pthread_cond_t m_cond;
        ZMutex& m_mutex;
};

#endif //_ZCONDITION_H__
