//
//  CrashHelper.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "CrashHelper.h"
#include "cocos2d.h"

USING_NS_CC;

CrashHelper *CrashHelper::mCrashHelper = nullptr;

CrashHelper::CGarbo CrashHelper::mGarbo;

CrashHelper *CrashHelper::singleton()
{
    if (!mCrashHelper)
    {
        mCrashHelper = new CrashHelper();
    }
    return mCrashHelper;
}

CrashHelper::CrashHelper()
: mHasError(false)
, mErrorMsg("")
{
    
}

CrashHelper::~CrashHelper()
{
    mCrashHelper = nullptr;
}

void CrashHelper::handlError()
{
    string filename = FileUtils::getInstance()->getWritablePath() + "error.log";
    if (FileUtils::getInstance()->isFileExist(filename))
    {
        ssize_t size;
        char* pBuffer = (char*)FileUtils::getInstance()->getFileData(filename.c_str(), "rt", &size);
        mErrorMsg.assign(pBuffer, size);
//        CCLOG(mErrorMsg.c_str());
        
        mHasError = true;
        
        //删除文件
        FileUtils::getInstance()->removeFile(filename);
    }
    else
    {
        mHasError = false;
    }
    
}









