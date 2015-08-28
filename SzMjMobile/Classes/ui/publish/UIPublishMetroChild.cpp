//  UIPublishMetroChild.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/28

#include "UIPublishMetroChild.h"
#include "XHelper.h"
#include "UIMainLayer.h"
#include "UITaskInfoLayer.h"

const string PrefixName = "Publish_";

bool UIPublishMetroChild::init()
{
    if (!BaseMetroSprite::init())
        return false;
    
    mImage = Sprite::create();
    mClippingNode->addChild(mImage);
    
    return true;
}

void UIPublishMetroChild::setStyle(MetroSpriteStyle style)
{
    BaseMetroSprite::setStyle(style);
}

void UIPublishMetroChild::LoadImages(int name)
{
    stringstream ss;
    ss<<name;
    ss>>mName;
    
    string snormal0 = __String::createWithFormat("publish/Publish_%d_0.png", name)->getCString();
    string snormal1 = __String::createWithFormat("publish/Publish_%d_1.png", name)->getCString();
    string sselect = __String::createWithFormat("publish/Publish_%d_2.png", name)->getCString();
    
    mNormal0 = Sprite::create(snormal0);
    mNormal0->setAnchorPoint(Point::ZERO);
    mClippingNode->addChild(mNormal0);
    mShowIndex = 0;
    
    mNormal1 = Sprite::create(snormal1);
    mNormal1->setAnchorPoint(Point::ZERO);
    mNormal1->setPosition(Point(0, 350));
    mClippingNode->addChild(mNormal1);
    
    mSelect = Sprite::create(sselect);
    mSelect->setAnchorPoint(Point::ZERO);
    mSelect->setVisible(false);
    mClippingNode->addChild(mSelect);
    
    //    string pathStr = "taskList/" + PrefixName + mName + "_%d.png";
    //    const char *path = pathStr.c_str();
    //    mImage->initWithFile(__String::createWithFormat(path, (int)(CCRANDOM_0_1() * 2))->getCString());
    //    mImage->setAnchorPoint(Point(0, 0));
    //
    //    imageRun();
}

void UIPublishMetroChild::imageRun()
{
    string nextPathStr = "publish/" + PrefixName + mName + "_%d.png";
    const char *nextPath = nextPathStr.c_str();
    string nextfile = __String::createWithFormat(nextPath, (int)(CCRANDOM_0_1() * 2))->getCString();
    
    mImage->setPosition(Point(0, 0));
    mImage->stopAllActions();
    mImage->removeAllChildren();
    
    Sprite *temp = Sprite::create(nextfile);
    temp->setPosition(Point(0, -350));
    temp->setAnchorPoint(Point(0, 0));
    mImage->addChild(temp);
    
    mImage->runAction
    (
     Sequence::create
     (
      DelayTime::create(CCRANDOM_0_1() * 5 + 1),
      MoveTo::create(0.3f, Point(0, 350)),
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

float UIPublishMetroChild::setHanldRunAction(function<void ()> func)
{
    float moveTime = 0.3f;
    mNormal0->stopAllActions();
    mNormal1->stopAllActions();
    
    if (mShowIndex == 0)
    {
        mNormal0->runAction
        (
         Sequence::create
         (
          MoveTo::create(moveTime, Point(0, - 350)),
          CallFunc::create(func),
          NULL)
         );
        mNormal1->runAction
        (
         Sequence::create
         (
          MoveTo::create(moveTime, Point(0, 0)),
          NULL)
         );
        mShowIndex = 1;
    }
    else
    {
        mNormal0->runAction
        (
         Sequence::create
         (
          MoveTo::create(moveTime, Point(0, 0)),
          CallFunc::create(func),
          NULL)
         );
        mNormal1->runAction
        (
         Sequence::create
         (
          MoveTo::create(moveTime, Point(0, 350)),
          NULL)
         );
        mShowIndex = 0;
    }
    return moveTime;
}

void UIPublishMetroChild::onSelect()
{
    mSelect->setVisible(true);
}

void UIPublishMetroChild::onSelectLeave(bool isMove)
{
    mSelect->setVisible(false);
    if (!isMove)
    {
        UIMainLayer::gUIMainLayer->pushLayer(UITaskInfoLayer::create());
    }
}












