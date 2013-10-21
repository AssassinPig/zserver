#include "../std_inc.hpp"
#include "../boost_thread.h"
#include "basic_atom.hpp"
using namespace boost;

template <class F>
thread make_thread(F f)
{
	return thread(f);
}

mutex io_mu;

void to_interrupt(atom_int& x, const string& s)
{
	for (int i=0; i<5; ++i) {
		mutex::scoped_lock lock(io_mu);
		cout << s <<endl;
		this_thread::interruption_point();	
	}
}

int main(int argc, char *argv[])
{
	atom_int x;
	thread t(to_interrupt, ref(x), "hello");	
	t.interrupt();
	t.join();
    return 0;
}

