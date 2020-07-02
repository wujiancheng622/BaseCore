#include <cstdio>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include "./ThreadCoreBase.h"

using namespace boost;
//
using namespace BaseCore::Threads;

class BMSCenterServer :public ThreadCoreBase
{
public:
	BMSCenterServer(void)
	{
	}
public:
	~BMSCenterServer(void)
	{

	}

	void Run()
	{

			printf("in run \n");
			ThreadCoreBase::Sleep(1000);    // 这种更好用 

	}

private:

};




int main()
{
	BMSCenterServer bser;
	bser.Start();

	
	for (int i=0;i<2000;++i)
	{
		printf("in main \n");

		//ThreadCoreBase::Sleep(2000);    // 这种更好用 
		usleep(1000 *1000);

        /*
		if (i==2)
		{
			bser.Stop();
		}
		if(i>2&&i<5)
		{
			printf("i>2 and i<5\n");
		}
		if(i==5)
		{
			printf("i==10\n");
			bser.Start();
		}
		
		if(i>5&&i<8)
		{
			bser.Stop();
			printf("i>5 and i<8\n");
		}
		if(i>=8)
		{
			printf("i>=8\n");
			bser.Start();
		}
		
        */		
		
	}
	return 0;
}
