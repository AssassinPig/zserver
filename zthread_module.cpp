#include "zthread_module.hpp"
#include "zexample_module.hpp"
#include "zepoll.hpp"

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
	ZEpoll* epoll_module = new ZEpoll;	
	m_pModuleList[m_count] = epoll_module;
	epoll_module->startup();
	m_count++;

	ZExampleModule* example_module = new ZExampleModule;  			
	m_pModuleList[m_count] = example_module;
	example_module->startup();
	m_count++;

	return 0;
}

int ZModuleContainer::loop()
{
	while(true)
	{
		if(!m_status)
		{
			break;
		}

		for(int i=0; i<m_count; ++i)
		{
			if(m_pModuleList)
			{
				ZModule* module = m_pModuleList[i];
				if(module->status() != ZMT_EXIT)
				{
					//scope mutex
					module->loop();	
				}
			}
		}
	}

	//clean();
//	for(int i=0; i<m_count; ++i)
//	{
//		if(m_pModuleList)
//		{
//			ZModule* module = m_pModuleList[i];
//		}
//	}
	

	return 0;	
}

int ZModuleContainer::exit()
{
	for(int i=0; i<m_count; ++i)
	{
			if(m_pModuleList)
			{
				ZModule* module = m_pModuleList[i];
				module->exit();
			}
	}

	return 0;
}
