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
: mIsShowPwd(true)
, mPhoneNum("")
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

void UIInfoManage::setShowPwd(Button *button, EditBox *textFied)
{
    auto setShowPwdFunc = [this, button, textFied]()
    {
        string text = textFied->getText();
        textFied->setText("");
        if (mIsShowPwd)
        {
            button->loadTextureNormal("ui/button_look0.png");
            button->loadTexturePressed("ui/button_look0.png");
            textFied->setInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS);
        }
        else
        {
            button->loadTextureNormal("ui/button_look1.png");
            button->loadTexturePressed("ui/button_look1.png");
            textFied->setInputFlag(EditBox::InputFlag::PASSWORD);
        }
        textFied->setText(text.c_str());
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


























