#ifndef _SCOPE_RANDOMER_H__
#define _SCOPE_RANDOMER_H__
#include <limits>
#include <vector>
#include <list>
using namespace std;

//从一个范围内获取n个随机的不重复的数字
//[m_lower_bound, m_upper_bound)
class scope_randomer
{
public:
	typedef vector<int> rand_vec;
public:
	scope_randomer(int lower_bound = 0, int upper_bound = numeric_limits<int>::max());
	int get_random();
	
	//[m_lower_bound, m_upper_bound)
    int get_random(rand_vec& vec, int count = 1);			
private:
	int m_lower_bound;
	int m_upper_bound;
};


#endif //_SCOPE_RANDOMER_H__ 
