#ifndef UDPCLIENTMODEL_H_
#define UDPCLIENTMODEL_H_ 

#include <string>
#include "CrossPlatform.h"
#include "NetSdkListener.h"


	
namespace BaseCore
{
	
namespace Net
{



class UdpClient_Helper; 
class AsioUdpClient;
class DLL_CLASS UdpClient
{
 public:
	 UdpClient(NetSdkListener *pListener);
	 virtual ~UdpClient(void);


	 /** �������� 
	  * @param[in]  desc:ÿ��udp client�ڲ�������һ���߳� desc������ʾ����̵߳����ƣ���Ҫ���ڵ���ʱʹ�ã����Բ�����
	  * return void
	  */
	 void Start(std::string desc="");

	 /** ֹͣ���� 
	  * return void
	  */
	 void Stop();

	/*
		breif :�������ݺ���
		param :pBuffer ��������
		param :len �����ֽڳ���
		param :remoteAddr ���շ���IP
		param :remotePort ���շ��Ķ˿ں�
		param :bAsync �Ƿ�ʹ���첽����ģʽ
		return :���ͳɹ��򷵻ط��͵��ֽ�����ʧ�ܷ���-1
	*/
	int  SendData(const char *pBuffer,int len, const char* remoteAddr, int remotePort,bool bAsync=false);

 private:
	 UdpClient_Helper *m_pDataHelper;
	 NetSdkListener *m_pNetSdkListener;
	 friend class  AsioUdpClient;
 };
 
 
}

}




#endif  //UDPCLIENTMODEL_H_