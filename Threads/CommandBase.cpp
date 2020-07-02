#include "CommandBase.h"

CommandBase::CommandBase(void)
{
	m_priority=0;
}

CommandBase::~CommandBase(void)
{
}


void CommandBase::SetPriority( int priority )
{
	m_priority=priority;
}

int CommandBase::GetPriority()
{
	return m_priority;
}

