//  TaskMetroChild.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#include "TaskMetroChild.h"
#include "XHelper.h"
#include "UIMainLayer.h"
#include "UITaskInfoLayer.h"

const string PrefixName = "Task_";

bool TaskMetroChild::init()
{
    if (!BaseMetroSprite::init())
        return false;
    
    mImage = Sprite::create();
    mClippingNode->addChild(mImage);
    
    return true;
}

void TaskMetroChild::setStyle(MetroSpriteStyle style)
{
    BaseMetroSprite::setStyle(style);
}

void TaskMetroChild::LoadImages(int name)
{
    stringstream ss;
    ss<<name;
    ss>>mName;
    
    string snormal0 = __String::createWithFormat("taskList/Task_%d_0.png", name)->getCString();
    string snormal1 = __String::createWithFormat("taskList/Task_%d_1.png", name)->getCString();
    string sselect = __String::createWithFormat("taskList/Task_%d_2.png", name)->getCString();
    
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

void TaskMetroChild::imageRun()
{
    string nextPathStr = "taskList/" + PrefixName + mName + "_%d.png";
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

float TaskMetroChild::setHanldRunAction()
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

void TaskMetroChild::onSelect()
{
    mSelect->setVisible(true);
}

void TaskMetroChild::onSelectLeave()
{
    mSelect->setVisible(false);
    UIMainLayer::gUIMainLayer->pushLayer(UITaskInfoLayer::create());
}












