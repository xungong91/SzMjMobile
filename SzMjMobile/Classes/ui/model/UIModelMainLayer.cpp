//
//  UIModelMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIModelMainLayer.h"
#include "UIMainLayer.h"
#include "UIModelListLayer.h"

bool UIModelMainLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Image_1")->addTouchEventListener
    ([](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIModelListLayer::create());
         }
     });
    
    return true;
}