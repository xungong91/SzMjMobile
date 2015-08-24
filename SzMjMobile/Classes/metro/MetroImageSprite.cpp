//
//  MetroImageSprite.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/14.
//
//

#include "MetroImageSprite.h"
#include "XHelper.h"

bool MetroImageSprite::init()
{
    if (!BaseMetroSprite::init())
    {
        return false;
    }
    
    mImage = Sprite::create();
    mClippingNode->addChild(mImage);
    
    loadImages();
    return true;
}

void MetroImageSprite::setStyle(MetroSpriteStyle style)
{
    BaseMetroSprite::setStyle(style);
}

void MetroImageSprite::loadImages()
{
    mImage->initWithFile(__String::createWithFormat("Metro/images/2_%d.jpg", (int)(CCRANDOM_0_1() * 8))->getCString());
    mImage->setAnchorPoint(Point(0, 0));
    
    imageRun();
}

void MetroImageSprite::imageRun()
{
    string nextfile = __String::createWithFormat("Metro/images/2_%d.jpg", (int)(CCRANDOM_0_1() * 8))->getCString();
    
    mImage->setPosition(Point(0, 0));
    mImage->stopAllActions();
    mImage->removeAllChildren();
    
    Sprite *temp = Sprite::create(nextfile);
    temp->setPosition(Point(0, -200));
    temp->setAnchorPoint(Point(0, 0));
    mImage->addChild(temp);
    
    mImage->runAction
    (
     Sequence::create
     (
      DelayTime::create(CCRANDOM_0_1() * 3 + 1),
      MoveTo::create(0.3f, Point(0, 200)),
      CallFunc::create([this, nextfile]()
                       {
                           mImage->initWithFile(nextfile);
                           mImage->setAnchorPoint(Point(0, 0));
                           imageRun();
                       }),
      NULL
      )
     );
}

void MetroImageSprite::onSelect()
{
    mImage->setOpacity(150);
}

void MetroImageSprite::onSelectLeave()
{
    mImage->setOpacity(255);
}











