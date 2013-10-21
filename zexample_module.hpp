#ifndef _ZEXAMPLE_H__
#define _ZEXAMPLE_H__
#include "zthread_module.hpp"
class ZExampleModule : public ZModule
{
public:
		virtual int init() ;
		virtual int startup() ;
		virtual int shutdown();
		virtual int exit() ;
		
		virtual int ready_process() ;
		virtual int process_input() ;
		virtual int process_output();
		virtual int process_except();

		virtual int loop() ;
private:

};
#endif //_ZEXAMPLE_H__
