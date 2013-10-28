#include "zclient.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "zlog.hpp"
#include "zworld.hpp"

#include <boost/bind.hpp>

#include "zserver.hpp"

ZClient::ZClient(ZServer* server) : m_server(server)
{
//	boost::function<int (char data[],  uint32_t len)> handler1 = boost::bind(&ZClient::on_message, this, _1, _2);
//	boost::function<int ()> handler2 = boost::bind(&ZClient::on_error, this);
//	boost::function<int ()> handler3 = boost::bind(&ZClient::on_close, this);

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

void ZClient::close_session()
{

}

int ZClient::process_packet()
{
//	int rest_len = m_input.length();
//	do{
//		if (rest_len < sizeof(zpacket_t)) {
//			break;
//		}
//		char* data = m_input.get_data();
//		zpacket_t head = ZPacket::build_head(data);
//		if (head.len > rest_len) {
//			break;
//		} 
//
//		ZPacket* packet = ZPacket_factory::create_packet(head, data);	
//		if (packet) {
//			zlog.log("uid[%u] handle cmd[%u]", head.uid, head.cmd);
//
//			char tmp[MAX_STREAM_LEN];
//			//未必out完
//			int out_len = m_input.output(tmp, MAX_STREAM_LEN);
//			rest_len -= out_len;
//
//			process_output();
//		} else {
//			//invalid cmd
//			zlog.log("uid[%u] invalid cmd[%u]", head.uid, head.cmd);
//			return -1;
//		}
//		break;
//	} while(true);
//
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}
	
int ZClient::process_input(char data[], uint32_t len)
{
	//input不能为0
	//assert(m_input.input(data, len));	
}

int ZClient::process_output()
{
	//gWorld.add_send_list(this);
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

void ZClient::set_connection(ZFD_T fd)
{
	m_connection.set_fd(fd);	
}
