#ifndef _ZREACTOR_H__ 
#define _ZREACTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_REQKEY_LEN 100
#define MAX_REQ_LEN 10
template<typename K>
class zsimple_request;

typedef struct key_req {
	uint32_t req; //from client or server first alloc
	uint32_t time; //the time receive
	zsimple_request<uint32_t>* request;
}KEY_REQ_ITEM;


template<typename K>
class zsimple_response;

typedef struct key_resp {
	uint32_t req;
	uint32_t time;
	zsimple_response<uint32_t>* resp;
}KEY_RESP_ITEM;

/*
template<typename C, typename T = uint32_t>
class reactor_item
{
public:
	T req;
	T time;
	C* ptr_item;	
}; 
*/

template<typename K = KEY_RESP_ITEM>
class zsimple_request
{
public:
	zsimple_request(uint32_t req, uint32_t cmd, bool needs_resp) {
		m_src_req = req;
		m_cmd = cmd;
		m_needs_resp = needs_resp;
		memset(m_keys, 0, sizeof(uint32_t)*MAX_REQ_LEN);

		//还是要new???
	}
	
	virtual void execute() = 0;
	
	bool is_complete()  {
		if (!m_needs_resp) {
			return true;
		}
			
		for (int i=0; i<MAX_REQ_LEN; ++i) {
			K& k = m_keys[i];
			if (k.req != 0 || (k.resp != NULL && !k.resp->is_complete())) {
				return false;
			}	
		}
	
		return true;
	}	
	
	virtual bool update(uint32_t req) {}

protected:
	K m_keys[MAX_REQ_LEN];	
	bool m_needs_resp;
	uint32_t m_cmd; //source c->s cmd
	uint32_t m_src_req;
};

template<typename K = KEY_RESP_ITEM>
class conrete_req : public zsimple_request<K> 
{
public:
	virtual void execute() {
		//create reponse	
		//send cmd to db/proxy server
	
		//total 2 s->s packets
/*
		int total = 2;
		for (int i=0; i<total; ++i) {
			m_keys[i] = m_src_req + i;
		}
*/
			//m_keys[i] = get_server_seq();
		//create s->s packet 1
		//create zsimple_response 1

		//create s->s packet 2
	}
	
	virtual bool update(uint32_t req) {
		
	}

private:

};

template<typename T = uint32_t>
class zsimple_response
{
public:
	zsimple_response(T t) {
		m_req = t;
	}	

	bool is_complete() {
		return true;
	}
	
	bool update() {
		return true;
	}
	
protected:
	T m_req;
	uint32_t m_cmd; //s->s cmd 
};

//seq 的来源
template<typename T2 = uint32_t, typename K = KEY_REQ_ITEM>
class zsimple_reactor
{
public:
	zsimple_reactor() {
		memset(m_keys, 0, sizeof(K)*MAX_REQKEY_LEN);
	}
	
	zsimple_request<T2>* create_req(...) {
		
	}

	bool receive_req(zsimple_request<T2>* req) {
				
	}
		
	zsimple_response<T2>* create_respon(...) {

	}

	bool receive_response(zsimple_response<T2>* respon) {
		return true;
	}

	//receive from other server 
 	bool update(uint32_t req, ...) {
		for (int i = 0; i < MAX_REQKEY_LEN; ++i) {
			K& k_item = m_keys[i];
			if (k_item.key != 0) {
				if(k_item.request->update(req)) {
					if (k_item.request->is_complete()) {
						//packet is ok
						//create_2_client_packet()

						k_item.key = 0;
						k_item.request = NULL;
						k_item.time = 0;
					} else {
						
					}	
				} else {
					//clean this request
				}
			} 
		}
		return true;
	}

	bool is_complete() {
		return true;
	}
	
private:
	K m_keys[MAX_REQKEY_LEN];
};

#endif //_ZREACTOR_H__
