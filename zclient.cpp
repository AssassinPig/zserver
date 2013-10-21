#include "zclient.hpp"
#include "com_macro.hpp"
#include "com_def.hpp"
#include "zlog.hpp"

ZFD_T ZClient::get_fd()
{
	return m_fd;
}
/*
int ZClient::process_cmd()
{
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}
*/

ZClient::ZClient(ZFD_T fd)
{
	//default length
	m_input.malloc();
	m_output.malloc();
}

ZClient::~ZClient()
{

}

void ZClient::close_session()
{

}

int ZClient::process_packet()
{
	int rest_len = m_input.length();
	do{
		if (rest_len < sizeof(zpacket_t)) {
			break;
		}
		char* data = m_input.get_data();
		zpacket_t head = ZPacket::build_head(data);
		if (head.len > rest_len) {
			break;
		} 

		ZPacket* packet = ZPacket_factory::create_packet(head, data);	
		if (packet) {
			//packet(packet);
			zlog.log("uid[%u] handle cmd[%u]", head.uid, head.cmd);

			char tmp[MAX_STREAM_LEN];
			//未必out完
			//m_input.output(tmp, head.len+sizeof(zpacket_t));
			int out_len = m_input.output(tmp, MAX_STREAM_LEN);
			rest_len -= out_len;
			//rest_len -= head.len;
			//rest_len -= sizeof(zpacket_t); 
		} else {
			//invalid cmd
			zlog.log("uid[%u] invalid cmd[%u]", head.uid, head.cmd);
			return -1;
		}
		break;
	} while(true);

	FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}
	
int ZClient::process_input(char data[], uint32_t len)
{
	//input不能为0
	assert(m_input.input(data, len));	
}

int ZClient::process_output()
{

}
