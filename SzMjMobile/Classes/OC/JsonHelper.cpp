#include "JsonHelper.h"

JsonHelper::JsonHelper()
{

}

JsonHelper::~JsonHelper()
{
	mJsonHelper = NULL;
}

JsonHelper::CGarbo JsonHelper::Garbo;

JsonHelper * JsonHelper::mJsonHelper = NULL;

JsonHelper * JsonHelper::singleton()
{
	if (mJsonHelper == NULL)
	{
		mJsonHelper = new JsonHelper();
	}
	return mJsonHelper;
}

bool JsonHelper::getDocument(const string &data, Document &doc)
{
    doc.Parse<kParseDefaultFlags>(data.c_str());
    
    if(doc.HasParseError())
    {
        return false;
    }
    
    if ((!doc.HasMember("error")) ||
        (doc.HasMember("error") && doc["error"].GetInt() != 0))
    {
        return false;
    }
    return true;
}

int JsonHelper::fristLineDocument(const string &data, Document &doc)
{
    doc.Parse<kParseDefaultFlags>(data.c_str());
    if(doc.HasParseError())
    {
        return -1;
    }
    if ( doc.HasMember("error"))
    {
        return doc["error"].GetInt();
    }
    else
    {
        return -1;
    }
}

bool JsonHelper::getWeixinAccessToken(const string &data, map<string, string> &outMap)
{
    Document doc;
    doc.Parse<kParseDefaultFlags>(data.c_str());
    if (!doc.HasMember("openid"))
    {
        return false;
    }
    
    outMap["access_token"] = getValueString("access_token", doc);
    outMap["openid"] = getValueString("openid", doc);
    
    return true;
}

bool JsonHelper::getWeixinUnionid(const string &data, map<string, string> &outMap)
{
    Document doc;
    doc.Parse<kParseDefaultFlags>(data.c_str());
    if (!doc.HasMember("unionid"))
    {
        return false;
    }
    
    outMap["unionid"] = getValueString("unionid", doc);
    
    return true;
}

string JsonHelper::getValueInt64(const char* name, Document &doc)
{
    rapidjson::Value &value = doc[name];
    int64_t num = value.GetInt64();
    stringstream ss;
    string s;
    ss<<num;
    ss>>s;
    return s;
}

string JsonHelper::getValueInt64(const char* name, rapidjson::Value &doc)
{
    int64_t num = doc[name].GetInt64();
    stringstream ss;
    string s;
    ss<<num;
    ss>>s;
    return s;
}

string JsonHelper::getValueInt( const char* name, Document &doc )
{
    rapidjson::Value &value = doc[name];
    int num = value.GetInt();
    stringstream ss;
    string s;
    ss<<num;
    ss>>s;
    return s;
}

string JsonHelper::getValueInt( const char* name, rapidjson::Value &val )
{
    int num = val[name].GetInt();
    stringstream ss;
    string s;
    ss<<num;
    ss>>s;
    return s;
}

string JsonHelper::getValueString( const char* name, Document &doc )
{
    rapidjson::Value &value = doc[name];
    return value.GetString();
}

string JsonHelper::getValueString( const char* name, rapidjson::Value &doc )
{
    rapidjson::Value &value = doc[name];
    return value.GetString();
}

string JsonHelper::getValueBool( const char* name, rapidjson::Value &doc )
{
    bool b = doc[name].GetBool();
    stringstream ss;
	string s;
	ss<<b;
	ss>>s;
	return s;
}

string JsonHelper::getValueDouble(const char* name, rapidjson::Value &doc)
{
    double b = doc[name].GetDouble();
    char data[10];
    sprintf(data, "%0.2f", b);
    return data;
}
