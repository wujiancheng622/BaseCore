#include "ServerNumsChangCMD.h"
#include "CULeaderElectionBean.h"


ServerNumsChangeCMD::ServerNumsChangeCMD()
{

}

ServerNumsChangeCMD::~ServerNumsChangeCMD()
{

}

void ServerNumsChangeCMD::Execute( void )
{
	m_pInvoker->OnServerNumsAdd(m_addedServerNums);
	m_pInvoker->OnServerReduce(m_removeServerIdVec);
}

void ServerNumsChangeCMD::SetAddedServerNums( int nums )
{
	m_addedServerNums=nums;
}

void ServerNumsChangeCMD::AddRemoveServerId( std::string id )
{
	m_removeServerIdVec.push_back(id);
}


