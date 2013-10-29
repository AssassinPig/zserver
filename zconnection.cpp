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
	zlog.log("zconnection on message len=%u", len);
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
		zlog.log("on_network_read %s", buf);
	}

	//char* buf = m_input.get_data();
	//	while ( (nread = read(m_fd, buf + n, BUFSIZ-1)) > 0) {
	//		n += nread;
	//	}

	if (nread == -1 && errno != EAGAIN) {
		perror("read error");
		return -1;
	}
	
	//on_message(m_input.get_data(), m_input.length());
	//on_message(buf, n);
	return n;	
}

int ZConnection::on_network_write()
{
	//int n = m_output.length();
	int nwrite = 0;
	char buf[MAX_SEND];
	sprintf(buf, "abcdef");
	int n = strlen(buf)+1;
	int ret = 0;

	while (n > 0) { 
		if( (nwrite = write(m_fd, buf, strlen(buf)+1)) <=0) {
			perror("write failed on network write");
			break;
		}

		n -= nwrite;
		ret += nwrite;
		zlog.log("on_network_write1 %s", buf);
	}

	zlog.log("on_network_write %s", buf);
	if (nwrite == -1 && errno != EAGAIN) {
        zlog.log("write error");
		perror("write error");
		return -1;
	}

	return ret;	
}
