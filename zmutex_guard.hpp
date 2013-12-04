#ifndef _ZMUTEX_GURAD_H__ 
#define _ZMUTEX_GURAD_H__

#include "zmutex.hpp" 

class ZMutexGuard
{
    public:
        ZMutexGuard()
        {
            m_mutex.Lock();	
        }

        ~ZMutexGuard()
        {
            m_mutex.Unlock();	
        }

    private:
        ZMutex m_mutex;
};

#endif//_ZMUTEX_GURAD_H__ 
