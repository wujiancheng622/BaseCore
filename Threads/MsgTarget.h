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

	//������ŵ����������
	int PushCommand(CommandBase *pCommand);


	//��ȡ��ǰ����ĸ���
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

