#include "zproxy_client.hpp"
#include "com_macro.hpp"

ZProxyClient::ZProxyClient(ZServer* server) : ZClient(server)
{

}

int ZProxyClient::on_message(char data[], uint32_t len)
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

int ZProxyClient::on_error()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

void ZProxyClient::on_close()
{
}

