#ifndef _ZSTREAM_H__
#define _ZSTREAM_H__

#define MAX_STREAM_LEN 1024*10

#include <stdint.h>
#include <assert.h>

class ZStream
{
    public:
        ZStream();
        ~ZStream();

        int malloc(uint32_t len = MAX_STREAM_LEN);
        int input(char* data, uint32_t len);
        int output(char* out, uint32_t len);
        uint32_t length();
        uint32_t capacity();
        void print_data();
        char* get_data();

        void cleanup();	

    private:
        uint32_t m_tail;
        uint32_t m_head;	
        uint32_t m_capacity;
        char* m_data; 
};

#endif //_ZSTREAM_H__
