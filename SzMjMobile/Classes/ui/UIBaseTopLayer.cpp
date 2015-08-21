//
//  UIBaseTopLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIBaseTopLayer.h"

UIBaseTopLayer::UIBaseTopLayer()
{
    
}

UIBaseTopLayer::~UIBaseTopLayer()
{
    
}

bool UIBaseTopLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mTopLayout = CSLoader::createNode("res/CCS_topWidget.csb");
    this->addChild(mTopLayout);
    
    return true;
}