#include "zthread_module.hpp"
#include "zexample_module.hpp"
#include "zepoll.hpp"

ZModuleContainer* g_ModuleContainer = NULL;
ZModule::ZModule()
{
}

ZModule::~ZModule()
{
}

ZModuleContainer::ZModuleContainer(int container_max)
{
    m_count = container_max;
    m_pModuleList = (ZModule**)malloc(sizeof(ZModule*)*container_max); 
}

ZModuleContainer::~ZModuleContainer()
{
}

int ZModuleContainer::init()
{
    return 0;
}

int ZModuleContainer::startup()
{
   // ZExampleModule* example_module = new ZExampleModule;  			
   // m_pModuleList[1] = example_module;

    return 0;
}

int ZModuleContainer::loop()
{
    while(true) {
        if(!m_status) {
            break;
        }

        for(int i=0; i<m_count; ++i) {
            if(m_pModuleList) {
                ZModule* module = m_pModuleList[i];
                if(module->status() != ZMT_EXIT) {
                    //scope mutex
                    module->loop();	
                }
            }
        }
    }

    //clean();
    return 0;	
}

int ZModuleContainer::exit()
{
    for(int i=0; i<m_count; ++i) {
        if(m_pModuleList) {
            ZModule* module = m_pModuleList[i];
            if(module)
                module->exit();
        }
    }

    return 0;
}

