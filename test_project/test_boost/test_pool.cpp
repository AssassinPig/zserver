#include "stdcpp.hpp"
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
using namespace boost;
class A
{};
void test_pool()
{
	cout<<"Init pool..."<<endl;
	pool<> p(10*sizeof(A));
	for(int i=0; i<10; ++i)	
	{
		A* a = (A*)p.malloc();
	}
	p.purge_memory();
	
	cout<<"Init object pool"<<endl;
	
	object_pool<A> q;
	for(int i=0; i<10; ++i)	
	{
		A* a = q.construct();
	}
	
	return; 
}
int main()
{
	test_pool();
	return 0;
}
