#include "zconfig.hpp"
#include "zproxy_server.hpp"
#include "zlog.hpp"

ZLOG_INIT(proxy_server.log); 
int main()
{
    g_config = new zconfig;
    if(!g_config->load_file("proxy_server.conf")) {
        perror("load_files failed");
        return 0; 
    }

    ZProxyServer server;
    server.init();

    std::string& bind_ip = g_config->find_value("ip");
    std::string& port = g_config->find_value("port");
    int nport = atoi(port.c_str());
    server.startup(bind_ip.c_str(), nport);
    server.loop();
    server.exit();
	
    return 0;  
}
