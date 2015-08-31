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
#include "UIInfoManage.h"

bool UILogin1Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login1.csb", this);
    
//    TextField *TextField_phoneNum = static_cast<TextField*>(CocosHelper::getWidgetByName(mLayout, "TextField_phoneNum"));
    
    Widget *Button_close = CocosHelper::getWidgetByName(mLayout, "Button_close");
    
    Widget *Image_warring = CocosHelper::getWidgetByName(mLayout, "Image_warring");
    
    Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_edit"));
    Size size = layout->getContentSize();
    UserEditBox* mSearchEdit = UserEditBox::create(size, Scale9Sprite::create("Transparent.png"));
    mSearchEdit->setPosition(Point::ZERO);
    mSearchEdit->setAnchorPoint(Point::ZERO);
    mSearchEdit->setFontSize(60);
    mSearchEdit->setFontColor(Color3B::BLACK);
    mSearchEdit->setPlaceHolder("请输入手机号");
    mSearchEdit->setPlaceholderFontColor(Color3B(100, 100, 100));
    mSearchEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    mSearchEdit->setDelegate(mSearchEdit);
    layout->addChild(mSearchEdit);
    
    mSearchEdit->setDidEndFunc([Button_close, Image_warring](string s)
                               {
                                   Button_close->setVisible(s != "");
                                   Image_warring->setVisible(!getIsRightPhone(s));
                                   if (s == "")
                                   {
                                       Image_warring->setVisible(false);
                                   }
                               });
    
    CocosHelper::getWidgetByName(mLayout, "Button_next")->addTouchEventListener
    ([this, mSearchEdit, Image_warring](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             string phone = mSearchEdit->getText();
             if (!getIsRightPhone(phone))
             {
                 return;
             }
             
             UIInfoManage::singleton()->mPhoneNum = phone;
             
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin2Layer::create());
         }
     });
    
    Button_close->setVisible(false);
    
    
    Button_close->addTouchEventListener
    ([this, mSearchEdit, Image_warring](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             mSearchEdit->setText("");
             static_cast<Widget*>(sender)->setVisible(false);
             Image_warring->setVisible(false);
         }
     });
    
    return true;
}

//-----------
//UserEditBox
//-----------

UserEditBox* UserEditBox::create(const Size& size, Scale9Sprite* normalSprite)
{
    UserEditBox* pRet = new (std::nothrow) UserEditBox();
    
    if (pRet != nullptr && pRet->initWithSizeAndBackgroundSprite(size, normalSprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

void UserEditBox::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    
}

void UserEditBox::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    if (mDidEndFunc)
    {
        mDidEndFunc(editBox->getText());
    }
}

void UserEditBox::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    
}

void UserEditBox::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
    
}



















