#include "zpacket.hpp"
#include "cmd_def.hpp"
#include "zlog.hpp"

#include "proto_inc.hpp"

//std::map<uint32_t, ZPacket::create_packet> Packet_factory::ms_create_funs;
std::map<uint32_t, create_fn> ZPacket_factory::ms_create_funs;

zpacket_t ZPacket::build_head(char data[])
{
    //zpacket_t* input = static_cast<zpacket_t*>(data);
    zpacket_t* pkt = (zpacket_t*)(data);
    ZDEBUG_LOG("uid[%u], len[%u], cmd[%0xu], seq[%u]",
            pkt->uid,
            pkt->len,
            pkt->cmd,
            pkt->seq);
    return *pkt;	
}

ZPacket* ZPacket_factory::create_packet(zpacket_t& head, char data[])
{
    ZDEBUG_LOG("ZPacket_factory::create_packet");
    ZPacket* pack = NULL;
    std::map<uint32_t, create_fn>::iterator it = ms_create_funs.find(head.cmd);	
    if (it == ms_create_funs.end()) {
        ZDEBUG_LOG("ZPacket_factory::create_packet find failed");
        return NULL;
    }

    pack = ((create_fn)it->second)(head, data);
    ZDEBUG_LOG("ZPacket_factory::create_packet find succ");
    return pack;
}

ZPacket* ZPacket::create_packet(zpacket_t& head, char data[])
{
    ZDEBUG_LOG("ZPacket::create_packet");
    return NULL;
} 

ZPacket* ZPacket_conceret::create_packet(zpacket_t& head, char data[])
{
    ZDEBUG_LOG("zpacket_conceret 1000");
    return new ZPacket_conceret();	
}

void ZPacket_factory::init()
{
    ZDEBUG_LOG("zpacket_factory init");
    //ZDEBUG_LOG("cmd %u", cmd_login);
    //ms_create_funs[cmd_login] = &ZPacket_conceret::create_packet;
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

void ZPacket_factory::clear()
{
    google::protobuf::ShutdownProtobufLibrary();
}
