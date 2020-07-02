#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
using namespace BaseCore::Clock;

class TimerTest:public TimerListener
{

public:
	TimerTest():m_timer(this)
	{

	}

	~TimerTest()
	{

	}
	virtual void OnTimeOut(int h)
	{
		static int i=0;
		i++;
		cout<<"TimerTest  time out i:"<<i<<endl;
		return;
	}
public:
	Timer m_timer;

};


int main()
{
	using namespace BaseCore::Clock;

	TimerTest my;

	my.m_timer.Start(1000,3);//开启Leader广播
	sleep(5);
	my.m_timer.Start(200,10);//开启Leader广播
	sleep(5);
	std::cout<<" next "<<endl;
	my.m_timer.Start(1000,0);//开启Leader广播

	while(true)
	{

	}
	std::cout << "press ENTER to exit..." << std::endl;
	std::cin.sync();

	return 0;
}
