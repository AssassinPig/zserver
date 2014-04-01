#include "zclient.hpp" 
#include "zsocket.hpp"

ZClient::ZClient()
{

}

ZClient::~ZClient()
{

}

int ZClient::Init()
{
    m_socket = new ZSocket;
}

int ZClient::Startup(const char* ip, int port)
{
}
 
int ZClient::Connect()
{

}

int ZClient::Disconnect()
{

}

int ZClient::Exit()
{

}

int ZClient::Loop()
{

}

