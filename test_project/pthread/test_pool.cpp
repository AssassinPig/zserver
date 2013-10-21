#include "thread_pool.hpp"
#include <iostream>
using namespace std;

int main()
{
	CWorkTask taskObj;
 	char szTmp[] = "this is the first thread running,haha success";
 	taskObj.SetData((void*)szTmp);

 	CThreadPool threadPool(10);
 	for(int i = 0;i < 11;i++)
	{
  		threadPool.AddTask(&taskObj);
 	}

 	while(1)
 	{
  		sleep(120);
	}

 	return 0;
}


