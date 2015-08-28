//
//  UIIncomePickRegLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomePickRegLayer.h"

bool UIIncomePickRegLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomePickReg.csb", this);
    
    return true;
}