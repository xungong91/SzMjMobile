//
//  UIBaseCenterLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIBaseCenterLayer.h"

UIBaseCenterLayer::UIBaseCenterLayer()
{
    
}

UIBaseCenterLayer::~UIBaseCenterLayer()
{
    
}

bool UIBaseCenterLayer::init()
{
    if (!NodeGrid::init())
    {
        return false;
    }
    
    return true;
}