#include "zpacket.hpp"
#include "cmd_def.hpp"
#include "zlog.hpp"

//std::map<uint32_t, ZPacket::create_packet> Packet_factory::ms_create_funs;
std::map<uint32_t, create_fn> ZPacket_factory::ms_create_funs;

zpacket_t ZPacket::build_head(char data[])
{
	//zpacket_t* input = static_cast<zpacket_t*>(data);
	zpacket_t* pkt = (zpacket_t*)(data);
	zlog.log("uid[%u], len[%u], cmd[%0xu], seq[%u]",
			 pkt->uid,
			 pkt->len,
			 pkt->cmd,
			 pkt->seq);
	return *pkt;	
}

ZPacket* ZPacket_factory::create_packet(zpacket_t& head, char data[])
{
	zlog.log("ZPacket_factory::create_packet");
	ZPacket* pack = NULL;
	std::map<uint32_t, create_fn>::iterator it = ms_create_funs.find(head.cmd);	
	if (it == ms_create_funs.end()) {
		zlog.log("ZPacket_factory::create_packet find failed");
		return NULL;
	}
	
	pack = ((create_fn)it->second)(head, data);
	zlog.log("ZPacket_factory::create_packet find succ");
	return pack;
}

ZPacket* ZPacket::create_packet(zpacket_t& head, char data[])
{
	zlog.log("ZPacket::create_packet");
	return NULL;
} 

ZPacket* ZPacket_conceret::create_packet(zpacket_t& head, char data[])
{
	zlog.log("zpacket_conceret 1000");
	return new ZPacket_conceret();	
}

void ZPacket_factory::init()
{
	zlog.log("zpacket_factory init");
	//zlog.log("cmd %u", cmd_login);
	ms_create_funs[cmd_login] = &ZPacket_conceret::create_packet;
}
