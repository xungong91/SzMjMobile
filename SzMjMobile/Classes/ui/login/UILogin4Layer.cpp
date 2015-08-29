//
//  UILogin4Layer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UILogin4Layer.h"
#include "UIInfoManage.h"
#include "UIWidgetMsgSprite.h"
#include "XHelper.h"
#include "UILogin3Layer.h"
#include "UIMainLayer.h"

bool UILogin4Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login4.csb", this);
    
    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this, TextField_phoneNum](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (!getIsUserName(TextField_phoneNum->getString()))
             {
                 UIWidgetMsgSprite::setMsg("您输入的密码有误，请重新输入");
                 return;
             }
             
             MessageBox("设置密码成功", "tiitle");
         }
     });
    
    CocosHelper::getWidgetByName(mLayout, "BtnReturn")->addTouchEventListener
    ([this, TextField_phoneNum](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin3Layer::create());
         }
     });
    
    Button *Button_close = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_close"));
    UIInfoManage::singleton()->setShowPwd(Button_close, TextField_phoneNum);
    
    return true;
}