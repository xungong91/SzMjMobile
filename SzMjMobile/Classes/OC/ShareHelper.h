//
//  ShareHelper.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/12.
//
//

#ifndef __SzMjMobile__ShareHelper__
#define __SzMjMobile__ShareHelper__

#include <stdio.h>
#include <string>
#include <functional>

#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace std;
USING_NS_CC;
using namespace network;

enum class ShareType
{
    weixin = 0
};

class ShareHelper
{
public:
    static ShareHelper *singleton();
    void showLog();
    
    //请求第三方登录
    void sendAuth(ShareType type, function<void (bool isSuccess, const string &id)> func);
    
    //第三方登录
    void reqAuth(ShareType type, const string &code, const string &stats);
    
    void onShareLink(ShareType type, const string &fileName);
private:
    string mAppId;
    string mAppSecret;
    string mOpenId;
    
    //第三方登录返回值
    function<void (bool isSuccess, const string &id)> mOtherLoginFunc;
    
    //http get请求部分
    void sendGetRequset(const string &url, function<void (bool b, const string &data)> func);
    
    static ShareHelper *gShareHelper;
    ShareHelper();
    ~ShareHelper();
    class CGarbo
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (ShareHelper::gShareHelper)
            {
                delete ShareHelper::gShareHelper;
            }
        }
    };
    static CGarbo mGarbo;
};

#endif /* defined(__SzMjMobile__ShareHelper__) */
