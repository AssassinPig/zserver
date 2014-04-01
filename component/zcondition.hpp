#ifndef _ZCONDITION_H__ 
#define _ZCONDITION_H__

#include <pthread.h>

class ZCondition
{
    public:
        ZCondition(const ZMutex& mutex):m_mutex(mutex)
        {
            m_cond = PTHREAD_COND_INITIALIZER; 
        }
        
        ~ZCondition()
        {
        
        }

        void Wait()
        {

        }

        void Signal()
        {
        
        }

    private:
        pthread_cond_t m_cond;
        ZMutex& m_mutex;
};

#endif //_ZCONDITION_H__
