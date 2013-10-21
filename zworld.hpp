#ifndef _ZWORLD_H__
#define _ZWORLD_H__
#include "std_inc.hpp"
#include "com_inc.hpp"
#include "zclient.hpp"
class ZPacket;
class ZWorld
{
public:
	void dispatch(char data[], uint32_t len, ZFD_T fd);
	typedef std::map<USER_ID, ZClient*> CLIENT_MAP;
	typedef std::map<ZFD_T, USER_ID> SESSION_MAP;

	//如果用户重复登录，则kick前一个, 保留最新登录的
	void add_session(ZFD_T fd);
	void add_client(USER_ID uid, ZFD_T fd);

	void kick_by_fd(ZFD_T fd);
	void kick_player(USER_ID uid);	
	
	void remove_player(USER_ID uid);
	
	int process_cmd();

protected:
	void handle_packet(ZPacket* packet);
private:
	ZClient* find_client(USER_ID uid);

	CLIENT_MAP m_clients;		
	SESSION_MAP m_sessions;
};

extern ZWorld gWorld;

#endif //_ZWORLD_H__
