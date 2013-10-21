#ifndef _ZCLIENT_H__
#define _ZCLIENT_H__
#include "com_def.hpp"
#include "zstream.hpp"
#include "zpacket.hpp"
class ZClient
{
public:
	ZClient(ZFD_T fd);	
	~ZClient();
	
	ZFD_T get_fd();
	
	void send_to_client(zpacket_t* packet);	
	void send_error();
	int process_packet();	
	int process_input(char data[], uint32_t len);
	int process_output();
	void close_session();

private:
	ZFD_T m_fd;
	ZStream m_input;
	ZStream m_output;
};
#endif //_ZCLIENT_H__ 
