//
//  UIWidgetSearchLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/30.
//
//

#include "UIWidgetSearchLayer.h"

bool UIWidgetSearchLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    mDidEndFunc = nullptr;
    
    mLayout = CSLoader::createNode("CCS_WIDGET_Search.csb");
    this->addChild(mLayout);
    this->setContentSize(Size(1080, 135));
    
    Layout *layout = static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_edit"));
    Size size = layout->getContentSize();
    mSearchEdit = EditBox::create(size, Scale9Sprite::create("Transparent.png"));
    mSearchEdit->setPosition(Point::ZERO);
    mSearchEdit->setAnchorPoint(Point::ZERO);
    mSearchEdit->setFontSize(60);
    mSearchEdit->setFontColor(Color3B::BLACK);
    mSearchEdit->setPlaceHolder("搜索模特昵称");
    mSearchEdit->setPlaceholderFontColor(Color3B::WHITE);
    mSearchEdit->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    mSearchEdit->setDelegate(this);
    layout->addChild(mSearchEdit);
    
    return true;
}

void UIWidgetSearchLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxEditingDidBegin");
}

void UIWidgetSearchLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxEditingDidEnd");
    if (mDidEndFunc)
    {
        mDidEndFunc(mSearchEdit->getText());
        this->setVisible(false);
    }
}

void UIWidgetSearchLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    CCLOG("editBoxTextChanged");
}

void UIWidgetSearchLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
    CCLOG("editBoxReturn");
}

void UIWidgetSearchLayer::setVisible(bool isVisble)
{
    Layer::setVisible(isVisble);
    if (isVisble)
    {
        this->stopAllActions();
        this->setScaleY(0);
        
        this->runAction(Sequence::create(ScaleTo::create(0.3, 1, 1), NULL));
    }
}





