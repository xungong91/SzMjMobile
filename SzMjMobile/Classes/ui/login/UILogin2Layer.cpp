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
#include "UILogin1Layer.h"
#include "UIInfoManage.h"

bool UILogin2Layer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_login2.csb", this);
    
    Widget *Image_warring = CocosHelper::getWidgetByName(mLayout, "Image_warring");
    
    Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_edit"));
    Size size = layout->getContentSize();
    UserEditBox* mSearchEdit = UserEditBox::create(size, Scale9Sprite::create("Transparent.png"));
    mSearchEdit->setPosition(Point::ZERO);
    mSearchEdit->setAnchorPoint(Point::ZERO);
    mSearchEdit->setFontSize(60);
    mSearchEdit->setFontColor(Color3B::BLACK);
    mSearchEdit->setPlaceHolder("请输入6位验证码");
    mSearchEdit->setPlaceholderFontColor(Color3B(100, 100, 100));
    mSearchEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    mSearchEdit->setDelegate(mSearchEdit);
    layout->addChild(mSearchEdit);
    
    CocosHelper::getWidgetByName(mLayout, "Button_queding")->addTouchEventListener
    ([this, mSearchEdit](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             string s = mSearchEdit->getText();
             if (s.size() != 6)
             {
                 return;
             }
             
             UIMainLayer::gUIMainLayer->removeChild(this);
             UIMainLayer::gUIMainLayer->addChild(UILogin3Layer::create());
         }
     });
    
    Button *Button_huoquyanzhengma = static_cast<Button*>(CocosHelper::getWidgetByName(mLayout, "Button_huoquyanzhengma"));
    
    Button_huoquyanzhengma->addTouchEventListener
    ([this, Button_huoquyanzhengma](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             char text[10];
             int temp = CCRANDOM_0_1() * 1000000;
             sprintf(text, "%06d", temp);
             
             UIWidgetMsgSprite::setMsg("已经发送验证码至" + UIInfoManage::singleton()->mPhoneNum);
             Button_huoquyanzhengma->setTouchEnabled(false);
             
             Text *Text_text = static_cast<Text*>(Button_huoquyanzhengma->getChildByName("Text_text"));
             
             static float gDt = 60;
             gDt = 60;
             this->schedule([Text_text, Button_huoquyanzhengma](float dt)
                            {
                                gDt -= dt;
                                Text_text->setString(__String::createWithFormat("%d秒", (int)gDt)->getCString());
                                if (gDt < 0)
                                {
                                    Button_huoquyanzhengma->setTouchEnabled(true);
                                    Text_text->setString("获取验证码");
                                }
                            }, 1.0f, "upda");
             
         }
     });
    
    mSearchEdit->setDidEndFunc([Image_warring](string s)
                               {
                                   Image_warring->setVisible(s.size() != 6);
                                   if (s.size() == 0)
                                   {
                                       Image_warring->setVisible(false);
                                   }
                               });

    
    return true;
}