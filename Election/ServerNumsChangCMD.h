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
	int m_addedServerNums;//����ӵķ������
	std::vector<std::string> m_removeServerIdVec;//���Ƴ��ķ���id
};




#endif//SERVERNUMSCHANGECMD_H_