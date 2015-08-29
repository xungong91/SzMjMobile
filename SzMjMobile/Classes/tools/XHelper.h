//
//  XHelper.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#ifndef __SzMjMobile__XHelper__
#define __SzMjMobile__XHelper__

#include "cocos2d.h"
#include <string>

using namespace std;

inline cocos2d::Point getPointHalf(const cocos2d::Size size)
{
    return cocos2d::Point(size.width / 2, size.height / 2);
}

inline cocos2d::Size getSizeWin()
{
    return cocos2d::Director::getInstance()->getWinSize();
}

inline bool getIsRightPhone( const string &phone )
{
    if (phone.size() != 11)
    {
        return false;
    }
    for (auto it : phone)
    {
        if (it<'0' || it >'9')
        {
            return false;
        }
    }
    return true;
}

inline bool getIsUserName( const string &name )
{
    //ºÏ≤È≥§∂»
    if (name.size() > 16 || name.size() < 4 )
    {
        return false;
    }
    //ºÏ≤È◊÷∑˚
    for (const char &it : name)
    {
        bool iNum = it >= 48 && it <= 57;
        bool iLetters = it >= 65 && it <= 90;
        bool iLowercase = it >= 97 && it <= 122;
        bool iSpecial = it == 95;
        if ((!iNum && !iLetters && !iLowercase && !iSpecial))
        {
            return false;
        }
    }
    return true;
}

#endif /* defined(__SzMjMobile__XHelper__) */
