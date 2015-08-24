//
//  ShareHelper.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/12.
//
//

#include "ShareHelper.h"

ShareHelper *ShareHelper::gShareHelper = nullptr;

ShareHelper::CGarbo ShareHelper::mGarbo;

ShareHelper *ShareHelper::singleton()
{
    if (!ShareHelper::gShareHelper)
    {
        ShareHelper::gShareHelper = new ShareHelper();
    }
    return ShareHelper::gShareHelper;
}

ShareHelper::ShareHelper()
: mAppId("wx323c2e438860301b")
, mAppSecret("5c930598301a376ef263cbdce42929e3")
, mOpenId("")
, mOtherLoginFunc(nullptr)
{
    
}

ShareHelper::~ShareHelper()
{
    ShareHelper::gShareHelper = nullptr;
}

void ShareHelper::sendGetRequset(const string &url, function<void (bool b, const string &data)> func)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("tag");
    request->setResponseCallback
    (
     [func](HttpClient* client, HttpResponse* response)
     {
         bool result = true;
         if (!response)
         {
             result = false;
         }
         auto statusCode = response->getResponseCode();
         if (!response->isSucceed())
         {
             CCLOG("response code: %ld", statusCode);
             result = false;
         }
         
         string sBuffer("");
         if (result)
         {
             vector<char> *buffer = response->getResponseData();
             sBuffer.assign(buffer->begin(), buffer->end());
         }
       
         func(result, sBuffer);
     }
     );
    HttpClient::getInstance()->send(request);
    
    request->release();
}