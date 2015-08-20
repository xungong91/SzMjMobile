//
//  UILogin4Layer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UILogin4Layer.h"
#include "UIInfoManage.h"

bool UILogin4Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login4.csb", this);
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             MessageBox("设置密码成功", "tiitle");
         }
     });
    
    Button *Button_close = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_close"));
    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    UIInfoManage::singleton()->setShowPwd(Button_close, TextField_phoneNum);
    
    return true;
}