#ifndef _ClientSocket_h_ 
#define _ClientSocket_h_ 

#include "bluemeiLib.h"
#include <winsock2.h>
#include "Object.h"
#include "BString.h"

namespace bluemei{

#define BUFFER_SIZE 1024

typedef SOCKET socket_t;

class BLUEMEILIB_API ClientSocket : public Object
{
public:
	ClientSocket();
	ClientSocket(socket_t hSocket);
	~ClientSocket();
protected:
	socket_t m_hSocket;
	sockaddr_in m_peerAddr;
private:
	bool m_bClose;
	int m_nTimeout;
protected:
	void createSocket();
public:
	void attach(socket_t s);
	socket_t detach();
public:
	void connect(cstring ip,unsigned short port);

	void setPeerAddr(sockaddr_in& addr);
	virtual String toString()const;

	String getPeerHost()const;//������string&�Ƿ�����?
	int getPeerPort()const;

	void setTimeout(int ms)/*��ʱ,���� */;
	void setNoDelay(bool b);

	unsigned long availableBytes();
	void skip(unsigned long len);

	int readBytes(char buffer[],int maxLength,int flags=0);
	int readEnoughBytes(char buffer[],int length);
	int readInt();
	int readShort();
	unsigned char readByte();
	//string& readLineByUtf();
	String readLineByGbk();
	//string readUtfString(int wantToReadSize);
	String readUtfString();

	//int writeBytes(byte*& buffer,int length);
	int writeBytes(const char buffer[],int length,int flags=0);
	int writeInt(int value);
	int writeShort(short value);
	int writeByte(unsigned char value);
	int writeString(const String& str);
	int writeUtfString(const String& str);
	int writeUnicodeString(const String& str);

	void close();
};


}//end of namespace bluemei
#endif