#ifndef _ZCONNECTION_H__
#define _ZCONNECTION_H__

#include "com_def.hpp"
#include "zstream.hpp"
#include "zpacket.hpp"
#include <boost/function.hpp>

class ZConnection
{
public:
    enum ZCONNECTION_STATUS {
        ZCS_CONNECTED,
        ZCS_CLOSE,
        ZCS_UNKOWN,
    };

    typedef	boost::function<int (char data[],  uint32_t len)> message_handler;
    typedef	boost::function<int ()> error_handler;
    typedef	boost::function<void ()> close_handler;

    ZConnection();
    ~ZConnection();

    inline ZFD_T get_fd() { return m_fd; }
    inline void set_fd(ZFD_T fd) { m_fd = fd;}

    void set_message_handler(message_handler handler);
    void set_error_handler(error_handler handler);
    void set_close_handler(close_handler handler);

    void on_message(char data[], uint32_t len);
    void on_error();
    void on_close();

    //be invoked by network epoll
    int on_network_read();
    int on_network_write();

    ZCONNECTION_STATUS status() { return m_status; } 

    ZStream& get_instream() { return m_input; }
    ZStream& get_outstream() { return m_output; }
private:
    ZFD_T m_fd;
    ZStream m_input;
    ZStream m_output;

    message_handler m_message_handler;
    error_handler m_error_handler;
    close_handler m_close_handler;

    ZCONNECTION_STATUS m_status;
};

#endif
