#ifndef _ZLOG_H__ 
#define _ZLOG_H__
#include "com_inc.hpp"
#include <stdarg.h>

#define zlog(text) zlog::log(text)

class ZLog
{
public:
	ZLog(); 
	~ZLog(); 
	static void log(const char* buf, ...);
protected:
	static FILE *ms_fp;
};

//no need any more
//void log(char * buf, ...);

extern ZLog zlog;
#endif //_ZSERVER_H__
