#include "zserver.hpp"
int main()
{
    ZServer server;

    server.init();
    server.startup();
    server.base_loop();
    server.uninit();
    //server.shutdown(99);

    return 0;  
}
