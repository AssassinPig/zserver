#include "../std_inc.hpp"
#include <boost/ref.hpp>
using namespace boost;

struct demo
{
	int f(int a,  int b)
	{
		return a + b;
	}
};

class demo_class
{
private:
	typedef function<void(int)> func_t;
	func_t func;
	int n;
public:
	template<typename Callback>
	void accept(Callback f)
	{
		func = f;
	}

	void run()
	{
		func(n);
	}
};

class call_back_factory
{
public:
	void call_back_func1(int i)
	{
		cout << "call_back_func1" << endl;
		cout << i * 2 << endl;
	}
	
	void call_back_func2(int i, int j)
	{
		cout << "call_back_func2" << endl;
		cout << i * j * 2 << endl;
	}
};

int main(int argc, char *argv[])
{
	int x = 10;
	reference_wrapper<int> rw(x);
	assert(x == rw);
	(int &) rw = 100;
	assert(x == 100);
	
	reference_wrapper<int> rw2(rw);
	assert(rw2.get() == 100);
	
	string str;
	reference_warpper<string> rws(str);
	*rws.get_pointer() = "test reference_wrapper";
	cout << rws.get().size() << endl;

	//use reference_warpper<T> ref(T& t);
	double x = 2.8;
	BOOST_AUTO(rw, cref(x));
	cout << typeid(rw).name() << endl;
	
	string str;
	BOOST_AUTO(rws, ref(str));
	cout << typeid(rws).name() << endl;

	//use is_reference_wrapper<T>
	// unwrap_reference<T> 返回真是类型
	
	//bind member function
	demo a, &ra=a;
	demo *p = &a;
	cout << bind(&demo::f, a, _1, 20)(10) << endl;
	cout << bind(&demo::f, ra, _2, _1)(10, 20) << endl;
	cout << bind(&demo::f, p, _1, _2)(10, 20) << endl;
	
	//搭配factory的用法
	demo_class dc(10);
	call_back_factory cbf;
	dc.accept(bind(&call_back_factory::call_back_func1, cbf, _1));
	dc.run();
	dc.accept(bind(&call_back_factory::call_back_func2, dbf, _1, 5));
	dc.run();
	
    return 0;
}

