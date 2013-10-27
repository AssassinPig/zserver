#ifndef _ZCLIENT_H__
#define _ZCLIENT_H__
#include "com_def.hpp"
#include "zstream.hpp"
#include "zpacket.hpp"
#include "zconnection.hpp"

class ZServer;
class ZClient
{
public:
	ZClient(ZServer* server);	
	~ZClient();

	int on_message(char data[], uint32_t len);
	int on_error();
	int on_close();

	ZFD_T get_fd();
	
	void send_to_client(zpacket_t* packet);	
	void send_error();
	int process_packet();	
	int process_input(char data[], uint32_t len);
	int process_output();
	void close_session();

	inline ZConnection* get_connection() { return &m_connection; }
private:
	ZConnection m_connection;
	ZServer* m_server;
};
#endif //_ZCLIENT_H__ 
