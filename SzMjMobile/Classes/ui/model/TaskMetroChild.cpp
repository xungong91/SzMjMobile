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
    
    string pathStr = "taskList/" + PrefixName + mName + "_%d.png";
    const char *path = pathStr.c_str();
    mImage->initWithFile(__String::createWithFormat(path, (int)(CCRANDOM_0_1() * 2))->getCString());
    mImage->setAnchorPoint(Point(0, 0));
    
    imageRun();
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

void TaskMetroChild::onSelect()
{
    mImage->setOpacity(150);
}

void TaskMetroChild::onSelectLeave()
{
    mImage->setOpacity(255);
    UIMainLayer::gUIMainLayer->pushLayer(UITaskInfoLayer::create());
}












