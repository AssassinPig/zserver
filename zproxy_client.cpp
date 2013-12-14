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

    //outstream.input(data, len);
    ZDEBUG_LOG("proxy client on_message %d", len);
    //instream.cleanup(); 

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

int ZProxyClient::on_error()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0);
}

void ZProxyClient::on_close()
{
}

void ZProxyClient::process_message()
{
    ZDEBUG_LOG("process message start");
    ZStream& instream = m_connection.get_instream();
    int i;
    if(instream.length()) {
        int thisrecv = instream.output((char*)&i, sizeof(int));
        ZDEBUG_LOG("processs messge i:%d, thisrecv:%d", i, thisrecv);
    } else {
        ZDEBUG_LOG("process message end");
        return;
    }

    i++;
    ZStream& outstream = m_connection.get_outstream();
    int thissend = outstream.input((char*)&i, sizeof(int));
    ZDEBUG_LOG("i:%d, thissend:%d", i, thissend);
    ZDEBUG_LOG("process message end");
}
