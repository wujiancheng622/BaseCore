#ifndef SERVERNUMSCHANGECMD_H_
#define SERVERNUMSCHANGECMD_H_


#include <vector>
#include <string>
#include "LeaderCommand.h"

class ServerNumsChangeCMD:public LeaderCommand
{

public:
	ServerNumsChangeCMD();
	~ServerNumsChangeCMD();

	void SetAddedServerNums(int nums);

	void AddRemoveServerId(std::string id);

private:
	virtual void Execute(void);
	int m_addedServerNums;//新添加的服务个数
	std::vector<std::string> m_removeServerIdVec;//被移除的服务id
};




#endif//SERVERNUMSCHANGECMD_H_