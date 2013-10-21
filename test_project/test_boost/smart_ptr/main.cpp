//#include <iostream>
//#include <boost/scoped_ptr.hpp>
//using namespace std;
#include "../std_inc.hpp"
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

class shared
{
private:
	shared_ptr<int> p;
public:
	shared(shared_ptr<int> p) : p(p) {}
	void print()
	{
		cout << "count: " << p.use_count() 
			<< "v = " << *p << endl;
	}
};

void print_func(shared_ptr<int> p) 
{
	cout << "count: " << p.use_count() 
		<< "v = " << *p << endl;
}

int main(int argc, char *argv[])
{
/*
    boost::scoped_ptr<int> i(new int);
    *i = 2;
    
    cout << *i << endl;
*/	

//shared_ptr case 1
/*
	shared_ptr<int> sp(new int(10));
	assert(sp.unique()); //only sp own the value
	shared_ptr<int> sp2 = sp;
	assert(sp == sp2 && sp.use_count() == 2); //both sp and sp2 have the value then use count is 2
	*sp2 = 100;
	assert(*sp == 100); //modify sp2`s value and sp`s also was modified
	sp.reset();			//clear the point
	assert(!sp);		//and sp will have NULL
*/	

//shared_ptr case 2 
/*
	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);
	
	s1.print();
	s2.print();
	
	*p = 20;
	print_func(p);
	
	s1.print();	
*/
//make shared_ptr
//	shared_ptr<string> sp = make_shared<string>("make_shared");
	
		
    return 0;
}

