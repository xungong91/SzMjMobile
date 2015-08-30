//  UIChatLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/29

#include "UIChatLayer.h"
#include "UIChatChildLayer.h"

bool UIChatLayer::init()
{
    if(!UIBaseTopLayer::init())
        return false;
    
    InitUI();
    
    return true;
}

void UIChatLayer::InitUI()
{
    //加载UI
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_chat_info.csb", this);
    
    //输入框
    mInput = ui::EditBox::create(Size(670, 85), ui::Scale9Sprite::create(" "));
    mInput->setFont("微软雅黑", 48);
    mInput->setFontColor(Color3B(0, 0, 0));
    mInput->setDelegate(this);
    mInput->setPosition(Vec2(390, 80));
    addChild(mInput);
    
    //表情按钮
    mBtnFace = (Button*)CocosHelper::getNodeByName(mLayout, "BtnBiaoQing");
    
    //发送按钮
    mBtnSend = (Button*)CocosHelper::getNodeByName(mLayout, "BtnSend");
    mBtnSend->setPressedActionEnabled(false);
    mBtnSend->addTouchEventListener(CC_CALLBACK_2(UIChatLayer::CallbackBtnSend, this));
    
    //聊天列表
    mList = (ListView*)CocosHelper::getNodeByName(mLayout, "ListContent");
    //mList->pushBackCustomItem(UIChatChildLayer::create());
    //mList->refreshView();
}

//发送按钮事件
void UIChatLayer::CallbackBtnSend(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        if(strcmp(mInput->getText(), "") != 0)
        {
            UIChatChildLayer *child = UIChatChildLayer::create();
            child->SetString(0, mInput->getText());
            mList->pushBackCustomItem(child);
            mList->refreshView();
        }
    }
}





void UIChatLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox)
{
}

void UIChatLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
}

void UIChatLayer::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    if(strcmp(mInput->getText(), "") != 0)
    {
        mBtnSend->loadTextures("chat/Chat_Btn_Send_1.png", "chat/Chat_Btn_Send_1.png");
        mBtnSend->setPressedActionEnabled(true);
    }
}

void UIChatLayer::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
}