#ifndef TCPCLIENTMODEL_H_
#define TCPCLIENTMODEL_H_


#include "CrossPlatform.h"
#include "NetSdkListener.h"





	
namespace BaseCore
{
	
namespace Net
{

/*  �ͻ��˻�����
	ʹ�÷�����
	1��ʹ�����趨��һ�������������NetSdkListener����������ָ�봫�ݸ�TcpServer�Ĺ��캯��
	2������Start������������
	3: ����Stop����ֹͣ����

*/



class TcpClient_Helper; 
class Client;
class DLL_CLASS TcpClient
{

	friend class  Client;
 public:
	 TcpClient(NetSdkListener *pListener);
	 virtual ~TcpClient(void);

	 /*
	 	breif : �������ӷ���
	 	param : ip ���������ڵ�ip��ַ
	 	param : nPort ������ʹ�õĶ˿�
	 	param : bConnectAsync �Ƿ�ʹ���첽����
		param : bAutoReconnect �����˶Ͽ����Ӻ��Ƿ��Զ���������
		param : hHandle������ʶ��ǰtcp client�ľ��ֵ��Ĭ��Ϊ0
	 	return : void
	 */
	 int  Start(const char* ip,int nPort,bool bConnectAsync=false,bool bAutoReconnect=true,int hHandle=0);

	 /** ��ȡ��ǰtcp client�ľ��
	  return : int :��ǰtcp client�ľ��
	  */
	 int GetHandle();

	 /*
	 	breif :ֹͣ����
	 	return :void
	 */
	 void Stop();


	 /*
	 	breif : �������ݺ���
	 	param : pBuffer ��������
	 	param : len ���ݳ���
	 	param : bSendAsync �Ƿ��첽����
	 	return :����첽����ɹ��򷵻�0�����򷵻�ʧ�ܣ����ͬ������ɹ��򷵻�ʵ�ʷ��͵��ֽ��������򷵻�-1
	 */
	 int  SendData(const char *pBuffer,int len,bool bSendAsync=false);


	 /*
		breif :�����ڽ��ܺͷ���TCP��ʱ�����ģʽ�����ݰ�ͷ�Ͱ�β�����һ�����������ݰ�������������򲻽��������
		ע���������������Start����֮ǰ���÷��������Ч
		param :pHeader ��ͷ����
		param :headerLen ��ͷ����
		param :pTrailer ��β����
		param :trailerLen ��β����
		return :���óɹ�����0�����򷵻�-1
	*/
	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);



	
 private:
	 TcpClient_Helper *m_pDataHelper;
	 NetSdkListener *m_pNetSdkListener;
 };
 
 
}

}



#endif  //TCPCLIENTMODEL_H_





