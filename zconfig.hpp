#ifndef _ZCONFIG_H__
#define _ZCONFIG_H__
#include <map>
#include <string>
class zconfig
{
    public:
    zconfig();
    ~zconfig();	

    typedef std::map<std::string, std::string> KEY_MAP;

    bool load_file(char* path);
    bool key_exist(char* key);
    std::string& find_value(char* key);

    void print_all();

    private:
    KEY_MAP m_keymap;
};
extern zconfig *g_config;
#endif //_ZCONFIG_H__
