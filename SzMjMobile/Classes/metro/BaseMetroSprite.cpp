//
//  BaseMetroSprite.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#include "BaseMetroSprite.h"

//----------------------
//MetroSpriteColor
//----------------------

MetroSpriteColor *MetroSpriteColor::create()
{
    MetroSpriteColor* ret = new (std::nothrow) MetroSpriteColor();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool MetroSpriteColor::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    
    return true;
}

void MetroSpriteColor::setLayerColor(const Color4B& color, GLfloat width, GLfloat height)
{
    this->initWithColor(color, width, height);
}

//----------------------
//BaseMetroSprite
//----------------------

BaseMetroSprite::BaseMetroSprite()
{
    
}

BaseMetroSprite::~BaseMetroSprite()
{
    
}

bool BaseMetroSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    this->setAnchorPoint(Point(0, 0));
    
    mBgColor = MetroSpriteColor::create();
    this->addChild(mBgColor);
    
    mClippingNode = ClippingNode::create();;
    mClippingNode->setAnchorPoint(Point(0, 0));
    mClippingNode->setPosition(0, 0);
    DrawNode *shap = DrawNode::create();
    shap->drawSolidRect(Point(0, 0), Point(1, 1), Color4F(255, 255, 255, 255));
    shap->setPosition(Point(0, 0));
    shap->setAnchorPoint(Point(0, 0));
    mClippingNode->setStencil(shap);
    mClippingNode->setInverted(false);
    this->addChild(mClippingNode);
    
    mNameLabel = Label::create();
    mNameLabel->setString("");
    mNameLabel->setSystemFontSize(24);
    mNameLabel->setAnchorPoint(Point(0, 0.5));
    mNameLabel->setPosition(Point(20, 20));
    mClippingNode->addChild(mNameLabel, 1);
    
    return true;
}

void BaseMetroSprite::setStyle(MetroSpriteStyle style)
{
    mStyle = style;
    
    auto size = getSizeForStyle(style);
    this->setContentSize(size);
    
    mBgColor->changeWidthAndHeight(size.width, size.height);
    
    //遮罩
    DrawNode* shap = static_cast<DrawNode*>(mClippingNode->getStencil());
    shap->drawSolidRect(Point(0, 0), Point(size.width, size.height), Color4F(255, 255, 255, 255));
}

void BaseMetroSprite::setBgColor(Color4B color4b)
{
    auto size = getSizeForStyle(mStyle);
    mBgColor->setLayerColor(color4b, size.width, size.height);
}

void BaseMetroSprite::setMetorName(const string &name)
{
    mNameLabel->setString(name);
}

void BaseMetroSprite::onSelect()
{
    mBgColor->setOpacity(150);
}

void BaseMetroSprite::onSelectLeave()
{
    mBgColor->setOpacity(255);
}











