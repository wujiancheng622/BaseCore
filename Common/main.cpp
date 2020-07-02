//ʹ��pthread�߳̿�  
#include <stdio.h>            
#include <string.h>           
#include <unistd.h>          
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <pthread.h>  
#include <stdlib.h>    
#include "Coroutine.h"



using namespace BaseCore::Common;

struct args 
{
	int n;
};

static void foo(struct schedule * S, void *ud) 
{
	struct args * arg = (struct args *)ud;
	int start = arg->n;
	int i;
	for (i=0;i<5;i++) {
		printf("coroutine %d : %d\n",coroutine_running(S) , start + i);
		coroutine_yield(S);
	}
}

static void test(struct schedule *S) 
{
	struct args arg1 = { 0 };
	struct args arg2 = { 100 };

	int co1 = coroutine_new(S, foo, &arg1);
	int co2 = coroutine_new(S, foo, &arg2);
	printf("main start\n");
	while (coroutine_status(S,co1) && coroutine_status(S,co2)) 
	{
		coroutine_resume(S,co1);
		coroutine_resume(S,co2);
	} 
	printf("main end\n");
}

#define PORT 1234           //�������˿�  
#define BACKLOG 5           //listen���еȴ���������  
#define MAXDATASIZE 1024    //��������С  


typedef struct  _ARG  
{  
	int connfd;  
	struct sockaddr_in client;   
}ARG;                    //�ͻ��˽ṹ��  


int main()  
{  

	struct schedule * S = coroutine_open();
	int listenfd, connectfd;     //socket������  
	ARG *arg;            //�ͻ��˽ṹ�����  
	struct sockaddr_in server;     //��������ַ��Ϣ�ṹ��  
	struct sockaddr_in client;     //�ͻ��˵�ַ��Ϣ�ṹ��  
	int sin_size;  

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //����socket�����������ͻ��˵�socket  
		perror("Creating socket failed.");  
		exit(1);  
	}  

	int opt = SO_REUSEADDR;          
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));    //����socket���ԣ��˿ڿ�������  
	//��ʼ����������ַ�ṹ��  
	bzero(&server,sizeof(server));  
	server.sin_family=AF_INET;  
	server.sin_port=htons(PORT);  
	server.sin_addr.s_addr = inet_addr("192.168.3.173");

	if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) //����bind���󶨵�ַ�Ͷ˿�  
	{    
		perror("Bind error.");  
		exit(1);  
	}     

	if(listen(listenfd,BACKLOG) == -1)//����listen����ʼ����  
	{      
		perror("listen() error\n");  
		exit(1);  
	}  

	printf(" listen success \n");
	sin_size=sizeof(struct sockaddr_in);  

	while(1) 
	{  
		if ((connectfd = accept(listenfd,(struct sockaddr *)&client,(socklen_t *)&sin_size))==-1) 
		{                      
			//����accept����������������ӵĿͻ���������  
			perror("accept() error\n");  
			exit(1);  
		}  
		/* �ӿͻ��˵��׽�������ȡ��IP��ַ ��������Ϣ*/  
		int clientip = client.sin_addr.s_addr;  
		printf("Client ip : %d.%d.%d.%d\n",clientip&255,(clientip>>8)&255,  (clientip>>16)&255,(clientip>>24)&255);  
		printf("Client prot : %d\n",ntohs(client.sin_port));  

		char  buffer[256]={0};
		send(connectfd,"hello world",strlen("hello world"),0);
		recv(connectfd,buffer,256,0);
		printf("recv :%s \n",buffer);

	}  
	close(listenfd);   //�رռ���socket      
	coroutine_close(S);

	return 0;
}  
