#ifndef _ZCMD_DEF_H__
#define _ZCMD_DEF_H__

enum cmd_def{
	cmd_register = 0x101,

	cmd_login = 0x1000,
	cmd_register_role = 0x1001,
	cmd_unregister_role = 0x1002,
		
	//用户基本信息
	cmd_get_user_info = 0x2000,
	cmd_get_bag_info = 0x2001,
	cmd_get_attribute = 0x2002,
	cmd_get_equipment = 0x2003,

	//行为
	cmd_walk = 0x3000,
	cmd_rest = 0x3001,
	cmd_attack = 0x3002,
	
	//任务
	cmd_get_mission = 0x4000,
	cmd_delete_mission = 0x4001,
	cmd_add_mission = 0x4002,
	cmd_set_step_mission = 0x4003,
	cmd_finish_mission = 0x4004,

	//team
	
	//social
	
	//	

	//
	cmd_exit = 0x9000,
};

#endif //_ZCMD_DEF_H__
