#include "com_inc.hpp"
#include "com_def.hpp"
#include "std_inc.hpp"

#ifndef _PACKET_H__
#define _PACKET_H__

struct zpacket_t {
   uint32_t len;
   uint32_t cmd;
   USER_ID uid;
   uint32_t seq;
   uint8_t ret;
   uint8_t body[];
}__attribute__((packed));

class ZPacket {
public:
    ZPacket() : m_ready(false) {}
    virtual bool input(const zpacket_t& packet) = 0;
    virtual bool output() { return true; }

	static zpacket_t build_head(char data[]);
	static ZPacket* create_packet(zpacket_t& head, char data[]); 
protected:
    zpacket_t m_packet;
    bool m_ready;
};

//typedef ZPacket* (ZPacket::*create_fn)(zpacket_t& head, char data[]); 
typedef ZPacket* (*create_fn)(zpacket_t& head, char data[]); 

class ZPacket_factory
{
public:
	//ZPacket_factory();
	static void init();
	//typedef (T::*create_packet)(zpacket_t& head, char data[]); 
	static ZPacket* create_packet(zpacket_t& head, char data[]);
	static std::map<uint32_t, create_fn> ms_create_funs;
	//static std::map<uint32_t, create_packet> ms_create_funs;
};

class ZPacket_conceret : public ZPacket
{
public:
    virtual bool input(const zpacket_t& packet) { return true; }
    //virtual bool output();
	static ZPacket* create_packet(zpacket_t& head, char data[]);
public:
    uint32_t m_data1;
};

#endif  //_PACKET_H_ 
