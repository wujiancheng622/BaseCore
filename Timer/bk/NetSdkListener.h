#ifndef NETSDKLISTENER_H
#define NETSDKLISTENER_H


class NetSdkListener
{
	public:
		NetSdkListener() {};
		virtual ~NetSdkListener() {};

		virtual int OData( const char * pBuffer, int len, const char* remoteAddr, int remotePort ){}
		virtual int OnData( const char * pBuffer, int len, int hSocket){}
		virtual void OnClose( int hSocket, int error ){}
		virtual void OnConnect( const char * remoteAddr, int remotePort){}
		virtual void OnAccept( int newClient, const char * remoteAddr, int remotePort){}
};

#endif//NETSDKLISTENER_H

