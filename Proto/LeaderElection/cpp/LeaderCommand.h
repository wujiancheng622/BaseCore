#ifndef LEADERCOMMAND_H_
#define LEADERCOMMAND_H_

#include "CommandBase.h"

class CULeaderElectionBean;
class LeaderCommand : public CommandBase
{
	
public:
	LeaderCommand(void);
	virtual ~LeaderCommand(void);

	static bool IsCommandValid(CommandBase *command);


protected:
	virtual void Execute(ThreadCoreBase *executive);
	virtual void Execute(void) = 0;
	static bool IsExecutiveValid(ThreadCoreBase *executive);

	CULeaderElectionBean *m_pInvoker;


};

#endif //LEADERCOMMAND_H_

