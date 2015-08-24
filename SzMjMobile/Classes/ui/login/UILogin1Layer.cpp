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

bool UILogin1Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login1.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin2Layer::create());
         }
     });
    
    Widget *Button_close = CocosHelper::getWidgetByName(mLayout, "Button_close");
    Button_close->setVisible(false);
    
    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    
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