#ifndef _SET_RANDOMER_H__
#define _SET_RANDOMER_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include <vector>
#include <list>

#include <stdint.h>

template<class T = uint32_t, class container = std::list<T> >
class set_randomer
{
public:	
	typedef	std::list<T> rand_set;
	typedef std::vector<T> rand_vec;

	set_randomer()
	{
		//按时间设置随机数种子
		srand((unsigned)time(NULL));
	}	

	bool insert_rand(const T& t)
	{
		return (m_list.insert(m_list.begin(), t) != m_list.end()); 
	}
	
	uint32_t get_set_count()
 	{
		 return m_list.size();
	}

	void clear_set()
	{
		m_list.clear();
	}
	
	void get_random(rand_vec& vec, uint32_t count = 1)
	{
		//count 必须小于区间数
		assert(count > 0 && count <= m_list.size());
	
		//scope_randomer randomer(0, m_list.size());
		//[m_lower_bound, m_upper_bound)
	
		uint32_t i = 0;
		T t;
		while(count > 0)
		{
			i = rand()%m_list.size();	
			typename rand_set::iterator it = m_list.begin();	
			advance(it, i);
			
			t = *(it);				
			vec.push_back(t);
			
			it = m_list.erase(it);
		
			--count;	
		}
	
		return;	
	}

private:
	container m_list;
};
#endif //_SET_RANDOMER_H__
