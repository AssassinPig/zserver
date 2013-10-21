#ifndef _ZNETWORK_MODUL_H__
#define _ZNETWORK_MODUL_H__

enum ZNETWORK_TYPE{
	ZNT_NORMAL = 0,
	ZNT_EXIT = 1,
};

#define ZNETWORK_MODUL_INIT ZNETWORK_TYPE ZNetwork_modul::ms_status=ZNT_EXIT;

class ZNetwork_modul
{
public:
	ZNetwork_modul();
	virtual ~ZNetwork_modul();
	
	virtual int init() = 0;
	virtual int startup() = 0;
	virtual int shutdown() = 0;
	virtual int exit() = 0;
	
	virtual int ready_process() = 0;
	virtual int process_input() = 0;
	virtual int process_output() = 0;
	virtual int process_except() = 0;
    //int loop();

protected:
	static ZNETWORK_TYPE ms_status;
};
#endif //_ZNETWORK_MODUL_H__
