#ifndef _ZMODULE_H__
#define _ZMODULE_H__

#include "zthread_util.hpp"

#define ZMODULE_NUM_MAX 64 

enum ZMODULE_TYPE{
	ZMT_RUNNING = 0,
	ZMT_EXIT = 1,
	ZMT_IDLE = 2,
};

class ZModule
{
	public:
		ZModule();
		virtual ~ZModule();
			
		virtual int init() {return 0;}
		virtual int startup() {return 0;}
		virtual int shutdown() {return 0;}
		virtual int exit() {return 0;}
		
		virtual int ready_process() {return 0;}

		virtual int process_input() {return 0;}
		virtual int process_output(){return 0;}
		virtual int process_except() {return 0;}

		virtual int loop() {return 0;} 
		//inline
		ZMODULE_TYPE status() { return m_status; }
	protected:
		ZMODULE_TYPE m_status;
		boost::thread m_thread;
};

typedef int (*thread_fun)(void*);
class ZModuleContainer
{
	public:
		ZModuleContainer(int container_max = ZMODULE_NUM_MAX); 
		virtual ~ZModuleContainer();

		int init();
		int startup();
		int loop();
		int exit();

		ZModule* get_network_module();

	private:
		boost::thread m_thread;
		ZModule** m_pModuleList; //make sure mutex
		int m_status;
		int m_count;
};

extern ZModuleContainer* g_ModuleContainer;

#endif //_ZNETWORK_MODUL_H__
