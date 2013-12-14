#ifndef _ZPROXY_CLIENT_H__ 
#define _ZPROXY_CLIENT_H__
#include "zclient.hpp"

class ZProxyClient : public ZClient
{
    public:
        ZProxyClient(ZServer* server);

	virtual int on_message(char data[], uint32_t len);
	virtual int on_error();
	virtual void on_close();

        virtual void process_message();
    private:

};

#endif //_ZPROXY_CLIENT_H__

