#ifndef MSGTARGET_H_
#define MSGTARGET_H_ 

#include <list>
#include <deque>
#include "CrossPlatform.h"
#include "ThreadCoreBase.h"


class CommandBase;


class DLL_CLASS CMsgTarget : public BaseCore::Threads::ThreadCoreBase
{
public:
	CMsgTarget(void);
	virtual ~CMsgTarget(void);

	//将命令放到命令队列中
	int PushCommand(CommandBase *pCommand);


	//获取当前命令的个数
	int GetCommandNums();

	void ClearAllCmd();
protected:
	virtual void Run();

private:
	virtual int OnReceiveCommand(CommandBase *pMsg) = 0;

	BaseCore::Threads::Mutex   m_mtxCommand;
	std::deque< CommandBase * > m_deqCommand;
};

#endif //MSGTARGET_H_

