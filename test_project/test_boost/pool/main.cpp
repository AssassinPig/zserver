#include "../std_inc.hpp"
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
using namespace boost;

struct demo_class
{
public:
	int a, b, c;
	demo_class(int x = 1, int y = 2, int z = 3) : a(x), b(y), c(z)
	{
		cout<<"construct"<<endl;
	}

	~demo_class() 
	{
		cout<<"desconstruct"<<endl;
	}
};

typedef singleton_pool<demo_class, sizeof(demo_class)> spl;

int main(int argc, char *argv[])
{
/*
	pool<> pl(sizeof(int));
	int *p = (int *)pl.malloc();
	assert(pl.is_from(p));
	pl.free(p);
	for (int i=0; i<100; ++i) 
	{
		pl.ordered_malloc(10);
	}		
*/

/*	
	object_pool<demo_class> pl;
	demo_class *p = pl.malloc();
	assert(pl.is_from(p));	
	
	assert(p->a!=1 || p->b!=2 || p->c!=3);
	
	p = pl.construct(7,8,9);
	assert(p->a == 7);
	
	object_pool<string> pls;
	for (int i=0; i<10; ++i)
	{
		string *ps = pls.construct("hello object pool");
		cout<< *ps <<endl;
	}
*/	

//singleton_pool case 
//the object will be initialized before main(), so you will not see construct string!!!
/*
	demo_class *p = (demo_class*)spl::malloc();	
	assert(spl::is_from(p));
	spl::release_memory();
*/
    return 0;
}

