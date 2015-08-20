//
//  UIBaseLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UIBaseLayer.h"

UIBaseLayer::UIBaseLayer()
{
    
}

UIBaseLayer::~UIBaseLayer()
{
    
}

bool UIBaseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

void UIBaseLayer::addPanelTouch(Layout *panel, function<void ()> func)
{
    panel->setTouchEnabled(true);
    panel->addTouchEventListener
    (
     [func, panel](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::BEGAN)
         {
             panel->setOpacity(150);
         }
         else if (type == Widget::TouchEventType::ENDED)
         {
             panel->setOpacity(255);
             func();
         }
         else if (type == Widget::TouchEventType::CANCELED)
         {
             panel->setOpacity(255);
         }
     }
     );
}
























