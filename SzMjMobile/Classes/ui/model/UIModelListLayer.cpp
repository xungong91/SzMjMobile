//
//  UIModelListLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/21.
//
//

#include "UIModelListLayer.h"
#include "UIModelInfoLayer.h"
#include "UIMainLayer.h"

bool UIModelListLayer::init()
{
    if (!UIBaseTopLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_model_list.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Image_1_2")->addTouchEventListener
    ([](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->pushLayer(UIModelInfoLayer::create());
         }
     });
    
    return true;
}