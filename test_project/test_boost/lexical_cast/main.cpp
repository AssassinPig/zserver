#include "../std_inc.hpp"
#include <boost/lexical_cast.hpp>
using namespace boost;

int main(int argc, char *argv[])
{
	std::string  s= "12";
	int i = lexical_cast<int>(s);
	cout << "i = " << i << endl;

    return 0;
}

