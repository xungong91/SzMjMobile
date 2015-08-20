//
//  UIInfoManage.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/18.
//
//

#include "UIInfoManage.h"

UIInfoManage *UIInfoManage::mUIInfoManage = nullptr;

UIInfoManage::CGarbo UIInfoManage::mGarbo;

UIInfoManage::UIInfoManage()
: mIsShowPwd(false)
{
    
}

UIInfoManage::~UIInfoManage()
{
    
}

UIInfoManage *UIInfoManage::singleton()
{
    if (!mUIInfoManage)
    {
        mUIInfoManage = new UIInfoManage();
    }
    return mUIInfoManage;
}

void UIInfoManage::setShowPwd(Button *button, TextField *textFied)
{
    auto setShowPwdFunc = [this, button, textFied]()
    {
        string text = textFied->getString();
        textFied->setString("");
        if (mIsShowPwd)
        {
            button->loadTextureNormal("ui/button_look0.png");
            button->loadTexturePressed("ui/button_look0.png");
            textFied->setPasswordEnabled(false);
        }
        else
        {
            button->loadTextureNormal("ui/button_look1.png");
            button->loadTexturePressed("ui/button_look1.png");
            textFied->setPasswordEnabled(true);
            textFied->setPasswordStyleText("*");
        }
        textFied->setString(text);
    };
    setShowPwdFunc();
    
    button->addTouchEventListener
    ([this, setShowPwdFunc](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             mIsShowPwd = !mIsShowPwd;
             setShowPwdFunc();
         }
     });
}


























