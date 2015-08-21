//
//  UIPublishMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIPublishMainLayer.h"

bool UIPublishMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_publish.csb", this);
    
    return true;
}