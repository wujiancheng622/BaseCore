#ifndef UDPSERVERMODEL_H_
#define UDPSERVERMODEL_H_

#include "CrossPlatform.h"
#include "NetSdkListener.h"

namespace BaseCore
{


namespace Net
{

class UdpServer_Helper;

class DLL_CLASS UdpServer
{
public:
	UdpServer(NetSdkListener *pListener);
	~UdpServer();


	/*
		breif :��������
		param :ip ����˵�ip��ַ
		param  :nPort ����˵Ķ˿ڵ�ַ
		return :int �����ɹ�����0��ʧ�ܷ���-1
	*/
	int Start(const char *ip,int nPort);



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


	/*
		breif :ֹͣ����
		return :void
	*/
	void Stop();



private:
	UdpServer_Helper *m_pDataHelper;
	NetSdkListener *m_pNetSdkListener;
	friend class  AsioUdpServer;
};



}
}



#endif  //UDPSERVERMODEL_H_


