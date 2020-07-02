#include "NetUtils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#include <winsock2.h>
#include <httpext.h>   
#include <windef.h>   
#include <Nb30.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"netapi32.lib")
#else
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#endif


namespace BaseCore
{
	namespace Net
	{

#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
		char*  GetIP(void)
		{
			WSADATA wsaData;
			char name[155];
			char *ip;
			PHOSTENT hostinfo;
			if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
			{
				if (gethostname(name, sizeof(name)) == 0)
				{
					if ((hostinfo = gethostbyname(name)) != NULL)
					{
						ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
						return ip;
					}
				}
				WSACleanup();
			}
			return NULL;
		}
		int GetMAC(char * mac)
		{
			NCB ncb;
			typedef struct _ASTAT_
			{
				ADAPTER_STATUS   adapt;
				NAME_BUFFER   NameBuff[30];
			}ASTAT, *PASTAT;

			ASTAT Adapter;
			typedef struct _LANA_ENUM
			{
				UCHAR length;
				UCHAR lana[MAX_LANA];
			}LANA_ENUM;
			LANA_ENUM lana_enum;
			UCHAR uRetCode;
			memset(&ncb, 0, sizeof(ncb));
			memset(&lana_enum, 0, sizeof(lana_enum));

			ncb.ncb_command = NCBENUM;
			ncb.ncb_buffer = (unsigned char *)&lana_enum;
			ncb.ncb_length = sizeof(LANA_ENUM);
			uRetCode = Netbios(&ncb);
			if (uRetCode != NRC_GOODRET)
				return uRetCode;

			for (int lana = 0; lana < lana_enum.length; lana++)
			{
				ncb.ncb_command = NCBRESET;
				ncb.ncb_lana_num = lana_enum.lana[lana];
				uRetCode = Netbios(&ncb);
				if (uRetCode == NRC_GOODRET)
					break;
			}
			if (uRetCode != NRC_GOODRET)
				return uRetCode;

			memset(&ncb, 0, sizeof(ncb));
			ncb.ncb_command = NCBASTAT;
			ncb.ncb_lana_num = lana_enum.lana[0];
			strcpy_s((char*)ncb.ncb_callname, 5, "*");
			ncb.ncb_buffer = (unsigned char *)&Adapter;
			ncb.ncb_length = sizeof(Adapter);
			uRetCode = Netbios(&ncb);
			if (uRetCode != NRC_GOODRET)
				return uRetCode;
			sprintf_s(mac, 18, "%02X-%02X-%02X-%02X-%02X-%02X",
				Adapter.adapt.adapter_address[0],
				Adapter.adapt.adapter_address[1],
				Adapter.adapt.adapter_address[2],
				Adapter.adapt.adapter_address[3],
				Adapter.adapt.adapter_address[4],
				Adapter.adapt.adapter_address[5]
			);
			return 0;
		}



#else
		string getLocalIP(char *eth)
		{
			int inet_sock;
			struct ifreq ifr;
			char ip[32] = { NULL };
			inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
			strcpy(ifr.ifr_name, eth);
			ioctl(inet_sock, SIOCGIFADDR, &ifr);
			strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
			return string(ip);
		}
		std::vector<std::pair<std::string, std::string> > GetAllLocalIP()
		{
			std:vector< std::pair<std::string, std::string> > ipvec;
			int sockfd;
			struct ifconf ifconf;
			struct ifreq *ifreq;
			char buf[512];//缓冲区
						  //初始化ifconf
			ifconf.ifc_len = 512;
			ifconf.ifc_buf = buf;
			if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			{
				perror("socket");
				exit(1);
			}
			ioctl(sockfd, SIOCGIFCONF, &ifconf); //获取所有接口信息
												 //接下来一个一个的获取IP地址
			ifreq = (struct ifreq*)ifconf.ifc_buf;
			printf("ifconf.ifc_len:%d\n", ifconf.ifc_len);
			printf("sizeof (struct ifreq):%d\n", sizeof(struct ifreq));

			for (int i = (ifconf.ifc_len / sizeof(struct ifreq)); i > 0; i--)
			{
				if (ifreq->ifr_flags == AF_INET)
				{ //for ipv4
					printf("name =[%s]\n", ifreq->ifr_name);
					printf("local addr = [%s]\n", inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
					ipvec.push_back(std::pair<std::string, std::string>(ifreq->ifr_name, inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr)));
					ifreq++;
				}
			}
			return ipvec;
		}
#endif


	}
}