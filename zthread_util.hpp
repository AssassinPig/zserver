#ifndef _ZTHRAED_UTIL_H__
#define _ZTHRAED_UTIL_H__

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>

template<typename T>
boost::thread make_thread(T fun, void* data)
{
	return boost::thread(fun, data);
}

//template<typename T>
//boost::thread make_thread(boost::function<T> f)
//{
//	return boost::thread(f);
//}


#endif 
