//
//  UILogin3Layer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UILogin3Layer.h"
#include "UIMainLayer.h"
#include "UILogin4Layer.h"
#include "UIInfoManage.h"
#include <functional>

bool UILogin3Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login3.csb", this);
    
    Button *Button_close = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_close"));
    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    UIInfoManage::singleton()->setShowPwd(Button_close, TextField_phoneNum);
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->intoMain();
         }
     });
    
    CocosHelper::getWidgetByName(mLayout, "Text_zhaohui")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin4Layer::create());
         }
     });
    
    
    return true;
}