#ifndef _JSON_HELPER_H_
#define _JSON_HELPER_H_

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include <string>
#include <list>
#include <map>

using namespace std;
using namespace rapidjson;

class JsonHelper
{
public:
	static JsonHelper *singleton();
    
    //获取微信token
    bool getWeixinAccessToken(const string &data, map<string, string> &outMap);
    //获取微信唯一标示
    bool getWeixinUnionid(const string &data, map<string, string> &outMap);
    
private:
    bool getDocument(const string &data, Document &doc);
    int fristLineDocument(const string &data, Document &doc);
    
    string getValueInt64(const char* name, rapidjson::Value &doc);
    string getValueInt64(const char* name, Document &doc);
	string getValueInt(const char* name, Document &doc);
	string getValueInt(const char* name, rapidjson::Value &val);
	string getValueString(const char* name, Document &doc);
	string getValueString(const char* name, rapidjson::Value &doc);
	string getValueBool(const char* name, rapidjson::Value &doc);
    string getValueDouble(const char* name, rapidjson::Value &doc);
	static JsonHelper *mJsonHelper;
	JsonHelper();
	~JsonHelper();
	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (mJsonHelper)  
				delete mJsonHelper;  
		}  
	};  
	static CGarbo Garbo;
};
#endif