#include <cstdio>
#include "LeaderCommand.h"
#include "CULeaderElectionBean.h"



LeaderCommand::LeaderCommand(void):m_pInvoker(NULL)
{
}

LeaderCommand::~LeaderCommand(void)
{
}

void LeaderCommand::Execute(ThreadCoreBase *executive)
{
	if (IsExecutiveValid(executive))
	{
		m_pInvoker=dynamic_cast<CULeaderElectionBean *>(executive);
		Execute();
	}
}

bool LeaderCommand::IsExecutiveValid(ThreadCoreBase *executive)
{
	if (executive)
	{
		CULeaderElectionBean * p = dynamic_cast<CULeaderElectionBean *> (executive);
		if (p)
		{
			return true;
		}
	}
	return false; 
}

bool LeaderCommand::IsCommandValid(CommandBase *command)
{
	if (command)
	{
		LeaderCommand * p = dynamic_cast<LeaderCommand *> (command);
		if (p)
		{
			return true;
		}
	}
	return false; 
}

