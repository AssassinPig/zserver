#include "../std_inc.hpp"
#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>

#include <boost/typeof/typeof.hpp>

#include <boost/optional.hpp>

using namespace boost;

int main(int argc, char *argv[])
{
//	BOOST_TYPEOF(2.0*3) x = 2.0*3;

	optional<int> op0;
	optional<int> op1(none);
	assert(!op0);
	
	assert(op0 == op1);
	assert(op0.get_value_or(253) == 253);
	
	optional<string> ops("test");
	cout<< *ops <<endl;
	
	vector<int> v(10);
	optional<vector<int>& > opv(v);
	opv->push_back(5);
	assert(opv->size() == 11);
	
	opv = none;
	assert(!opv);
	
    return 0;
}

