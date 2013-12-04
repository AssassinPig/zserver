#ifndef _ZMUTEX_H__
#define _ZMUTEX_H__

#include <pthread.h>

class ZMutex 
{
    public:
        ZMutex():m_holder(0)
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

        ~ZMutex()
        {
            assert(m_holder == 0);
            pthread_mutex_destroy(&m_mutex);
        }

        void AssaginHolder()
        {
            m_holder = pthread_self();
        }

        void Lock()
        {
            pthread_mutex_lock(&m_mutex);	
        }

        void Unlock()
        {
            pthread_mutex_unlock(&m_mutex);	
        }

    private:
        pthread_mutex_t m_mutex;
        pid_t			m_holder;
};

#endif //_ZMUTEX_H__
