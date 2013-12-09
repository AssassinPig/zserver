#include "zclient.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "zlog.hpp"
#include "zworld.hpp"

#include <boost/bind.hpp>

#include "zserver.hpp"

ZClient::ZClient(ZServer* server) : m_server(server)
{
	ZConnection::message_handler handler1 = boost::bind(&ZClient::on_message, this, _1, _2);
	ZConnection::error_handler handler2 = boost::bind(&ZClient::on_error, this);
	ZConnection::close_handler handler3 = boost::bind(&ZClient::on_close, this);

	m_connection.set_message_handler(handler1);
	m_connection.set_error_handler(handler2);
	m_connection.set_close_handler(handler3);
}

ZClient::~ZClient()
{

}

int ZClient::on_message(char data[], uint32_t len)
{
	zlog.log("on_message: data len=%u", len);
	ZStream& out = m_connection.get_outstream();
	out.output(data, len);
	m_connection.on_network_write();
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

int ZClient::on_error()
{
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

void ZClient::on_close()
{
	zlog.log("client close");
	m_server->close_client(this);
}
