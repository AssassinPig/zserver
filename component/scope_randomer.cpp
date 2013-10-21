#include "scope_randomer.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

scope_randomer::scope_randomer(int lower_bound, int upper_bound)
{
	assert(lower_bound>=0 && upper_bound >= lower_bound);
	m_lower_bound = lower_bound;
	m_upper_bound = upper_bound;
	
	//按时间设置随机数种子
	srand((unsigned)time(NULL));
}

int scope_randomer::get_random()
{
	return ((rand()%m_upper_bound) + m_lower_bound);
}

int scope_randomer::get_random(rand_vec& vec, int count)
{
	//count 必须小于区间数
	assert(count<= (m_upper_bound - m_lower_bound));
	if(count == 1)
	{	
		vec.push_back(get_random());
		return 0;	
	}
	
	//[m_lower_bound, m_upper_bound)
	list<int> list_tmp;
	for(int i=m_lower_bound; i<m_upper_bound; ++i)	
	{
		list_tmp.push_back(i);
	}	

	int i = 0;
	int n = m_lower_bound;
	while(count > 0)
	{
		i = rand()%list_tmp.size();	
		list<int>::iterator it = list_tmp.begin();	
		advance(it, i+1);
		n = *(it);				
		vec.push_back(n);
		
		it = list_tmp.erase(it);
				
		--count;	
	}
	
	return 0;
}


