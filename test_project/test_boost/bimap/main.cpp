#include "../std_inc.hpp"
#include <boost/bimap.hpp>
#include <boost/typeof/typeof.hpp>
using namespace boost;

int main(int argc, char *argv[])
{
	bimap<int, string> bm;
	bm.left.insert(make_pair(1, "111"));
	bm.left.insert(make_pair(2, "222"));
	
	bm.right.insert(make_pair("string", 10));
	bm.right.insert(make_pair("bimap", 20));

	//for (bimap<int, string>::iterator pos = bm.left.begin(); pos != bm.left.end(); ++pos)
	for (BOOST_AUTO(pos,bm.left.begin()); pos != bm.left.end(); ++pos)
	{
		cout<<"left["<<pos->first<<"]="<<pos->second<<endl;
	}
		
    return 0;
}

