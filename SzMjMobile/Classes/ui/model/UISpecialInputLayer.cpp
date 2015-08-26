//  UISpecialInputLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/26

#include "UISpecialInputLayer.h"

UISpecialInputLayer::UISpecialInputLayer()
{
}

UISpecialInputLayer::~UISpecialInputLayer()
{
}

bool UISpecialInputLayer::init()
{
    if(!Layer::init())
        return false;

    InitUI();
    
    return true;
}

//初始化UI
void UISpecialInputLayer::InitUI()
{
    //输入框
    mInput = (UIInput*)ui::EditBox::create(Size(537, 130), ui::Scale9Sprite::create("addModel/InputBg_0.png"));
    mInput->setFont("微软雅黑", 38);
    mInput->setFontColor(Color3B(0, 0, 0));
    mInput->setDelegate(this);
    addChild(mInput);
    
    //label，添加此对象的原因纯粹是因为EditBox中的文本不能居中
    mNullLabel = ui::Text::create("昵称", "微软雅黑", 38);
    mNullLabel->setColor(Color3B(0, 0, 0));
    addChild(mNullLabel);
    
    mTitleLabel = ui::Text::create("昵称", "微软雅黑", 35);
    mTitleLabel->setColor(Color3B(240, 162, 26));
    mTitleLabel->setPositionY(40);
    mTitleLabel->setVisible(false);
    addChild(mTitleLabel);
    
    mContentLabel = ui::Text::create("我是你大爷", "微软雅黑", 45);
    mContentLabel->setColor(Color3B(240, 162, 26));
    mContentLabel->setPositionY(-20);
    mContentLabel->setVisible(false);
    addChild(mContentLabel);
}

void UISpecialInputLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox)
{
    if(editBox == mInput)
    {
        mInput->SetScale9Sprite(Size(537, 130), "addModel/InputBg_1.png");
        mInput->setPlaceHolder("用户名");//设置输入框内的默认文本，且直到输入新内容前一直显示
        
        mNullLabel->setVisible(false);
    }
}

void UISpecialInputLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    if(editBox == mInput)
    {
        if(strcmp(mInput->getText(), "")  != 0)
        {
            mInput->SetScale9Sprite(Size(537, 130), "addModel/InputBg_0.png");
            mInput->setPlaceHolder("");//设置输入框内的默认文本，且直到输入新内容前一直显示
        }
    }
}

void UISpecialInputLayer::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
}

void UISpecialInputLayer::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
}









