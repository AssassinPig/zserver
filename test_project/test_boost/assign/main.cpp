#include "../std_inc.hpp"
#include <boost/assign.hpp>
using namespace boost;
//this is important
using namespace boost::assign;

int main(int argc, char *argv[])
{
/*
	//use += operator
	vector<int> v;
	v += 1,2,3,4,5,6;
	cout<<v.size()<<endl;

	//use push_back
	push_back(v), 7,8,9,10;	
	cout<<v.size()<<endl;

	push_back(v)(11),(12),(13),(14);
	cout<<v.size()<<endl;

	//use push_front(container)(value), (value)
	list<string> l;
	push_front(l)("cpp"), ("java"), ("c#"), ("python");
	
	//use insert
	set<double> s;
	insert(s) (3.14) (0.618) (1.732);

	map<int, string> m;
	insert(m) (1, "one") (2, "two");

	//use push_front(container)= value, value;
	deque<string> d;
	push_front(d)()="cpp", "java", "c#", "python";
	
	assert(d.size()==5);
	
	//use map_list_of		
	map<int, int> m1 = map_list_of(1,2)(3,4)(5,6);
	map<int, string> m2 = map_list_of(1,"one")(2,"two");
*/	
	//use repeat
	vector<int> v = list_of(1).repeat(3,2)(3)(4)(5);
	//v=1, 2,2,2 3,4,5
	multiset<int> ms;
	insert(ms).repeat_fun(5, &rand).repeat(2,1), 10;
	//x,x,x,x,x, 1,1, 10
	
	deque<int> d;
	push_front(d).range(v.begin(), v.begin()+5);
	//d=3,2,2,2,1
	
    return 0;
}

