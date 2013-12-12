#include "zwork_client.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"

ZWorkClient::ZWorkClient(ZServer* server) : ZClient(server)
{

}

int ZWorkClient::on_message(char data[], uint32_t len)
{
    ZStream& instream = m_connection.get_instream(); 
    ZStream& outstream = m_connection.get_outstream(); 

    ZDEBUG_LOG("zworkclient on_message input %d", data);

    char buf[32];
    static int times = 0;
    sprintf(buf, "%d", times++);
    outstream.input(buf, sizeof(int));

    instream.cleanup(); 

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

int ZWorkClient::on_error()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

void ZWorkClient::on_close()
{

}

