#pragma once
#include "stdafx.h"
#include "Util.h"

namespace bluemei{

using std::string;
using std::wstring;

/*
* 字符及其编码工具类
* @author Javeme
* @create 2012/3/30
*/
class BLUEMEILIB_API CodeUtil : public Util
{
public:	
	static int bytesToInt(char *buf,int sizeOfInt);
	static float bytesToFloat(char *buf,int size);
	static double bytesToDouble(char *buf,int size);

	static void intToBytes(char buf[],int value);
	static void shortToBytes(char buf[],short value);
	static void floatToBytes( char* buf, float f );	
	static void doubleToBytes( char* buf, double f );

	//static char* gbkToUtf8(const char *strGBK);
	//static void utf8ToGbk(string& szstr); 

	static int gbkToUtf8(string& strUtf8,const char *strGBK);
	static int utf8ToGbk(string& strGbk,const char* strUtf8);

	static int utf8ToUnicode(wstring& strUnicode,const char *strUtf8);//返回字节数(unicode字符串长度的2倍)
	static int unicodeToUtf8(string& strUtf8,const wstring& strUnicode);


	static int gbkToUnicode(wstring& strUnicode,const char *strGBK);
	static int gb2312ToUnicode(wstring& result,const char *strGb2312);
	static int unicodeToGbk(string& result,const wstring& uStr);

	static String unicodeToGbk(const wstring& uStr);
	static String utf8ToGbk(const char* strUtf8);
	static int gbkToUtf8(String& strUtf8,const char *strGBK);

	static void base64Decode(const char* str,string& szResault);

public:	
	static String bytesToHexString(const byte buffer[], int len);

	static int str2Int(const String& str);;
	static double str2Float(const String& str);
};

#define invert_int32(x)\
	( (((x) & (0xffU << 24)) >> 24)\
	| (((x) & (0xffU << 16)) >> 8)\
	| (((x) & (0xffU << 8))  << 8)\
	| (((x) & 0xffU)         << 24) )


struct BLUEMEILIB_API CONVWSTR{
	string str;
	CONVWSTR(const wchar_t* cstr)
	{
		CodeUtil::unicodeToGbk(str,(const wchar_t*)cstr);
	}
	operator const char*(){
		return str.c_str();
	}
};
struct BLUEMEILIB_API CONVSTR{
	wstring wstr;
	CONVSTR(const String& str)
	{
		CodeUtil::gb2312ToUnicode(wstr,str);
	}
	operator const wchar_t*(){
		return wstr.c_str();
	}
};

}//end of namespace bluemei