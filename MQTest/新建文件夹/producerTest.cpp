#include <iostream>
#include <string>
#include <unistd.h>
#include "ActivemqParseMessage.h"
#include "ActivemqAPI.h"
#include "MqLog.h"
#include "ParamMessageBean.pb.h"
#include "DataType.pb.h"
#include "ModuleType.pb.h"
#include "DataType.pb.h"
#include "DevInfo.pb.h"


using namespace  std;

using namespace cms;
using namespace com::arges::file::proto;
using namespace com::arges::devinfo::proto;

int _ParseMessageFromMq(std::string& str)
{
	printf("_ParseMessageFromMq\n");
	return 0;
}



int main()
{

	int ret=hlog_init();
	if (ret!=RET_OK)
	{
		//打印输出提示初始化hlog库失败
		exit(0);
	}

	ret=_CreateMqLog();
	if (ret!=RET_OK)
	{
		//打印输出提示实例化log对象失败
		hlog_uninit();
		exit(0);
	}

	ret=_InitMq();
	if (ret!=RET_OK)
	{
		//打印输出提示初始化mq库失败
		hlog_uninit();
		exit(0);
	}

	//	初始化线程池
	InitThreadPoolByActivemq(200, 200, 10000);


	printf("run here\n");
	ActivemqProducer *m_pETSProducer=_CreateActivemqProducer("failover://tcp://127.0.0.1:61616?connection.sendTimeout=1000","DIS_TO_BMS_TEST" );//192.168.3.136

	ParamMessage paramMessage;

	std::ostringstream ostreamModel;
	ostreamModel<< BMS;
	paramMessage.set_model(ostreamModel.str());
	printf("model:%s\n",paramMessage.model().c_str());

	std::ostringstream ostreamType;
	ostreamType<< 200;
	paramMessage.set_type(ostreamType.str());
	printf("type:%s\n",paramMessage.type().c_str());

	std::ostringstream ostreamSrcModel;
	ostreamSrcModel<<C_DIS_SERVER;
	paramMessage.set_srcmodule(ostreamSrcModel.str());
	printf("srcModel:%s\n",paramMessage.srcmodule().c_str());

	paramMessage.set_code("1");

	std::string content;

	DevInfo  devInfo;
	devInfo.set_deviceid("10001");
	devInfo.set_devip(std::string("127.0.0.1"));
	devInfo.set_devport(0);
	devInfo.set_devtype(3);
	devInfo.set_provider("Aleph");
	devInfo.set_model("AL_7416IP");
	devInfo.SerializeToString(&content);

	paramMessage.set_content(content);

	std::string strMessage;
	paramMessage.SerializeToString(&strMessage);


	_SendBytesMessage(m_pETSProducer,strMessage);
	printf("run end\n");
	while(true)
	{
		sleep(5);
	}
	
	return 0;

}
