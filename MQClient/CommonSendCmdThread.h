#ifndef COMMONSENDCMDTHREAD_H_
#define COMMONSENDCMDTHREAD_H_


#include <boost/shared_ptr.hpp>
#include "ThreadCoreBase.h"
#include "MQClientDefine.h"

namespace BaseCore
{
	namespace Threads
	{
		class Mutex;
	}
}

class CommonSendCmdThread:public BaseCore::Threads::ThreadCoreBase
{
public:

	static CommonSendCmdThread * Instance();
	~CommonSendCmdThread();

	virtual void Run();
	void ProcessCmd();
	void PushMQCmd(MQCmd cmd);

	void ClearAllCmd();

	static  boost::shared_ptr<CommonSendCmdThread> m_stInstance;

protected:
	CommonSendCmdThread();
private:
	MQCmdDeque m_MQCmdDeque;
	static boost::shared_ptr<BaseCore::Threads::Mutex> m_spMutex;
};


#endif //COMMONSENDCMDTHREAD_H_