//
//  UIManageEditlLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageEditlLayer.h"

bool UIManageEditlLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    mModelTouchFunc = nullptr;
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_manageEdit.csb", this);
    
    
    CocosHelper::getWidgetByName(mLayout, "Button_model")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (mModelTouchFunc)
             {
                 mModelTouchFunc();
             }
         }
     });
    
    return true;
}