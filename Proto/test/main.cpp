#include <cstdio>
#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>


//#include "DataType.pb.h"
//#include "ModuleType.pb.h"
#include "ParamMessageBean.pb.h"
using namespace com::arges::file::proto;  




std::string GetParamMessage(int model,int type,int srcModel,std::string content,std::string brokerUrl="",std::string destUrl="",int code=1,std::string doman="1",std::string sessionId="1")
{
	ParamMessage paramMessage;
	paramMessage.set_model(model);
	paramMessage.set_type(type);
	paramMessage.set_srcmodule(srcModel);
	paramMessage.set_content(content);
	paramMessage.set_code(code);
	paramMessage.set_brokerurl(brokerUrl);
	paramMessage.set_desturl(destUrl);
	paramMessage.set_sessionid(sessionId);
	std::string message;
	paramMessage.SerializeToString(&message);
	return message;
}


int main()
{

	std::string ff=GetParamMessage(100,200,100,"ss","ss");

	printf("\n  test hello \n");
	return 0;
}




