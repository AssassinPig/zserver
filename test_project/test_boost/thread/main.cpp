#include "../std_inc.hpp"
#include "../boost_thread.h"
using namespace boost;

template <class F>
thread make_thread(F f)
{
	return thread(f);
}


mutex io_mu;
//void printing(atom_int& x, const string& s)
void printing(const string& str)
{
	for (int i=0; i<5; ++i) {
		mutex::scoped_lock lock(io_mu);
		cout << str <<endl;
	}
}

int main(int argc, char *argv[])
{
	//atom_int x;
	
	//thread(printing, ref(x), "hello");
	//thread(printing, ref(x), "boost");

	thread t1(printing, "hello");
	thread t2(printing, "boost");
	
	//t1.time_join(posix_time::seconds(1)); //等待1秒之后返回
	t2.join();							  //一直等待
	t1.detach();						  //对象与线程分离, 分离后，线程继续执行
	//当t1对象销毁的时候，也会自动detach的	
	

	function<void()> f = bind(printing, "bind fun");
	thread t3(f);
	
	//让出时间片
	thread::yield();
	//sleep 本线程
	thread::sleep(get_system_time() + posix_time::seconds(1));
	//打印出目前并发的线程数
	cout << thread::hardware_concurrency() << endl;
	//本线程的id	
	cout << this_thread::get_id();

	sleep(1);
    return 0;
}

