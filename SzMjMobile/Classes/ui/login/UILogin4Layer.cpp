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
#include "UILogin1Layer.h"

bool UILogin4Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login4.csb", this);
    
    Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_edit"));
    Size size = layout->getContentSize();
    UserEditBox* mSearchEdit = UserEditBox::create(size, Scale9Sprite::create("Transparent.png"));
    mSearchEdit->setPosition(Point::ZERO);
    mSearchEdit->setAnchorPoint(Point::ZERO);
    mSearchEdit->setFontSize(60);
    mSearchEdit->setFontColor(Color3B::BLACK);
    mSearchEdit->setPlaceHolder("请输入6-16位密码");
    mSearchEdit->setPlaceholderFontColor(Color3B(100, 100, 100));
    mSearchEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    mSearchEdit->setDelegate(mSearchEdit);
    layout->addChild(mSearchEdit);
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this, mSearchEdit](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (!getIsUserName(mSearchEdit->getText()))
             {
                 return;
             }
             UIWidgetMsgSprite::setMsg("设置登录密码成功");
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->intoMain();
         }
     });
    
    CocosHelper::getWidgetByName(mLayout, "BtnReturn")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin3Layer::create());
         }
     });
    
    Button *Button_close = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_close"));
    UIInfoManage::singleton()->setShowPwd(Button_close, mSearchEdit);
    
    Widget *Image_warring = CocosHelper::getWidgetByName(mLayout, "Image_warring");
    
    mSearchEdit->setDidEndFunc([Image_warring](string s)
                               {
                                   Image_warring->setVisible(!getIsUserName(s));
                                   if (s == "")
                                   {
                                       Image_warring->setVisible(false);
                                   }
                               });
    
    return true;
}