#ifndef _ZMODUL_H__
#define _ZMODUL_H__

#define ZMODULE_NUM_MAX 64 

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/pthread/once.hpp>

enum ZMODULE_TYPE{
	ZMT_NORMAL = 0,
	ZMT_EXIT = 1,
};

class ZModule
{
	public:
		ZModule();
		virtual ~ZModule();
			
		virtual int init() = 0;
		virtual int startup() = 0;
		virtual int shutdown() = 0;
		virtual int exit() = 0;
		
		virtual int ready_process() = 0;
		virtual int process_input() = 0;
		virtual int process_output() = 0;
		virtual int process_except() = 0;

		virtual int loop() = 0;
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

	private:
		boost::thread m_thread;
		ZModule** m_pModuleList; //make sure mutex
		int m_status;
		int m_count;
};

#endif //_ZNETWORK_MODUL_H__
