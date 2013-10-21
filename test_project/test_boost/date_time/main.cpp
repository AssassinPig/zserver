//#include <iostream>
//#include <boost/scoped_ptr.hpp>

//using namespace std;
#include "../std_inc.hpp"

#include <fstream>

#include <boost/timer.hpp>
#include <boost/progress.hpp>
using namespace boost;

int main(int argc, char *argv[]) {
/*
    boost::scoped_ptr<int> i(new int);
    *i = 2;
    
    cout << *i << endl;
*/
	
/*
	timer t;
	cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;

	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
	
	int n = 0;
	while(n++<100)
		cout << "now time elapsed:" << t.elapsed() << "s" << endl;
*/	

/*
{
	boost::progress_timer t;
	int n = 0;
	while(n++<100)
		cout << "now time elapsed:" << t.elapsed() << "s" << endl;
}		
*/

	vector<string> v(100);
	ofstream fs;
	fs.open("test.txt", ios_base::app);
	
	progress_display pd(v.size());
	
	vector<string>::iterator pos;
	for (pos = v.begin(); pos != v.end(); ++pos) 
	{
		fs << *pos <<endl;
		++pd;
	}
	fs.close();
    return 0;
}

