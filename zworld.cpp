#include "zworld.hpp"
#include "zpacket.hpp"
#include "zlog.hpp"
#include "cmd_def.hpp"
#include "zepoll.hpp"
#include "zthread_module.hpp"

ZWorld gWorld;
void ZWorld::dispatch(char data[], uint32_t len, ZFD_T fd)
{
//	SESSION_MAP::iterator it = m_sessions.find(fd);
//	if (it == m_sessions.end()) {
//		//m_sessions[fd] = 0;
//		zlog.log("fd does not exist");
//		return;
//	}
//	
//	//rebuild head	
//	zlog.log("receive data len[%u]", len);
//	zpacket_t head = ZPacket::build_head(data);
/*
	if (head.len > len) {
		zlog.log("uid[%u] invalid packet len[%u], head.len[%u]", head.uid, len, head.len);
		return;
	}
*/	
//	ZClient* client = find_client(head.uid);
//	if (client) {
//		client->process_input(data, len);
//	} else {
//		if (head.cmd == cmd_login) {
//			add_client(head.uid, fd);
//		} else {
//			zlog.log("player[%u] have not login", head.uid);			
//			return;
//		}
//	} 
}

int ZWorld::process_cmd()
{
//	CLIENT_MAP::iterator it_begin = m_clients.begin();		
//	CLIENT_MAP::iterator it_end = m_clients.end();		
	//CLIENT_MAP::itertor it = it_begin;		
	//针对每一个客户端处理
//	for (; it_begin != it_end; ++it_begin) {
//		if (it_begin->second->process_packet() == -1) {
//			//invaild cmd
//			kick_player(it_begin->first);
//		}	
//	}
	return 0;
}

void ZWorld::add_send_list(ZClient* client)
{
	//m_listReadyClients.push_back(client);	
	//
	//ZEpoll* epoll = (ZEpoll*)g_ModuleContainer->get_network_module();
	//epoll->add_send_event(client->get_fd());
}

ZWorld::SEND_LIST& ZWorld::get_send_list()
{
	return m_listReadyClients;	
}

ZClient* ZWorld::get_client(int fd)
{
	SESSION_MAP::iterator it = m_sessions.find(fd);
	CLIENT_MAP::iterator it_client = m_clients.find(it->second);
	return it_client->second; 
}

void ZWorld::add_session(ZFD_T fd)
{
	SESSION_MAP::iterator it = m_sessions.find(fd);
	if (it == m_sessions.end()) {
		m_sessions[fd] = 0;
	} else {
		zlog.log("player[%u] reconnect!!!", m_sessions[fd]);	
		kick_player(m_sessions[fd]);
	}	
}

void ZWorld::add_client(USER_ID uid, ZFD_T fd)
{
	SESSION_MAP::iterator it = m_sessions.find(fd);
	if (it == m_sessions.end()) {
		zlog.log("player[%u] fd does not exist", uid);
		return;
	}
	
	m_sessions[fd] = uid;
	//先这样，后面优化
//	ZClient* client = new ZClient(fd);
//	m_clients[uid] = client;
}

void ZWorld::kick_player(USER_ID uid)
{
//	ZClient* client = find_client(uid);
//	if (client) {
//		zlog.log("kick player[%u]", uid);
//		client->close_session();
//		remove_player(uid);	
//		return;
//	}
	
	zlog.log("kick player[%u] faild, he does not exist", uid);
}

void ZWorld::remove_player(USER_ID uid)
{
	CLIENT_MAP::iterator it = m_clients.find(uid);	
	if (it == m_clients.end()) {
		zlog.log("remove player[%u] failed", uid);
	} else {
		m_clients.erase(it);
	}
}

ZClient* ZWorld::find_client(USER_ID uid)
{
	CLIENT_MAP::iterator it = m_clients.find(uid);
	if (it == m_clients.end()) {
		return NULL;
	} else {
		return it->second;	
	}
}

