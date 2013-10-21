#include "../std_inc.hpp"
#include "../boost_thread.h"
#include <boost/serialization/singleton.hpp>
using namespace boost;

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
	//typedef singleton_default<thread_group> thread_pool;
	thread_group tg;
	function<void()> f = bind(printing, "bind fun");
	//thread_pool::instance().create_thread(f);
	//thread_pool::instance().join_all();
	
	tg.create_thread(f);
	tg.join_all();
	
	sleep(1);
    return 0;
}

