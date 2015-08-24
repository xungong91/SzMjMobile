//
//  CoinsBy.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/4/28.
//
//

#include "CoinsTo.h"

CoinsTo* CoinsTo::create(float duration, const string &num, Text *text)
{
    CoinsTo *ret = new (std::nothrow) CoinsTo();
    
    if (ret)
    {
        if (ret->initWithDuration(duration, num, text))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

bool CoinsTo::initWithDuration(float duration, const string &num, Text *text)
{
    bool ret = false;
    
    if (ActionInterval::initWithDuration(duration))
    {
        stringstream ss;
        string s;
        ss<<num;
        ss>>mNum;
        
        ss.str("");
        ss.clear();
        ss<<text->getString();
        ss>>mStartNum;
        
        mText = text;
        
        ret = true;
    }
    
    return ret;
}

void CoinsTo::update(float time)
{
    if (_target)
    {
        CCLOG("%.2f", time);
        
        stringstream ss;
        string s;
        ss<<(mStartNum + (mNum - mStartNum) * time);
        ss>>s;
        mText->setString(s);
    }
}

