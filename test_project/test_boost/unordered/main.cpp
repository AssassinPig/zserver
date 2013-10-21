#include "../std_inc.hpp"

//#include <ext/hash_set>
#include <boost/unordered_set.hpp>

#include <boost/unordered_map.hpp>
#include <boost/assign.hpp>
using namespace boost;

template<typename T>
void hash_func()
{
	using namespace boost::assign;
	
	T s = (list_of(1), 2,3,4,5);
	for (typename T::iterator p = s.begin(); p != s.end(); ++p)
	{
		cout<< *p <<endl;
	}		

	cout<<endl;
	cout<<s.size()<<endl;
	
	s.clear();	
	cout<<s.empty()<<endl;
	
	s.insert(8);
	s.insert(45);
	
	cout<< s.size() <<endl;
	cout<< *s.find(8) <<endl;
	
	s.erase(45);
}

int main(int argc, char *argv[])
{
	//test unordered_set 
	//hash_func<stdhash_set<int> >();
	hash_func<unordered_set<int> >();
	
	unordered_map<int, string> um = map_list_of(1, "one") (2."two") (3, "three");
	
	um.insert(make_pair(10, "ten"));
	cout<<um[10]<<endl;
	um[11]="eleven";
	um[15]="fifteen";
	
	BOOST_AUTO(p, um.begin());
	for (p; p != um.end(); ++p)
	{
		cout << p->first << "-" << p->second << ",";
	}
	cout<<endl;
	
	um.erase(11);	
	cout<<um.size()<<endl;
	
	hash_map<int, string> hm = map_list_of(4, "four") (5, "five") (6, "six");
	BOOST_AUTO(q, hm.begin());	
 	for (q; q!=hm.end(); ++q)
	{	cout << q-first << "-"<< q->second <<",";	}

	cout<<endl;	

	//get bucket size
	//uint32_t bucket_count = um.bucket_count() 

	//assess bucket
	//um.bucket_size(i)

	//rehash resize the size of buckets
	//um.rehash(200)

    return 0;
}

