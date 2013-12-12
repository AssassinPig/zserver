#include "zlog.hpp"
#include <time.h>
#include <assert.h>

ZLog::ZLog(const char* logfilename)
{
    m_fp = NULL;

    if(!logfilename)
        m_fp = fopen("log.txt", "a");
    else 
        m_fp = fopen(logfilename, "a");
    assert(m_fp);
}

ZLog::~ZLog()
{
    if (m_fp) {
        fclose(m_fp);
    }
}

void ZLog::log(const char* buf, ...)
{
    assert(m_fp);

    char tmp_buf[1024], tmp_buf2[1024];
    va_list args;

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

    fprintf(m_fp, "%s", tmp_buf2);
    fflush(m_fp);
}

