#include "zconnection.hpp"

ZConnection::ZConnection()
{
	m_input.malloc();
	m_output.malloc();
}

ZConnection::~ZConnection()
{

}

void ZConnection::set_message_handler(message_handler handler)
{
	m_message_handler = handler;
}

void ZConnection::set_error_handler(error_handler handler)
{
	m_error_handler = handler;
}

void ZConnection::set_close_handler(close_handler handler)
{
	m_close_handler = handler;
}

void ZConnection::on_message(char data[], uint32_t len)
{
	m_message_handler(data, len);		
}

void ZConnection::on_error()
{
	m_error_handler();
}

void ZConnection::on_close()
{
	m_close_handler();
}

