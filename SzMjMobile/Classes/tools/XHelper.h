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

inline cocos2d::Point getPointHalf(const cocos2d::Size size)
{
    return cocos2d::Point(size.width / 2, size.height / 2);
}

inline cocos2d::Size getSizeWin()
{
    return cocos2d::Director::getInstance()->getWinSize();
}

#endif /* defined(__SzMjMobile__XHelper__) */
