//
//  UIGraboMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIGrabMainLayer.h"
#include "UIGrabInfoLayer.h"
#include "UIGrabModelInfoLayer.h"
#include "UIMainLayer.h"

bool UIGrabMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_grab.csb", this);
    
    for (int i = 0; i < 3; ++i)
    {
        CocosHelper::getWidgetByName(mLayout, __String::createWithFormat("Image_%d", i)->getCString())->addTouchEventListener(CC_CALLBACK_2(UIGrabMainLayer::onInfoTouch, this));
        
        CocosHelper::getWidgetByName(mLayout, __String::createWithFormat("Panel_model%d", i)->getCString())->addTouchEventListener(CC_CALLBACK_2(UIGrabMainLayer::onModelInfoTouch, this));
    }
    
    return true;
}

void UIGrabMainLayer::onInfoTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UIGrabInfoLayer::create());
    }
}

void UIGrabMainLayer::onModelInfoTouch(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UIGrabModelInfoLayer::create());
    }
}