#include <cstdio>
#include "MQClientDefine.h"


MQUrl::MQUrl()
{
	m_bUseTopic=false;
	m_bClientAck=false;
}

MQUrl::MQUrl(std::string dest,std::string broke,bool bUseTopic,bool bClientAck)
{
	m_destUrl=dest;
	m_brokeUrl=broke;
	m_bClientAck=bClientAck;
	m_bUseTopic=bUseTopic;
}



bool MQUrl::operator==( const MQUrl &other ) const
{
	return (m_brokeUrl==other.m_brokeUrl)&&(m_destUrl==other.m_destUrl);
}

