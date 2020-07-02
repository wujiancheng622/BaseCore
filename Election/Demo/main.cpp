#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>  
#include <boost/uuid/uuid_generators.hpp>  
#include <boost/uuid/uuid_io.hpp>   
#include "CULeaderElectionBean.h"
#include "ActivemqParseMessage.h"
#include "ActivemqAPI.h"
#include "DataType.pb.h"
#include "ModuleType.pb.h"
#include "ParamMessageBean.pb.h"
using namespace std;
using namespace boost::uuids;  
using namespace com::arges::file::proto;


CULeaderElectionBean test;

//这里是所有mq消息的入口函数
int _ParseMessageFromMq(std::string& strMessageBody)
{
	
	ParamMessage paramMessage;
	paramMessage.ParseFromString(strMessageBody);
	int model=paramMessage.model();
	int srcmodel=paramMessage.srcmodule();
	int type=paramMessage.type();
	int code=paramMessage.code();
	std::string content=paramMessage.content();

	test.OnMessage(type,content);

	return 0;
}

int main()
{
	using namespace cms;

	int ret=_CreateMqLog();
	if (ret!=RET_OK)
	{
		exit(0);
	}

	ret=_InitMq();
	if (ret!=RET_OK)
	{
		exit(0);
	}

	//	初始化线程池
	InitThreadPoolByActivemq(200, 200, 10000);


	test.SetQUEUE_Leader("testfff");
	test.SetTOPIC_Colony("testcol");
	test.SetMqBrokeUrl("failover://tcp://192.168.3.173:61616?connection.sendTimeout=1000");
	test.SetModelNumbers(3);

	random_generator rgen;  
	uuid ranUUID = rgen();                  // 生成一个随机uuid  
	string struuid=to_string(ranUUID);
	test.SetUUID(struuid);

	test.StartService();

	while(true){}
	return 0;
}

