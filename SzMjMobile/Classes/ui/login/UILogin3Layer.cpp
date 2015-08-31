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
#include "UIWidgetMsgSprite.h"
#include "XHelper.h"
#include "UILogin1Layer.h"

bool UILogin3Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login3.csb", this);
    
    Button *Button_close = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_close"));
    
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
    
    UIInfoManage::singleton()->setShowPwd(Button_close, mSearchEdit);
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this, mSearchEdit](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (!getIsUserName(mSearchEdit->getText()))
             {
                 return;
             }
             
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










