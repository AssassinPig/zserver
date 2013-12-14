#include "zconnection.hpp"
#include "zlog.hpp"

ZConnection::ZConnection()
{
    m_status = ZCS_CONNECTED;
    m_input.malloc();
    m_output.malloc();
}

ZConnection::~ZConnection()
{

}

void ZConnection::set_message_handler(message_handler handler)
{
    m_message_handler = handler;
}

void ZConnection::set_error_handler(error_handler handler)
{
    m_error_handler = handler;
}

void ZConnection::set_close_handler(close_handler handler)
{
    m_close_handler = handler;
}

void ZConnection::on_message(char data[], uint32_t len)
{
    ZDEBUG_LOG("zconnection on message len=%u", len);
    m_message_handler(data, len);		
}

void ZConnection::on_error()
{
    m_error_handler();
}

void ZConnection::on_close()
{
    m_status = ZCS_CLOSE;
    m_close_handler();
}

int ZConnection::on_network_read() 
{
    int n = 0;
    int nread = 0;

    char buf[MAX_SEND];
    memset(buf, 0, MAX_SEND);

    while ( (nread = read(m_fd, buf, MAX_SEND)) > 0) {
        n += nread;
        if(n<(int)m_input.capacity()) {
            m_input.input(buf, nread); 
        } else {
            perror("input stream full, the rest will be thrown"); 
        }
        
        memset(buf, 0, MAX_SEND);
        ZDEBUG_LOG("on_network_read1 thisread:%d", nread);
    }

    if (nread == -1 && errno != EAGAIN) {
        perror("read error");
        return -1;
    }

    ZDEBUG_LOG("on_network_read sum:%d", n);
    //on_message(m_input.get_data(), m_input.length());
    return n;	
}

int ZConnection::on_network_write()
{
    int nwrite = 0;
    char buf[MAX_SEND];
    int n = m_output.length();
    int ret = 0;

    while (n > 0) { 
        int thiswrite = m_output.output(buf, sizeof(int));
        ZDEBUG_LOG("on_network_write0 n:%d, thiswirte:%d", n, thiswrite);
        if( (nwrite = write(m_fd, buf, thiswrite)) <=0) {
            perror("write failed on network write");
            break;
        }

        n -= nwrite;
        ret += nwrite;
        memset(buf, 0, MAX_SEND);
        ZDEBUG_LOG("on_network_write1 thiswirte:%d, nwrite:%d, n:%d", thiswrite, nwrite, n);
    }

    if (nwrite == -1 && errno != EAGAIN) {
        ZDEBUG_LOG("write error");
        perror("write error");
        return -1;
    }
    
    if(ret >= (int)m_output.length()) {
        m_output.cleanup(); 
    }

    return ret;	
}
