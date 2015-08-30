//
//  UIWidgetMsgSprite.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/28.
//
//

#include "UIWidgetMsgSprite.h"
#include "UIMainLayer.h"

UIWidgetMsgSprite::UIWidgetMsgSprite()
{
    
}

UIWidgetMsgSprite::~UIWidgetMsgSprite()
{
    
}

bool UIWidgetMsgSprite::init()
{
    if (!Sprite::initWithFile("Metro/msgBoxBg.png"))
    {
        return false;
    }
    Sprite::setOpacity(200);
    Size size = CCDirector::getInstance()->getWinSize();
    this->setPosition(Point(size.width/2, size.height/2));
    mLabel = Label::create();
    mLabel->setSystemFontSize(45);
    mLabel->setAnchorPoint(Point(0, 0));
    mLabel->setColor(Color3B::WHITE);
    this->addChild(mLabel);
    
    return true;
}

UIWidgetMsgSprite * UIWidgetMsgSprite::getRichCB()
{
    UIWidgetMsgSprite *sprite = UIWidgetMsgSprite::create();
    UIMainLayer::gUIMainLayer->addChild(sprite, 10);
    
    sprite->runAction(Sequence::create(
                                       DelayTime::create(1.6f),
                                       MoveBy::create(0.3f, Point(0, 350)),
                                       DelayTime::create(0.8f),
                                       CallFunc::create([sprite]()
                                                        {
                                                            sprite->getParent()->removeChild(sprite);
                                                        }),
                                       NULL));
    return sprite;
}

void UIWidgetMsgSprite::setMsg(const string &msg)
{
    if (UIMainLayer::gUIMainLayer)
    {
        UIWidgetMsgSprite *sprite = getRichCB();
        sprite->mLabel->setString(msg.c_str());
        sprite->setSize();
    }
}

void UIWidgetMsgSprite::setSize()
{
    mLabel->setPosition((Point(this->getContentSize().width/2, this->getContentSize().height/2 - 70)) +
                        (Point(-mLabel->getContentSize().width/2, -mLabel->getContentSize().height/2)));
}


















