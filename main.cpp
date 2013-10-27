#include "zserver.hpp"
int main()
{
    ZServer server;

    server.init();
    server.startup();
    server.loop();
	//server.exit();
	
    return 0;  
}
