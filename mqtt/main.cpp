#include "MQTTModule.h"

void testPub(){
	MQTTModule pub;
	pub.init("tcp://192.168.17.143:1883","MQTT_Examples",MQTTModule::PUBLICATION,"publiaction");
	pub.Start();
	BaseCore::Threads::ThreadCoreBase::Sleep(3000);
	while(true)
	{
		printf("in main \n");
		BaseCore::Threads::ThreadCoreBase::Sleep(1000);
		pub.sendData("ahaha");
	}
}

void testSub(){
	MQTTModule pub;
	pub.init("tcp://192.168.17.143:1883","MQTT_Examples",MQTTModule::SUBSCRIPTION,"subscription");
	pub.Start();
	BaseCore::Threads::ThreadCoreBase::Sleep(3000);
	while(true)
	{
		printf("in main \n");
		BaseCore::Threads::ThreadCoreBase::Sleep(1000);
		std::vector<string> outPutData;
		if(pub.getMessage(outPutData))
		{
			for(int i=0;i<outPutData.size();++i){
				printf(" data:%s \n",outPutData[i].c_str());
			}
		}else{
			printf("get data failed \n");
		}
	}
}

void testPubSub{
	MQTTModule pub;
	pub.init("tcp://192.168.17.143:1883","MQTT_Examples",MQTTModule::PUBLICATION,"publiaction");
	pub.Start();
	MQTTModule pub;
	pub.init("tcp://192.168.17.143:1883","MQTT_Examples",MQTTModule::SUBSCRIPTION,"subscription");
	pub.Start();
	BaseCore::Threads::ThreadCoreBase::Sleep(3000);
	while(true)
	{
		printf("in main \n");
		BaseCore::Threads::ThreadCoreBase::Sleep(1000);
		pub.sendData("ahaha");
	}

}


int main()
{
	//testPub();
	testSub();
	return 0;
}
