#include <iostream>
#include <string>
#include <unistd.h>
#include "ActivemqParseMessage.h"
#include "ActivemqAPI.h"
#include "MqLog.h"
#include "ParamMessageBean.pb.h"
#include "DataType.pb.h"
#include "ModuleType.pb.h"
#include "RaiseDustData.pb.h"


using namespace  std;

using namespace cms;
using namespace com::arges::file::proto;


int _ParseMessageFromMq(std::string& str)
{
	printf("_ParseMessageFromMq\n");
	ParamMessage paramMessage;
	paramMessage.ParseFromString(str);
	int model=paramMessage.model();
	int srcmodel=paramMessage.srcmodule();
	int type=paramMessage.type();
	int code=paramMessage.code();
	std::string content=paramMessage.content();


	printf("\nmodel:%d  srcmodel:%d  type:%d  contentlen:%d \n",model,srcmodel,type,content.size());

	RaisuDustData data;
	data.ParseFromString(content);
	printf("\n  id:%s \n",data.devicecode().c_str());
	for (int i=0;i<data.values_size();++i)
	{
		printf("id:%d  value:%f \n",i,data.values(i));
	}
	printf("\n\n\n");

	return 0;
}



int main()
{
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


	printf("run here\n");
	ActivemqConsumer *pConsumer= _CreateActivemqConsumer("failover://tcp://192.168.3.170:61616?connection.sendTimeout=1000","QUEUE_DC");
	while(true)
	{
		printf("run end\n");
		sleep(5);
	}
	
	return 0;

}
