#include <iostream>  
#include <stdio.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/socketvar.h>  
#include <fcntl.h>  
#include <netinet/in.h>   
#include <arpa/inet.h>  
  
const int MAX_CLIENT = 40;  
using namespace std;  
int main()  
{  
    int m_nSocket;  
    sockaddr_in m_stSockaddr;  
    string m_strIP = "192.168.3.119";  
   // string m_strIP = "172.17.0.8";  
    printf("ip :%s \n",m_strIP.c_str());
    int m_nPort = 11210;  
    m_nSocket = socket(AF_INET, SOCK_STREAM, 0);  
    if (m_nSocket < 0)  
    {  
        cout<<"Create failed!"<<endl;  
        return 1;  
    }  
  
    cout<<"socket succed!"<<endl;  
  
  fcntl(m_nSocket, F_SETFL, O_NONBLOCK);  //设置socket非阻塞  
    int nTmp = 1;  
    int nRet =setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, &nTmp, sizeof(int));  
    if (nRet < 0)  
    {  
        return 1;  
    }  
  
    cout<<"fcntl succed!"<<endl;  
  
    // 设置SOCKET接收地址和端口  
    memset (&m_stSockaddr, 0, sizeof(m_stSockaddr));  
    m_stSockaddr.sin_family = AF_INET;  
    m_stSockaddr.sin_addr.s_addr = inet_addr(m_strIP.c_str());  
    m_stSockaddr.sin_port = htons (m_nPort);  
  
    nRet = bind (m_nSocket, (struct sockaddr*)&m_stSockaddr,sizeof(m_stSockaddr));  
    if (nRet < 0)  
    {  
		cout<<"failed"<<endl;
        return 1;  
    }  
  
    cout<<"bind succed!"<<endl;  
  
    nRet = listen (m_nSocket, MAX_CLIENT);  
    if (nRet < 0)  
    {  
        return 1;  
    }  
    cout<<"listen succed!"<<endl;  
	while(true)
	{
		char c;
		getchar();
	}
	
    return 0;  
}  
