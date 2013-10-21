#include "../std_inc.hpp"
#include <boost/utility/result_of.hpp>
#include <typeinfo>
#include <boost/typeof/typeof.hpp>
using namespace boost;

#include <math.h>

template<typename T, typename T1>
typename result_of<T(T1)>::type call_func(T t, T1 t1)
{
	return t(t1);
}

int main(int argc, char *argv[])
{
	typedef double (*Func)(double d);
	Func func = sqrt;
	BOOST_AUTO(x, call_func(func, 5.0));
	cout<<typeid(x).name()<<endl;

    return 0;
}

