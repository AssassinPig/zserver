#include <stdio.h>
#include <stdlib.h>
#include "../std_inc.hpp"
#include <boost/swap.hpp>
using namespace boost;

template<typename T>
void print_array(const T a[], int len)
{
	printf("a[]=");
	for(int i=0; i<len; ++i)
	{
		printf("%d", a[i]);
		if(i!=len-1)
			printf(",");
	}

	printf("\n");
} 

class point
{
private:
	int x, y, z;
public:
	explicit point(int a=0, int b=0, int c=0): x(a), y(b), z(c) {}
	
	void print() const
	{	cout<<x<<","<<y<<","<<z<<endl;	}
	
	void swap(point& p)
	{
		std::swap(x, p.x);	
		std::swap(y, p.y);	
		std::swap(z, p.z);
	}
};

//for case 1
/*
namespace std 
{
	template<>
	void swap(point& a, point& b)
	{
		a.swap(b);
	}
};
*/

//for case 2, you will also add this fun to namespace boost invoid pollution
void swap(point &x, point &y)
{
	x.swap(y);
} 

int main(int argc, char *argv[])
{
	const int len=10;
	int a1[len];
	int a2[len];
	std::fill_n(a1, len, 5);
	std::fill_n(a2, len, 10);

	print_array(a1, len);
	print_array(a2, len);

	boost::swap(a1, a2);
	
	print_array(a1, len);
	print_array(a2, len);
		
	//specialization some class
	point p1(1,2,3);
	point p2(4,5,6);
	//case 1: use specialize fun add namespace std 
	/*
	point p1(1,2,3);
	point p2(4,5,6);
	std::swap(p1,p2);	
	p1.print();
	p2.print();
	boost::swap(p1,p2);
	p1.print();
	p2.print();
	*/
	
	//case 2: boost will use the global swap fun 
	p1.print();
	p2.print();
	boost::swap(p1,p2);
	p1.print();
	p2.print();
	
    return 0;
}

