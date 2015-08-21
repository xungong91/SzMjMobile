//
//  UIModelMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIModelMainLayer.h"

bool UIModelMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model.csb", this);
    
    return true;
}