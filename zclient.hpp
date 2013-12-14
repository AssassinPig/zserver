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
	virtual ~ZClient();

	virtual int on_message(char data[], uint32_t len);
	virtual int on_error();
	virtual void on_close();
	
        virtual void process_message();

	void send_to_client(zpacket_t* packet);	
	void send_error();
	inline ZConnection* get_connection() { return &m_connection; }
	inline void set_connection(ZFD_T fd) { m_connection.set_fd(fd); }

protected:
	ZConnection m_connection;
	ZServer* m_server;
};
#endif //_ZCLIENT_H__ 
