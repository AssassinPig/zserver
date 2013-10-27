#ifndef _ZCONNECTION_H__
#define _ZCONNECTION_H__

#include "com_def.hpp"
#include "zstream.hpp"
#include "zpacket.hpp"
#include <boost/function.hpp>

enum ZCONNECTION_STATUS {
	ZCS_CONNECTING, 
	ZCS_CONNECTED,
	ZCS_EXITING,
	ZCS_CLOSE,
	ZCS_UNKOWN,
};

class ZConnection
{
public:
	typedef	boost::function<int (char data[],  uint32_t len)> message_handler;
	typedef	boost::function<int ()> error_handler;
	typedef	boost::function<int ()> close_handler;
		
	ZConnection();
	~ZConnection();

	inline ZFD_T get_fd() { return m_fd; }
	
	void set_message_handler(message_handler handler);
	void set_error_handler(error_handler handler);
	void set_close_handler(close_handler handler);

	void on_message(char data[], uint32_t len);
	void on_error();
	void on_close();

	int on_network_read() 
	{
		int n = 0;
		int nread = 0;
		char* buf = m_input.get_data();
		while ((nread = read(m_fd, buf + n, BUFSIZ-1)) > 0) {
			n += nread;
		}

		if (nread == -1 && errno != EAGAIN) {
			perror("read error");
			return -1;
		}

		return n;	
	}

	int on_network_write()
	{
		int n = m_output.length();
		int nwrite = 0;
		char* buf = m_output.get_data();
		while (n > 0) {
			nwrite = write(m_fd, buf + n, BUFSIZ-1);
			if (nwrite < n) {
				if (nwrite == -1 && errno != EAGAIN) {
					perror("write error");
				}
				break;
			}

			n -= nwrite;
		}
		return 0;	
	}

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
