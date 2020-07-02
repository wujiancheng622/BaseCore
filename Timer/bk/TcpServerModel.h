#include "NetSdkListener.h"

namespace BaseCore
{
	
namespace Net
{




class TcpServer_Helper; 
class Server;


/*  ����˻�����
	ʹ�÷�����
	1��ʹ�����趨��һ�������������NetSdkListener����������ָ�봫�ݸ�TcpServer�Ĺ��캯��
	2������Start������������
	3: ����Stop����ֹͣ����

*/
class TcpServer 
{
	friend class  Server;
public:
	TcpServer(NetSdkListener *pListener);
	virtual ~TcpServer(void);



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
		param :hHandle ���͸��ĸ��ͻ��ˣ����hHandleΪ0���ʾ���͸������һ���ͻ���
		param :bAsync true��ʾʹ���첽����,false��ʾͬ������
		return :ͬ�����ͷ��ͳɹ��򷵻ط��͵��ֽ������첽���ͳɹ�����0�� ͬ�����첽����ʧ��ʱ������-1
	*/
	int  SendData(const char *pBuffer,int len,int hHandle=0,bool bAsync=false);


	/*
		breif :ֹͣ����
		return :void
	*/
	void Stop();

	/*
		breif :�����ڽ��ܺͷ���TCP��ʱ�����ģʽ�����ݰ�ͷ�Ͱ�β�����һ���������ݰ�������������򲻽��������
		ע���������������Start����֮ǰ���÷��������Ч
		param :pHeader ��ͷ����
		param :headerLen ��ͷ����
		param :pTrailer ��β����
		param :trailerLen ��β����
		return :���óɹ�����0�����򷵻�-1
	*/
	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);



private:
	TcpServer_Helper *m_pDataHelper;
	NetSdkListener *m_pNetSdkListener;
};


}

}
 
