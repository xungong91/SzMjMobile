//
//  ShareHelper.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/12.
//
//

#include "ShareHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

#endif

void ShareHelper::showLog()
{
    
}

void ShareHelper::sendAuth(ShareType type, function<void (bool isSuccess, const string &id)> func)
{
    
}

void ShareHelper::reqAuth(ShareType type, const string &code, const string &stats)
{
    
}

void ShareHelper::onShareLink(ShareType type, const string &fileName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JniMethodInfo jmi;
    if(JniHelper::getStaticMethodInfo(jmi , "org/cocos2dx/cpp/MjmJni" , "openURL" , "(Ljava/lang/String;)Z"))
    {
        jstring str_reg = jmi.env->NewStringUTF(fileName.c_str());
        
        jboolean b = jmi.env->CallStaticBooleanMethod(jmi.classID , jmi.methodID , str_reg);
        
    }
    else
    {

    }
#endif
}