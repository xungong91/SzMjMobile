//
//  UILogin2Layer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UILogin2Layer.h"
#include "UIMainLayer.h"
#include "UILogin3Layer.h"
#include "UIWidgetMsgSprite.h"

bool UILogin2Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login2.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_queding")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (static_cast<TextField*>(CocosHelper::getNodeByName(mLayout, "TextField_phoneNum"))->getString().size() != 6)
             {
                 UIWidgetMsgSprite::setMsg("验证码有误，请重新输入");
                 return;
             }
             
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin3Layer::create());
         }
     });
    
    CocosHelper::getWidgetByName(mLayout, "Button_huoquyanzhengma")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             char text[10];
             int temp = CCRANDOM_0_1() * 1000000;
             sprintf(text, "%06d", temp);
             
             static_cast<TextField*>(CocosHelper::getNodeByName(mLayout, "TextField_phoneNum"))->setString(text);
         }
     });
    
    return true;
}