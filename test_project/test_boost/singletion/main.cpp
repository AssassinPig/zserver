#include "../std_inc.hpp"
#include <boost/serialization/singleton.hpp>

using namespace boost;
//using boost::details::pool::singleton_default;
using namespace boost::serialization;

//case 2 use as inherit
class SqlDB_t : public singleton<SqlDB_t>
{
public:
	static void connect()
	{

	}

	static void exec(const char* sqlstr)
	{

	}

	static void query(const char* sqlstr)
	{

	}
};

typedef SqlDB_t SqlDB;

//case 1 use as template
//typedef singleton_default<SqlDB_t> SqlDB;


int main(int argc, char *argv[])
{
	const SqlDB& DB = SqlDB::get_const_instance();
	DB.connect();
	DB.exec("insert into table values(1,2,3,4)");
	DB.query("select * from table");

    return 0;
}

