//
//  UIIncomePickLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIIncomePickLayer.h"
#include "UIIncomePickRegLayer.h"
#include "UIMainLayer.h"

bool UIIncomePickLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_incomePick.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_reg")->addTouchEventListener
    (
     [](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIIncomePickRegLayer::create());
         }
     }
     );
    
    return true;
}