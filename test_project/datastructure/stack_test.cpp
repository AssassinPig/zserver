#include "stdcpp.hpp"
template<class T>
class stack
{
public:
	stack(int n = 100)
	{
		m_t = NULL;
		m_t = new T[n];
		m_top = -1;
		m_capacity = n;	
	}

	~stack()
	{
		if(m_t)
		{
			m_top = -1;
			delete [] m_t;
			m_t = NULL;
		}
	}

	bool push(T t)
	{
		if(m_top == m_capacity)
			return false;
		m_t[++m_top] = t;
		return true;
	}

	bool pop()
	{
		if(m_top >= 0)
		{	
			--m_top;
			return true;
		}
		
		return false;
	}

	T& top()
	{
		return m_t[m_top];
	}
private:
	T* m_t;
	int m_top;
	int m_capacity;
};

enum {
	enum1 = 3,
};

int main()
{
	return 0;
}
