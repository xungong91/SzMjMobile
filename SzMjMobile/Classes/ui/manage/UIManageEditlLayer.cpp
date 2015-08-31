//
//  UIManageEditlLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/29.
//
//

#include "UIManageEditlLayer.h"
#include "XHelper.h"

vector<string> UIManageEditlLayer::mEditInputs(4);

bool UIManageEditlLayer::init()
{
    if (!UIBaseCenterLayer::init())
    {
        return false;
    }
    mModelTouchFunc = nullptr;
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_manageEdit.csb", this);
    
    
    CocosHelper::getWidgetByName(mLayout, "Button_model")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             if (mModelTouchFunc)
             {
                 mModelTouchFunc();
             }
         }
     });
    
    vector<string> layoutNames = {"Panel_phoneEdit", "Panel_bankEdit", "Panel_bankNameEdit"};
    
    mEditHolders = {"请输入手机号", "请输入银行账号", "请输入银行户名"};
    
    for (int i = 0; i < 3; ++i)
    {
        Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, layoutNames[i]));
        Size size = layout->getContentSize();
        EditBox *tempEdit = EditBox::create(size, Scale9Sprite::create("Transparent.png"));
        tempEdit->setPosition(Point::ZERO);
        tempEdit->setAnchorPoint(Point::ZERO);
        tempEdit->setFontSize(60);
        tempEdit->setFontColor(Color3B::BLACK);
        tempEdit->setPlaceHolder(mEditHolders[i].c_str());
        tempEdit->setPlaceholderFontColor(Color3B(100, 100, 100));
        tempEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        tempEdit->setDelegate(this);
        tempEdit->setTag(i);
        if (i == 0)
        {
            tempEdit->setInputMode(EditBox::InputMode::NUMERIC);
        }
        
        layout->addChild(tempEdit);
        
//        mEdits.push_back(tempEdit);
//        mLayouts.push_back(layout);
    }
    
    CocosHelper::getWidgetByName(mLayout, "Button_save")->addTouchEventListener
    ([this](Ref *sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             ((Widget*)sender)->setVisible(false);
         }
     });
    
    
//    setInput();
    
    return true;
}

void UIManageEditlLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxEditingDidBegin");
    
    return;
    auto index =  std::find(mEdits.begin(), mEdits.end(), editBox) - mEdits.begin();
    if (index < mEdits.size())
    {
        editBox->setPlaceHolder(mEditHolders[index].c_str());
        editBox->setText(mEditInputs[index].c_str());
        
        mLayouts[index]->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        
        mLayouts[index]->getChildByName("Text_title")->setVisible(false);
        mLayouts[index]->getChildByName("Text_value")->setVisible(false);
    }
}

void UIManageEditlLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxEditingDidEnd");
    
    CocosHelper::getWidgetByName(mLayout, "Button_save")->setVisible(true);
    return;
    auto index =  std::find(mEdits.begin(), mEdits.end(), editBox) - mEdits.begin();
    if (index < mEdits.size())
    {
        editBox->setPlaceHolder("");
        if (mEditInputs[index] != editBox->getText())
        {
            onChange();
        }
        mEditInputs[index] = editBox->getText();
        string showMsg = mEditInputs[index];
        editBox->setText("");
        
        if (editBox->getTag() == 0)
        {
            if (!getIsRightPhone(showMsg))
            {
                showMsg = "请输入正确的手机号";
            }
        }
        else if (editBox->getTag() == 2)
        {
            if (!getIsRightBankNum(showMsg))
            {
                showMsg = "请输入正确的银行卡号";
            }
        }
        
        mLayouts[index]->setBackGroundColorType(Layout::BackGroundColorType::NONE);
        
        auto Text_title = mLayouts[index]->getChildByName("Text_title");
        auto Text_value = static_cast<Text*>(mLayouts[index]->getChildByName("Text_value"));
        Text_title->setVisible(true);
        Text_value->setVisible(true);
        Text_value->setString(showMsg);
        if (showMsg == "")
        {
            Text_title->setPosition(getPointHalf(mLayouts[index]->getContentSize()));
            Text_value->setVisible(false);
        }
        else
        {
            Text_title->setPosition(getPointHalf(mLayouts[index]->getContentSize()) + Point(0, 30));
            Text_value->setPosition(getPointHalf(mLayouts[index]->getContentSize()) + Point(0, -30));
        }
    }
}

void UIManageEditlLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    CCLOG("editBoxTextChanged");
}

void UIManageEditlLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxReturn");
}

void UIManageEditlLayer::onChange()
{
    CocosHelper::getWidgetByName(mLayout, "Button_save")->setVisible(true);
}

void UIManageEditlLayer::setInput()
{
    for (int i = 0; i < mLayouts.size(); ++i)
    {
        auto Text_title = mLayouts[i]->getChildByName("Text_title");
        auto Text_value = static_cast<Text*>(mLayouts[i]->getChildByName("Text_value"));
        Text_title->setVisible(true);
        Text_value->setVisible(true);
        Text_value->setString(mEditInputs[i]);
        
        if (mEditInputs[i] == "")
        {
            Text_title->setPosition(getPointHalf(mLayouts[i]->getContentSize()));
            Text_value->setVisible(false);
        }
        else
        {
            Text_title->setPosition(getPointHalf(mLayouts[i]->getContentSize()) + Point(0, 30));
            Text_value->setPosition(getPointHalf(mLayouts[i]->getContentSize()) + Point(0, -30));
        }
    }
}











