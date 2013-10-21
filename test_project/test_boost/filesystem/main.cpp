#include "../std_inc.hpp"
#include <boost/filesystem.hpp>
using namespace boost;
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
	namespace fs = boost::filesystem;
	
	path ptest = "./test";
	
	if (exists(ptest)) {
		if (is_empty(ptest)) {
			fs::remove(ptest); //remove 只能删除空目录和文件
		} else {
			remove_all(ptest);
		}
	}

	assert(!exists(ptest));
	create_directory(ptest);
	
	copy_file("./main.cpp", ptest / "test.cpp");
	assert(exists(ptest / "test.cpp"));
	rename(ptest / "test.cpp",  ptest / "b.txt");
	assert(exists(ptest / "b.txt"));
	
	create_directories(ptest / "sub_dir1" / "sub_dir2");

    return 0;
}

