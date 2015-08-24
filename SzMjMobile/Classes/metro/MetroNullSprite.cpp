//
//  MetroNullSprite.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "MetroNullSprite.h"

bool MetroNullSprite::init()
{
    if (!BaseMetroSprite::init())
    {
        return false;
    }
    
    this->setVisible(false);
    
    return true;
}