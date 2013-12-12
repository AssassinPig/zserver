#include "zproxy_client.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"

ZProxyClient::ZProxyClient(ZServer* server) : ZClient(server)
{

}

int ZProxyClient::on_message(char data[], uint32_t len)
{
    ZStream& instream = m_connection.get_instream(); 
    ZStream& outstream = m_connection.get_outstream(); 

    outstream.input(data, len);

    ZDEBUG_LOG("proxy client on_message %d", len);
    instream.cleanup(); 

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

int ZProxyClient::on_error()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

void ZProxyClient::on_close()
{
}

