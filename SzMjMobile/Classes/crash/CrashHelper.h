//
//  CrashHelper.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#ifndef __SzMjMobile__CrashHelper__
#define __SzMjMobile__CrashHelper__

#include <stdio.h>
#include <string>

using namespace std;

class CrashHelper
{
public:
    static CrashHelper *singleton();
    
    void InitCrashReport();

    //测试 产生bug
    void throwError();
    
    //处理bug
    void handlError();
    
private:
    string mErrorMsg;
    bool mHasError;
    
    static CrashHelper *mCrashHelper;
    CrashHelper();
    ~CrashHelper();
    class CGarbo
    {
    public:
        CGarbo(){}
        ~CGarbo()
        {
            if (CrashHelper::mCrashHelper)
            {
                delete CrashHelper::mCrashHelper;
            }
        }
    };
    static CGarbo mGarbo;
};

#endif /* defined(__SzMjMobile__CrashHelper__) */
