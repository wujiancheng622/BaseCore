#ifndef NETSDKLISTENER_H
#define NETSDKLISTENER_H
#include "CrossPlatform.h"

class DLL_CLASS NetSdkListener
{

public:
	NetSdkListener() {};
	virtual ~NetSdkListener() {};


	///////////////////////
	//UDP
	
	/** UDP�����ϱ��ص����� 
	 * @param[in] pBuffer����������
	 * @param[in] len:���ݳ���
	 * @param[in] remoteAddr�����ͷ���ip��ַ
	 * @param[in] remotePort�����ͷ��Ķ˿ڵ�ַ
	 * return int :
	 */
	virtual int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort ){ return 0; }

	//////////////////////



	///////////////////////
	//TCP�ͻ���

	/** TCP �ͻ��������ϱ��ص����� 
	 * @param[in] pBuffer������
	 * @param[in] len�����ݳ���
	 * @param[in] remoteAddr�����ͷ���ip��ַ
	 * @param[in] remotePort�����ͷ��Ķ˿ڵ�ַ
	 * return int :
	 */
	//virtual int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort){ return 0; }

	/** TCP�ͻ������ӱ��жϻص����� 
	 * @param[out] error���жϴ�����
	 * @param[out] serverAddr�����ӵķ�����ip��ַ
	 * @param[out] serverListenPort�������������˿�
	 * return void
	 */
	virtual void OnClose(int error,const char* serverAddr, int serverListenPort){}


	/** TCP�ͻ��������Ϸ���˻ص�����  TCP�ͻ������������ʵ�ָýӿ�
	 * @param[in] serverAddr������˵�ip��ַ
	 * @param[in] serverListenPort������˵ļ����˿�
	 * return void
	 */
	virtual void OnConnect( const char * serverAddr, int serverListenPort){}

	///////////////////////





	///////////////////////
	//TCP�����


	/** TCP ����������ϱ��ص����� 
	 * @param[in] pBuffer������
	 * @param[in] len�����ݳ���
	 * @param[in] hSocket�����ĸ������ϱ����������ݣ������ǰ���Ƿ������������ͨ���ò����ж����ĸ��ͻ��˷��͹�����
	 * @param[in] listenPort���ɼ����˿ڵķ�����ϱ�������
	 * return int :
	 */
	virtual int OnData( const char * pBuffer, int len, int hSocket,int listenPort){ return 0; }


	/** TCP��������ӱ��жϻص����� 
	 * @param[in] hSocket:����ָʾ�ĸ����ӱ��ж�,�����ǰ���Ƿ����hSocket����ָʾ�ĸ��ͻ��������ж�
	 * @param[out] error���жϴ�����
	 * @param[out] listenPort: ����Ƿ���ˣ��򷵻��ĸ������˿�
	 * return void
	 */
	virtual void OnClose( int hSocket, int error ,int listenPort){}


	/** TCP����˽��������ӻص�����   TCP��������������ʵ�ָýӿ�
	 * @param[out] newClient:�����ӵľ��
	 * @param[out] remoteAddr��������ip��ַ
	 * @param[out] remotePort�������ӵĶ˿ں�
	 * @param[out] listenPort�����ĸ������˿�������
	 * return bool: �������ʾ���ո����ӣ����ؼٱ�ʾ�ܾ�������Ҳ���ǶϿ�������
	 */
	virtual bool OnAccept( int newClient, const char * remoteAddr, int remotePort,int listenPort){ return true; }

	///////////////////////


};

#endif//NETSDKLISTENER_H

