#include "zstream.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

ZStream::ZStream()
{
    m_tail = 0;
    m_head = 0;	

    m_capacity = 0;
    m_data = NULL; 
}

ZStream::~ZStream()
{
    if (m_data) {
        delete  [] m_data;
    }
}

int ZStream::malloc(uint32_t len)
{
    assert(len);
    uint32_t size = len > MAX_STREAM_LEN ? MAX_STREAM_LEN : len;
    m_capacity = size;
    m_data = new char[size]; 
    memset(m_data, 0, size); 
    return size;
}

int ZStream::input(char* data, uint32_t len)
{
    assert(data != NULL && len != 0);
    if (m_capacity == 0) {
        return 0;
    }

    if (m_head > m_tail) {
        //tail will never equal head
        if (m_head - m_tail + 1 == m_capacity) {
            return 0;			
        }				

        uint32_t empty = m_capacity - (m_head - m_tail);
        //whether take all
        if (empty >= len) {
            memcpy(m_data+m_head, data, len);	
            m_head += len;
            m_head %= m_capacity;
            return len;
        } else {
            uint32_t part_len1 = m_capacity - 1 - m_head;
            uint32_t part_len2 = m_tail;

            memcpy(m_data+m_head, data, part_len1);	
            m_head += part_len1;
            m_head %= m_capacity;
            if (part_len2) {
                memcpy(m_data+m_head, data + part_len1, part_len2);	
            }

            m_head += part_len2;
            m_head %= m_capacity;

            return part_len1 + part_len2;
        }
    } else if (m_head == m_tail) {
        uint32_t size = m_capacity - 1 < len ? m_capacity - 1 : len;
        memcpy(m_data, data, size);		
        m_tail = 0;
        m_head = size;
        return size;
    } else {
        //tail will never equal head
        if (m_tail - m_head + 1 == m_capacity) {
            return 0;
        }	

        //cache not enough
        uint32_t empty = m_capacity - (m_tail - m_head);
        if (empty < len) {
            uint32_t part_len1 = m_capacity - m_tail - 1;
            uint32_t part_len2 = m_tail;

            memcpy(m_data+m_head, data, part_len1);
            if (part_len2 != 0) {
                memcpy(m_data, data + part_len1, part_len2);
            } 

            m_head = m_tail - 1;
            return part_len1 + part_len2;
        } else {
            //this case include first time condition when tail eq head
            uint32_t part_len1 = m_capacity - m_tail - 1;
            uint32_t part_len2 = len - part_len1 > 0 ? len - part_len1 : 0;
            memcpy(m_data+m_head, data, part_len1); 

            if (part_len2 != 0) {
                memcpy(m_data, data+part_len1, part_len2);
            }

            m_head += part_len1;
            m_head += part_len2;
            m_head %= m_capacity;	

            return len;
        }
    }
}

int ZStream::output(char* out, uint32_t len)
{
    assert(out != NULL && len);
    if (m_head > m_tail) {
        //out enough
        if (m_head - m_tail < len) {
            uint32_t size = m_head-m_tail;
            memcpy(out, m_data+m_tail, size);
            m_tail = m_head;
            return size;
        } else {
            memcpy(out, m_data+m_tail, len);
            m_tail += len;
            m_tail %= m_capacity;
            return len;
        }		
    } else if(m_tail > m_head) {
        uint32_t part_len1 = m_capacity - m_tail - 1;	
        uint32_t part_len2 = m_head + 1;
        if (part_len1 > len) {
            memcpy(out, m_data+m_tail, part_len1);
            m_tail += part_len1;
            m_tail %= m_capacity;
            return len;	
        } 

        if (part_len2 >= len - part_len1) {
            memcpy(out, m_data+m_tail, part_len1);	
            memcpy(out+part_len1, m_data, len-part_len1);
            m_tail = part_len2 - (len - part_len1);	
            return len;
        }

        memcpy(out, m_data+m_tail, part_len1);
        memcpy(out+part_len1, m_data, part_len2);
        m_tail = m_head;
        return part_len1 + part_len2;
    } else {
       // if(len<m_capacity) {
       //     memcpy(out, m_data+m_tail, len);
       //     return len; 
       // } else {
       //     memcpy(out, m_data+m_tail, m_capacity);
       //     return m_capacity; 
       // }
       return 0;
    }
}

uint32_t ZStream::length()
{
    if (m_head > m_tail) {
        return m_head - m_tail;
    } else if(m_head < m_tail) {
        return m_capacity - m_tail + m_head;
    } else {
        return 0; 
    }
}

uint32_t ZStream::capacity()
{
    return m_capacity;
}

void ZStream::print_data()
{
    printf("head:%u, tail:%u\n",  m_head, m_tail);
}

char* ZStream::get_data()
{
    return m_data;
}

void ZStream::cleanup()
{
    m_tail = 0;
    m_head = 0;	
    memset(m_data, 0, m_capacity); 
}
