//
//  UIMediaSelectItemLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#include "UIMediaSelectItemLayer.h"
#include "UIMediaVideoLayer.h"

UIMediaSelectItemLayer::UIMediaSelectItemLayer()
: mIsSelect(false)
{
    
}

UIMediaSelectItemLayer::~UIMediaSelectItemLayer()
{
    
}

bool UIMediaSelectItemLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    this->setContentSize(Size(520, 520));
    
    mSelectSprite = Sprite::create("CloseNormal.png");
    mSelectSprite->setPosition(Point(500, 500));
    mSelectSprite->setScale(2.0f);
    mSelectSprite->setVisible(mIsSelect);
    this->addChild(mSelectSprite, 1);
    
    return true;
}

void UIMediaSelectItemLayer::setResInfo(const string &file, UIMediaType type)
{
    mType = type;
    mFile = file;
    
    if (type == UIMediaType::image)
    {
        Sprite *image = Sprite::create(file);
        image->setScale(this->getContentSize().width / image->getContentSize().width,
                        this->getContentSize().height / image->getContentSize().height);
        image->setAnchorPoint(Point::ZERO);
        this->addChild(image);
    }
    else if (type == UIMediaType::video)
    {
        UIMediaVideoLayer *image = UIMediaVideoLayer::create();
        image->setVideoFile(file);
        image->setContentSize(this->getContentSize());
        this->addChild(image);
    }
}

void UIMediaSelectItemLayer::onSelect()
{
    
}

void UIMediaSelectItemLayer::onSelectLeave()
{
    
}

void UIMediaSelectItemLayer::selectThis()
{
    mIsSelect = !mIsSelect;
    mSelectSprite->setVisible(mIsSelect);
}

UIImageStruct UIMediaSelectItemLayer::getType()
{
    UIImageStruct stru = {mType, mFile};
    return stru;
}




















