#include "zconfig.hpp"
#include <assert.h>
#include <fstream>

zconfig* g_config = NULL; 
zconfig::zconfig()
{
}

zconfig::~zconfig()
{
}

bool zconfig::load_file(char* path)
{
	assert(path);
	
        std::fstream ifs;
	ifs.open(path, std::ios::in);
	
	assert(ifs.is_open());	

	//content line:key value 
        std::string str;
	while(getline(ifs, str)) {
		size_t t = str.find_first_of(' ');
		//no value no insert
		if (t == std::string::npos) {
			continue;
		}
		
		//get key and trim
                std::string key = str.substr(0, t);
                std::string value = str.substr(t, str.length()-key.length());
		
		//trim space
		size_t trim = 0;
		while(value.at(trim) == ' ' && trim < value.length()) { 
			++trim;
        }

		//++trim;
		value = value.substr(trim, value.length()- trim);

		trim = value.length()-1;
		bool need = false;
		while(value.at(trim) == ' ' && trim > 0) { 
			--trim;
			need = true;
		}
			
		if (need) {
			value = value.substr(0, trim+1);	
		}

		m_keymap[key] = value;
	}	

	ifs.close();
	return false;
}

void zconfig::print_all()
{
	KEY_MAP::iterator it = m_keymap.begin();
	for ( ; it != m_keymap.end(); ++it) {
		printf("[%s = %s]\n", it->first.c_str(), it->second.c_str());
	}
}

bool zconfig::key_exist(char* key)
{
	assert(key);
	if(m_keymap.find(key)!=m_keymap.end()) {
		return true;
	}	

	return false;
}

std::string& zconfig::find_value(char* key)
{
	assert(key!=NULL && m_keymap.size()!=0);
	return m_keymap.find(key)->second;
}
