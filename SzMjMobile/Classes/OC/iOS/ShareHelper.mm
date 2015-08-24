//
//  ShareHelper.m
//  SzMjMobile
//
//  Created by gongxun on 15/8/12.
//
//

#import <Foundation/Foundation.h>
#include "ShareHelper.h"
#import "WXApi.h"
#include "JsonHelper.h"


void ShareHelper::showLog()
{
    NSString *str = @"aaaaaaabbbbbbb";
    NSLog(@"string plus %@",str);
}

void ShareHelper::sendAuth(ShareType type, function<void (bool isSuccess, const string &id)> func)
{
    mOtherLoginFunc = func;
    if (type == ShareType::weixin)
    {
        if (![WXApi isWXAppInstalled])
        {
            MessageBox("没有安装微信", "微信登录失败");
            return;
        }
        
        SendAuthReq* req =[[SendAuthReq alloc ] init];
        req.scope = @"snsapi_userinfo";
        req.state = @"key01" ;
        [WXApi sendReq:req];
    }
}

void ShareHelper::reqAuth(ShareType type, const string &code, const string &stats)
{
    if (type == ShareType::weixin)
    {
        //获取用户的key
        auto getAccessToken = [this](const string &accessToken, const string &openid)
        {
            mOpenId = openid;
            
            ostringstream oss;
            oss<<"https://api.weixin.qq.com/sns/userinfo";
            oss<<"?access_token="<<accessToken;
            oss<<"&openid="<<openid;
            string get = oss.str();
            
            sendGetRequset(get, [this](bool b, const string &dota)
                           {
                               map<string, string> oupMap;
                               bool isSuccess = JsonHelper::singleton()->getWeixinUnionid(dota, oupMap);
                               CCLOG("微信唯一标示");
                               CCLOG(oupMap["unionid"].c_str());
                               
                               mOtherLoginFunc(isSuccess, oupMap["unionid"]);
                           });
        };
        
        //获取token
        ostringstream oss;
        oss<<"https://api.weixin.qq.com/sns/oauth2/access_token";
        oss<<"?appid="<<mAppId;
        oss<<"&secret="<<mAppSecret;
        oss<<"&code="<<code;
        oss<<"&grant_type="<<"authorization_code";
        string get = oss.str();
        
        sendGetRequset(get, [getAccessToken](bool b, const string &dota)
                       {
                           if (b)
                           {
                               map<string, string> oupMap;
                               JsonHelper::singleton()->getWeixinAccessToken(dota, oupMap);
                               getAccessToken(oupMap["access_token"], oupMap["openid"]);
                           }
                       });
        
        
        
        
       
    }
}

void ShareHelper::onShareLink(ShareType type, const string &fileName)
{
    if (type == ShareType::weixin)
    {
        WXMediaMessage *message = [WXMediaMessage message];
        message.title = @"正宗汗味麻将";
        message.description = @"武汉麻将真好玩，每天都要玩几把";
        //        [message setThumbImage:[UIImage imageNamed:[NSString stringWithUTF8String:fileName.c_str()]]];
        [message setThumbImage:[UIImage imageNamed:@"logo_wechat.png"]];
        
        WXWebpageObject *ext = [WXWebpageObject object];
        ext.webpageUrl = @"http://16youxi.com";
        
        message.mediaObject = ext;
        message.mediaTagName = @"WECHAT_TAG_JUMP_IMAGE";
        
        SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
        req.bText = NO;
        req.message = message;
        req.scene = WXSceneSession;
        [WXApi sendReq:req];
    }
}

















