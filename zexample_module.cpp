#include "com_inc.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"
#include "zexample_module.hpp"
#include "zworld.hpp"

int example_thread(void* data)
{
    ZExampleModule* module = (ZExampleModule*)data;
    while(1) {
        if(module->status()  == ZMT_EXIT) {
            break;	
        }

        ZDEBUG_LOG("example_thread while");
        //unsafe tobe continued
        //loop client
        //build packet and process
        gWorld.process_cmd();
    }

    //clean 
    ZDEBUG_LOG("epoll thread exit then close epoll");
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZExampleModule::init() 
{
    return 0;
}

int ZExampleModule::startup() 
{
    //boost::function<int(void*)> f = boost::bind(example_thread, (void*)this);
    //m_thread = make_thread<int(void*)>(f);
    //m_thread = make_thread<int(void*)>(example_thread, (void*)this);

    return 0;
}

int ZExampleModule::shutdown()
{
    return 0;
}

int ZExampleModule::exit() 
{
    return 0;
}

int ZExampleModule::loop() 
{
    //process input 
    //process output
    return 0;
}

