#include "stdcpp.hpp"
#include "binary_num.hpp"
#include <typeinfo>
#include "policy.hpp"


template <class T>
class Iterator
{
public:
	typedef T value_type;
	Iterator(T t) {}
};

template <class T>
class traits
{
public:
	traits(T t) {}
	void fun()
	{
		typename T::value_type value;
	    //cout<<typeid(value)<<endl;	
	}
};


int main()
{
	cout<<binary<1000>::value<<endl;	
	
	Iterator<int> it(10);	
	traits<Iterator<int> > tr(it); 

	int num[] = { 1, 2, 3, 4, 5 };	
	cout<<Accum<int, SumPolicy>::accum(&num[0], &num[5])<<endl;
	cout<<Accum<int, MultiPolicy>::accum(&num[0], &num[5])<<endl;

	return 0;
}
