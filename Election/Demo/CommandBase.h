#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include "CrossPlatform.h"
#include "ThreadCoreBase.h"

using namespace BaseCore::Threads;


class DLL_CLASS CommandBase
{
public:
	virtual ~CommandBase(void);
	virtual void Execute(ThreadCoreBase *executive) = 0;


	void SetPriority(int priority);

	int GetPriority();

protected:
	virtual void Execute() = 0;

	CommandBase(void);

	int m_priority;//m_priority 0��ʾ�����ȼ���1��ʾ�����ȼ�
};

#endif //COMMANDBASE_H_

