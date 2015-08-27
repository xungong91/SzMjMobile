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
    
    return true;
}

//初始化UI
void UISpecialInputLayer::InitUI(string titleStr, string placeHolderStr, ui::EditBox::InputMode inputMode, InputType inputType)
{
    mTitleStr = titleStr;
    mPlaceHolderStr = placeHolderStr;
    mInputType = inputType;
    
    //输入框
    mInput = (UIInput*)ui::EditBox::create(Size(537, 130), ui::Scale9Sprite::create("addModel/InputBg_0.png"));
    mInput->setInputMode(inputMode);
    mInput->setFont("微软雅黑", 38);
    mInput->setFontColor(Color3B(0, 0, 0));
    mInput->setDelegate(this);
    addChild(mInput);
    
    //label，添加此对象的原因纯粹是因为EditBox中的文本不能居中
    mNullLabel = ui::Text::create(titleStr, "微软雅黑", 38);
    mNullLabel->setColor(Color3B(0, 0, 0));
    addChild(mNullLabel);
    
    mTitleLabel = ui::Text::create(titleStr, "微软雅黑", 35);
    mTitleLabel->setColor(Color3B(240, 162, 26));
    mTitleLabel->setPositionY(40);
    mTitleLabel->setVisible(false);
    addChild(mTitleLabel);
    
    mContentLabel = ui::Text::create("XXXXX", "微软雅黑", 45);
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
        mInput->setPlaceHolder(mPlaceHolderStr.c_str());//设置输入框内的默认文本，且直到输入新内容前一直显示
        
        mNullLabel->setVisible(false);
    }
}

void UISpecialInputLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    if(editBox == mInput)
    {
        if(strcmp(mInput->getText(), "")  != 0)
        {
            mStr = mInput->getText();
            
            mTitleLabel->setVisible(true);
            mContentLabel->setVisible(true);
            SetString(mStr);
        }
        else
        {
            mStr = mInput->getText();
            
            mNullLabel->setVisible(true);
        }
        
        mInput->SetScale9Sprite(Size(537, 130), "addModel/InputBg_0.png");
        mInput->setPlaceHolder("");//设置输入框内的默认文本，且直到输入新内容前一直显示
        mInput->setText("");
    }
}

void UISpecialInputLayer::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
}

void UISpecialInputLayer::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
}

void UISpecialInputLayer::SetString(string str)
{
    string tempStr = str;
    
    if(mInputType == InputType::ANY)
    {
        mContentLabel->setString(str);
    }
    else if(mInputType == InputType::BIRTHDAY)
    {
        //只适用8位的生日19880219
        string year = tempStr.substr(0, 4);
        string month = tempStr.substr(4, 2);
        string day = tempStr.substr(6, 2);
        year += "年";
        month = (month.substr(0, 1) == "0") ? month.substr(1, 1) : month;
        month += "月";
        day = (day.substr(0, 1) == "0") ? day.substr(1, 1) : day;
        day += "日";
        tempStr = year + month + day;
        mContentLabel->setString(tempStr);
    }
    else if(mInputType == InputType::HEIGHT)
    {
        tempStr += "cm";
        mContentLabel->setString(tempStr);
    }
    else if(mInputType == InputType::BHW)
    {
        tempStr.insert(2, "B-");
        tempStr.insert(6, "-");
        mContentLabel->setString(tempStr);
    }
    else if(mInputType == InputType::TEL)
    {
        tempStr.insert(3, "-");
        tempStr.insert(8, "-");
        mContentLabel->setString(tempStr);
    }
}








