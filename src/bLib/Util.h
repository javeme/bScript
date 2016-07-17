#pragma once
#include "bluemeiLib.h"
#include "File.h"
#include "Object.h"

namespace bluemei{

using std::string;
#define PropertiesMap map<string,string>

class BLUEMEILIB_API Util : public Object
{
public:
	Util(void);
	~Util(void);
private:
	static PropertiesMap propertiesMap;
	static string filePath;//"config/upload.cfg"	
	static string content;
	static bool bInited;
	static bool bChanged;
private:
	static void readPropertyFromFile(const string& path);
public:	
	static void init();
	static void setPropertyFilePath(const string& path);
	static bool getProperty(const string& key,string& value);//获取配置属性		
	static bool setProperty(const string& key,const string& value);//设置配置属性
	static bool removeProperty(const string& key);
	static void saveProperty();
public:
	static bool simpleEncode(string& plaintext,const string& code);//明文->密码
	static bool simpleDecode(string& cipher,const string& code);//密码->明文
public:
	static bool getSelfPath(string& path);
	static bool open(const string& name,const string& arg="");
public:
	static void replaceString(string & strToReplace, const string & strSrc, const string &strDst);
	static void trim(string &str);
	static short getChar(int& pos,const string& str);
	static int match(const string& value,const string& regex);//正则匹配

	static int str2Int(const string& str);
	static string int2Str(int i);
public:
	static int random();
};


}//end of namespace bluemei