#include "zlog.hpp"
#include <time.h>
#include <assert.h>

FILE* ZLog::ms_fp = NULL;

ZLog::ZLog()
{
	ms_fp = NULL;

	ms_fp = fopen("log.txt", "a");
	assert(ms_fp);
}

ZLog::~ZLog()
{
	if (ms_fp) {
		fclose(ms_fp);
	}
}

void ZLog::log(char* buf, ...)
{
	assert(ms_fp);

	char tmp_buf[1024], tmp_buf2[1024];
	va_list args;
	//ms_fp;
	
	time_t tval;
	time(&tval);
	tm* curr_time = localtime(&tval);
	
	va_start(args, buf);
	vsprintf(tmp_buf, buf, args);
	va_end(args);
	
	sprintf(tmp_buf2, "[%d/%02d/%02d %02d:%02d:%02d]%s\n",
	curr_time->tm_year+1900,
	curr_time->tm_mon+1,
	curr_time->tm_mday,
	curr_time->tm_hour,
	curr_time->tm_min,
	curr_time->tm_sec,
	tmp_buf
	);
	
	fprintf(ms_fp, "%s", tmp_buf2);
	fflush(ms_fp);
}

//no need any more
void log(char * buf, ...)
{
	char tmp_buf[1024], tmp_buf2[1024];
	va_list args;
	FILE *fp;
	
	time_t tval;
	time(&tval);
	tm* curr_time = localtime(&tval);
	
	fp = fopen("log.txt", "a");
	if(!fp) {
		return;
	}
	
	va_start(args, buf);
	vsprintf(tmp_buf, buf, args);
	va_end(args);
	
	sprintf(tmp_buf2, "[%d/%02d/%02d %02d:%02d:%02d]%s\n",
	curr_time->tm_year+1900,
	curr_time->tm_mon+1,
	curr_time->tm_mday,
	curr_time->tm_hour,
	curr_time->tm_min,
	curr_time->tm_sec,
	tmp_buf
	);
	
	//strcpy(tmp_buf, tmp_buf2);
	strncpy(tmp_buf, tmp_buf2, 1024);
	fprintf(fp, "%s", tmp_buf);
	
	fclose(fp);
}
