#ifndef _ZCONFIG_H__
#define _ZCONFIG_H__
#include <map>
#include <string>
using namespace std;
class zconfig
{
public:
	zconfig();
	~zconfig();	
	
	typedef std::map<string, string> KEY_MAP;

	bool load_file(char* path);
	bool key_exist(char* key);
	string& find_value(char* key);
	
	void print_all();
		
private:
	KEY_MAP m_keymap;
};
#endif //_ZCONFIG_H__
