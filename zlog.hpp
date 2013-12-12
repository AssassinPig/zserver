#ifndef _ZLOG_H__ 
#define _ZLOG_H__
#include "com_inc.hpp"
#include <stdarg.h>

#define ZLOG_INIT(filename) ZLog* zlog=new ZLog(#filename);
#define ZDEBUG_LOG zlog->log

class ZLog 
{
    public:
        ZLog(const char* logfilename = NULL); 
        ~ZLog(); 

        void log(const char* buf, ...);
    protected:
        FILE *m_fp;
};

extern ZLog* zlog;
#endif //_ZSERVER_H__
