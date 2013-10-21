#include "../std_inc.hpp"
#include <boost/signals2.hpp>
using namespace boost;
using namespace boost::signals2;

void slots1()
{
	cout << "slot1 called" << endl;
}

void slots2()
{
	cout << "slot2 called" << endl;
}


int main(int argc, char *argv[])
{
	signal<void()> sig;

	sig.connect(&slots1);
	sig.connect(&slots2);
	sig();

    return 0;
}

