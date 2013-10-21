//#include "scope_randomer.hpp"
#include "set_randomer.hpp"
#include <iostream>
#include <algorithm>
#include "zstream.hpp"
#include <memory.h>

#include "zstring.hpp"
#include "zconfig.hpp"
#include <stack>
using namespace std;

void print_elem(int i)
{
	cout<<i<<"\t";
}

void print_elem(char a[], int i)
{
	for(int j=0; j<i; ++j) {
		printf("[%d]=%c\n", j, a[j]);
	}
}

class Base
{
public: 	
	//virtual ~Base() { cout << "~Base()" <<endl; }
	~Base() { cout << "~Base()" <<endl; }
};

class Derived : public Base {
public:
	~Derived() { cout << "~Derived()" <<endl; }
};

int foni(int n)
{
	assert(n>0);
	if(n == 1 || n == 2) return 1;
	return foni(n-1) + foni(n-2);
}

int foni_2nd(int n)
{
	assert(n>0);
	std::stack<int> stack;
	int sum = 0;
	stack.push(n);
	while(!stack.empty()) {
		int top = stack.top();
		if (top == 1 || top == 2) {
			sum += 1;
			stack.pop();
		} else {
			stack.pop();
			stack.push(top-1);		
			stack.push(top-2);		
		}	
	}

	return sum;
}

int main()
{
	/*
	scope_randomer rdmer(10001, 20001);
	vector<int> vec;
	rdmer.get_random(vec, 10);
	for_each(vec.begin(), vec.end(), print_elem);
	cout<<endl;	
	*/

	//set_randomer<int, list<int> > rdmer;

/*	
	set_randomer<> rdmer;
	for(int i=0; i<10; ++i)	
	{
		if(!rdmer.insert_rand(i))
			cout<<"i "<<i<<"insert falied"<<endl;
	}

	cout<<"set_randomer.count() = "<<rdmer.get_set_count()<<endl;

	vector<uint32_t> vec;
	rdmer.get_random(vec, rdmer.get_set_count());
	
	for_each(vec.begin(), vec.end(), print_elem);
	cout<<endl;	
*/

/*	
	ZStream stream;		
	stream.malloc(10);
	stream.print_data();
	
	char a[2]={'a', 'b'};
	stream.input(a, 2);		
	stream.print_data();
	
	char b[2];
	memset(b, 0, 2);
	stream.output(b, 2);
	stream.print_data();
	print_elem(b, 2);
*/

/*
	char a[]="Hello World!";	
	//char b[12];
	char* b = new char[strlen(a)+1];
	strcpy(b,a);
	if (strcmp(a,b)==0) {
		printf("a=b\n");
	}
		
	printf("sizeof(a) = %d\n",sizeof(a));

	Base* pBase = new Derived;
	delete pBase;

	char c[10];	
	memset(c, 0, sizeof(c));
	//sprintf(c, "abcded");
	sprintf(c, "abcdedf");
	
	int len=strlen(c);
	for (int i=0; i<len/2+1; ++i) {
		char tmp = c[i];
		c[i] = c[len-1-i];	
		c[len-1-i] = tmp;
	}

	for (int i=0; i<len; ++i) {
		printf("%c,", c[i]);
	}
		
	printf("\n");
	
	int i=0;
	int j=len-1;	
	do {
		char tmp = c[i];
		c[i] = c[j];	
		c[j] = tmp;
	} 
	while(i++<=j--);
	
	for (int i=0; i<len; ++i) {
		printf("%c,", c[i]);
	}
	printf("\n");

	const char *p;
	char c1='a';
	char c2='b';
	p=&c1;	
	p=&c2;	
	
	char const* p2;
	//char* const p3; //g++ can not pass
	
	char content[10];
	char from[]="abc 0";
	int n;
	sscanf(from, "%s %d", content, &n);//& 符号不可忘记
	printf("from=%s\n", from);
	printf("content=%s, n=%d\n", content, n);
	
	union V {
		struct X {
			unsigned char s1:2;
			unsigned char s2:3;
			unsigned char s3:3;
		} x;
		unsigned char c;
    } v;

    v.c = 100;
    printf("v.x.s3=%d\n", v.x.s3);

	struct A 
	{ 
			char t:4; 
			char k:4; 
			unsigned short i:8; 
			unsigned long m; 
	}; 

	printf("sizeof(A)=%u\n", sizeof(A));
	printf("sizeof(long)=%u\n", sizeof(long));

*/

	//zconfig test
	/*
	zconfig config;
	config.load_file("./config.txt");
	config.print_all();
	*/	
	
	//foni foni_2nd test
	int n = 10;
	printf("foni(%d) = %d, foni_2nd(%d) = %d\n", n, foni(n), n, foni_2nd(n)); 

	return 0;
}

