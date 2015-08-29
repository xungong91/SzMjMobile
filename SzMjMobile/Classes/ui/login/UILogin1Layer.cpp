//
//  UILogin1Layer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UILogin1Layer.h"
#include "UIMainLayer.h"
#include "UILogin2Layer.h"
#include "XHelper.h"
#include "UIWidgetMsgSprite.h"

bool UILogin1Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login1.csb", this);
    
    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this, TextField_phoneNum](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             string phone = TextField_phoneNum->getString();
             if (!getIsRightPhone(phone))
             {
                 UIWidgetMsgSprite::setMsg("您输入的手机号有误，请重新输入");
                 return;
             }
             
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin2Layer::create());
         }
     });
    
    Widget *Button_close = CocosHelper::getWidgetByName(mLayout, "Button_close");
    Button_close->setVisible(false);
    
    
    Button_close->addTouchEventListener
    ([this, TextField_phoneNum](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             TextField_phoneNum->setString("");
             static_cast<Widget*>(sender)->setVisible(false);
         }
     });
    
    TextField_phoneNum->addEventListener([Button_close, TextField_phoneNum](Ref* sender, TextField::EventType type)
                                              {
                                                  if (type == TextField::EventType::DETACH_WITH_IME)
                                                  {
                                                      Button_close->setVisible(TextField_phoneNum->getString() != "");
                                                  }
                                              });
    
    return true;
}