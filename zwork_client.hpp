#ifndef _ZWORK_CLIENT_H__
#define _ZWORK_CLIENT_H__

#include "zclient.hpp"

class ZServer;
class ZWorkClient : public ZClient
{
    public:
        ZWorkClient(ZServer* server);

	virtual int on_message(char data[], uint32_t len);
	virtual int on_error();
	virtual void on_close();
};

#endif //_ZWORK_CLIENT_H__
