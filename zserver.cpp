#include "zserver.hpp"
#include "com_macro.hpp"
#include "zlog.hpp"
#include "zpacket.hpp"
#include "zworld.hpp"

#include<signal.h>

ZLog zlog;
//ZEpoll ZServer::m_epoll;
bool ZServer::ms_active=false;
//zmodulecontainer
ZModuleContainer* m_ModuleContainer=NULL; 	

ZServer::ZServer()
{
	ms_active = false;
}

int ZServer::init()
{   
  	set_signal();
	//m_epoll.init();
	ZPacket_factory::init();
	ms_active = true;
	m_ModuleContainer = new ZModuleContainer;	
	FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::process_input()
{

}

int ZServer::process_output()
{

}

int ZServer::process_cmd()
{

}

int ZServer::set_signal()
{
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	act.sa_flags &= ~SA_RESETHAND;
	sigaction(SIGPIPE, &act, NULL);
	
	signal(SIGINT, ZServer::shutdown);
	signal(SIGKILL, ZServer::shutdown);
	signal(SIGQUIT, ZServer::shutdown);
	signal(SIGTERM, ZServer::shutdown);
	
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZServer::recv_thread_fn(void* args)
{
/*
	printf("thread[%u] ready\n", pthread_self());
	zlog.log("thread[%u] ready", pthread_self());
	while(1) {
		int status = pthread_cond_wait(&work_list->cond, &work_list->mutex);
		if (status != 0)
			perror("wait failed");
		else {
			printf("thread[%u] run\n", pthread_self());
			zlog.log("thread[%u] run", pthread_self());
		}
		//break;
	}	

	printf("thread[%u] end\n", pthread_self());
*/
}

void ZServer::send_thread_fn(void* args)
{

}

void ZServer::admin_thread_fn(void* args)
{

}

int ZServer::start_thread()
{
	/*
	int ret = pthread_create(&m_admin_tid, NULL, admin_thread_fn, NULL);
	if (ret) {
		perror("pthread_create admin failed\n");
		zlog.log("pthread_create admin failed");
	} else {
		ret = pthread_join(m_admin_tid, NULL);
		if (ret) {
			perror("admin thread return failed\n");
			zlog.log("admin thread return failed");
		} else {
			printf("admin thread return success\n");
			zlog.log("admin thread return success");
		}
	} 
	*/
	//pthread_t recv_thd_pid;
	//pthread_t send_thd_pid;
}

int ZServer::startup()
{
    //m_epoll.startup();
	m_ModuleContainer->startup();

	//log("server startup");
	zlog.log("server startup");
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

bool ZServer::is_active()
{
	return ms_active;
}

int ZServer::base_loop()
{                  
	while(is_active()){
		zlog.log("server base_loop");
			//zmodulecontainer
				
			//network input output 
    		//m_epoll.loop();
			
  			//process_input();
  			//process_output();
  			//gWorld.process_cmd();
		sleep(100);	
	}
	
	//m_epoll.exit();

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

void ZServer::shutdown(int sig_num)
{
	m_ModuleContainer->exit();
	//m_epoll.shutdown();
	ms_active = false;
	zlog.log("server shutdown[sig:%d]", sig_num);
    //FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::uninit()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZServer::load_config()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}
