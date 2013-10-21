#ifndef _BINARY_NUM_H__ 
#define _BINARY_NUM_H__
template<unsigned long N>
class binary
{
public:
	const static unsigned long value = (binary<N/10>::value << 1 | N%10 );
};

template<>
class binary<0>
{
public:
	const static unsigned long value = 0;
};

#endif //_BINARY_NUM_H__
