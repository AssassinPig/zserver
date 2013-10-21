#ifndef _ZSTRING_H__
#define _ZSTRING_H__
#include <stdint.h>
#include <string.h>
#include <assert.h>
template<typename T = char>
class ZString 
{
public:
	ZString(char* str = "") 
	{
		m_data = NULL; 
		m_len = 0;
	
		assert(str);
		
		m_len = strlen(str);
		m_data = new char[m_len];
		m_data[m_len-1] = '\0'; 
		memcpy(m_data, str, m_len-1);
	}
	
	bool alloc(char* str)
	{
		assert(str);
		
		m_len = strlen(str);
		m_data = new char[m_len];
		m_data[m_len-1] = '\0'; 
		memcpy(m_data, str, m_len-1);
		return true;
	}
	
	ZString(ZString& str) 
	{
		assert(!str.empty());
		
		char* pstr = str.get_ptr();
		alloc(pstr);
	}

	const ZString& operator = (const ZString& str) 
	{
		assert(!str.empty());
		
		char* pstr = str.get_ptr();
		alloc(pstr);
		return *this;
	}

	~ZString() 
	{
		if (m_data) {
			if (m_len > 1)
				delete [] m_data;
			else 
				delete m_data;
		}

		m_len;	
	}

	uint32_t length() 
	{
		return m_len;
	}
	
	T* get_ptr() 
	{
		return m_data;
	}
	
	bool empty() 
	{
		return m_len == 0 ? true : false;	
	}
	
	void append(char c);
	void append(ZString& str);
	
	void erase(uint32_t from, uint32_t len)
	{
		assert(from + len < m_len && len > 0);
		
		do{
			m_data[from] = '\0';
		}while(len-->0);
	}
	
	ZString substr(uint32_t from, uint32_t len)
	{
		assert(from + len < m_len && len > 0);
		
		ZString retstr(m_data+from);
		retstr.erase(m_data+from+len, m_len-from-len);
		return retstr;	
	}

	bool replace(ZString& target, ZString& new_str)
	{
		return true;
	}
	
private:
	T* m_data; 
	uint32_t m_len;
};
#endif
