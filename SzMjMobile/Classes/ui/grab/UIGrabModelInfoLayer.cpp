//
//  UIGrabModelInfoLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIGrabModelInfoLayer.h"

bool UIGrabModelInfoLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_grabModelInfo.csb", this);
    return true;
}