//  UIPublishMetroChild.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/28

#include "UIPublishMetroChild.h"
#include "XHelper.h"
#include "UIMainLayer.h"
#include "UITaskInfoLayer.h"
#include "UIMainLayer.h"
#include "UIPublishTaskInfo.h"

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
    /*
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
    mClippingNode->addChild(mSelect);*/
    
    string pathStr = "publish/" + PrefixName + mName + "_%d.png";
    const char *path = pathStr.c_str();
    mImage->initWithFile(__String::createWithFormat(path, (int)(CCRANDOM_0_1() * 2))->getCString());
    mImage->setAnchorPoint(Point(0, 0));
    
    static Point gTouchStartPoint = Point::ZERO;
    
    mEventListener = EventListenerTouchOneByOne::create();
    mEventListener->retain();
    mEventListener->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        return true;
    };
    
    mEventListener->onTouchMoved = [this](Touch* touch, Event  *event)
    {
    };
    
    mEventListener->onTouchEnded = [this](Touch* touch, Event  *event)
    {
        this->onSelect();
    };
    
    mEventListener->onTouchCancelled = [this](Touch* touch, Event  *event)
    {
    };

    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mEventListener, this);
    
    //mBtn = MenuItemImage::create("publish/" + PrefixName + mName + "_0.png", "publish/" + PrefixName + mName + "_2.png");
    //mBtn->
    
    //mBtn = ImageView::create("publish/" + PrefixName + mName + "_2.png");
    mBtn = Button::create();
    mBtn->loadTextures("publish/Publish_" + mName + "_2.png", ("publish/Publish_" + mName + "_2.png").c_str());
    mBtn->addTouchEventListener(CC_CALLBACK_2(UIPublishMetroChild::CallbackClick, this));
    mBtn->setOpacity(0);
    mBtn->setPosition(Vec2(341*0.5, 340*0.5));
    this->addChild(mBtn);
    
    imageRun();
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

void UIPublishMetroChild::CallbackClick(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::BEGAN)
    {
        mBtn->setOpacity(255);
    }
    else if(type == Widget::TouchEventType::ENDED)
    {
        mBtn->setOpacity(0);
        
        if(mName == "0")
        {
            
        }
        else if(mName == "1")
        {
            UIMainLayer::gUIMainLayer->pushLayer(UIPublishTaskInfo::create());
        }
    }
    else if(type == Widget::TouchEventType::CANCELED)
    {
        mBtn->setOpacity(0);
    }
}











