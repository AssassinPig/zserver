#include "../std_inc.hpp"
#include "../boost_thread.h"
using namespace boost;

#include <stack>
using namespace std;

mutex io_mu;
template<typename T = int>
class buffer
{
private:
	mutex mu;
	condition_variable_any cond_put;
	condition_variable_any cond_get;
	//stack<int> 
	std::stack<T> stack;
	int un_read, capacity;
	
	bool is_full()
	{	return un_read == capacity;	}
	
	bool is_empty()
	{	return un_read == 0; }
public:
	buffer(size_t n) : un_read(0), capacity(n) {  }
	
	void put(T t)
	{
		{
			mutex::scoped_lock lock(mu);
			while(is_full())
			{
				{
					mutex::scoped_lock lock(io_mu);			
					cout << "full waiting..." << endl;
				}
				cond_put.wait(mu);
			}
			
			stack.push(t);
			++un_read;
		}		
	
		cond_get.notify_one();
	}

	void get(T *t) 
	{
		{
			mutex::scoped_lock lock(mu);
			while(is_empty())
			{	
				{
					mutex::scoped_lock lock(io_mu);
					cout << "empty waiting..." << endl;
				}
				cond_get.wait(mu);
			}
			
			*t = stack.top();
			stack.pop();
			--un_read;
		}

		cond_put.notify_one();
	}
	
};

buffer<int> buf(5);
void producer(int n)
{
	for(int i = 0; i < n; ++i) 
	{
		{
			mutex::scoped_lock lock(io_mu);
			cout << "put " << i << endl;
		}
		buf.put(i);
	}
}

void consumer(int n)
{
	int j;
	for(int i = 0; i < n; ++i)
	{
		{
			buf.get(&j);
			mutex::scoped_lock lock(io_mu);
			cout << "get " << j << endl;
		}
	}
}

int main(int argc, char *argv[])
{
	//typedef singleton_default<thread_group> thread_pool;
	thread t1(bind(producer, 20));
	thread t2(bind(consumer, 10));
	thread t3(bind(consumer, 10));

	t1.join();
	t2.join();
	t3.join();

    return 0;
}

