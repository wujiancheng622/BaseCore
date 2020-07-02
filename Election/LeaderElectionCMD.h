#ifndef LEADERELECTIONCMD_H_
#define LEADERELECTIONCMD_H_


#include <vector>
#include <string>
#include "LeaderCommand.h"

class BMSHeartTimeOutCMD:public LeaderCommand
{

public:
	BMSHeartTimeOutCMD();
	~BMSHeartTimeOutCMD();


private:
	virtual void Execute(void);

};




class RequestVoteFromOtherBMSCMD:public LeaderCommand
{

public:
	RequestVoteFromOtherBMSCMD();
	~RequestVoteFromOtherBMSCMD();

private:
	virtual void Execute(void);

};

class CountCurTermWinVoteCMD:public LeaderCommand
{

public:
	CountCurTermWinVoteCMD();
	~CountCurTermWinVoteCMD();

private:
	virtual void Execute(void);

};





#endif//LEADERELECTIONCMD_H_