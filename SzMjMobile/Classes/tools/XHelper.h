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

inline string getString(int value)
{
    stringstream ss;
    string s;
    ss<<value;
    ss>>s;
    return s;
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

inline bool getIsRightBankNum( const string &cardNum )
{
    if (cardNum.size() != 16 || cardNum.size() != 18 || cardNum.size() != 19 || cardNum.size() != 15)
    {
        return false;
    }
    
    for (const char &it : cardNum)
    {
        if (it < 48 && it > 57)
        {
            return false;
        }
    }
    
    string snum6 = cardNum.substr(0, 6);
    stringstream ss;
    int num6;
    ss<<snum6;
    ss>>num6;
    if (num6 < 622126 || num6 > 622925)
    {
        return false;
    }
    
    //TODO 16位校验码
    
    return true;
}

inline bool getIsUserName( const string &name )
{
    //ºÏ≤È≥§∂»
    if (name.size() > 16 || name.size() < 6 )
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
