//
//  UIMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UIMainLayer.h"
#include "CocosHelper.h"
#include "UILogin1Layer.h"

UIMainLayer *UIMainLayer::gUIMainLayer = nullptr;

UIMainLayer::UIMainLayer()
{
    gUIMainLayer = this;
}

UIMainLayer::~UIMainLayer()
{
    gUIMainLayer = nullptr;
}

bool UIMainLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    this->addChild(UILogin1Layer::create());
    
    return true;
}