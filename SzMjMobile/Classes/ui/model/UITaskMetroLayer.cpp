//  UITaskMetroLayer.cpp
//  SzMjMobile
//  Created by LiuXueCheng on 15/8/25

#include "UITaskMetroLayer.h"

#include <functional>
#include <vector>

#include "XHelper.h"
#include "MetroTextSprite.h"
#include "MetroImageSprite.h"

using namespace std;

UITaskMetroLayer::UITaskMetroLayer()
{
    //mMetroSpriteManage = new MetroSpriteManage();
    mMetroChildManager = new TaskMetroChildManager();
    mMetroTouchManage = new MetroTouchManage();
}

UITaskMetroLayer::~UITaskMetroLayer()
{
    //delete mMetroSpriteManage;
    delete mMetroChildManager;
    delete mMetroTouchManage;
}

bool UITaskMetroLayer::init()
{
    if (!BaseLayer::init())
        return false;
    
    //auto bgLayer = LayerColor::create(Color4B(255, 255, 255, 255), getSizeWin().width, getSizeWin().height - 530);
    //this->addChild(bgLayer);
    
    mMoveLayer = Layer::create();
    this->addChild(mMoveLayer);
    
    mMetroChildManager->setMetro(mMoveLayer);
    //testAddChild();
    
    //touch move layer
    setTouch();
    
    this->scheduleUpdate();
    return true;
}

void UITaskMetroLayer::onEnter()
{
    BaseLayer::onEnter();
}

void UITaskMetroLayer::onExit()
{
    BaseLayer::onExit();
}

void UITaskMetroLayer::setTouch()
{
    //mMetroTouchManage->setInfo(this, _eventDispatcher, mMoveLayer, mMetroSpriteManage);
    mMetroTouchManage->setInfo(this, _eventDispatcher, mMoveLayer, mMetroChildManager);
    mMetroTouchManage->setTouchMove();
}

void UITaskMetroLayer::update(float dt)
{
    BaseLayer::update(dt);
}

void UITaskMetroLayer::testAddChild()
{
    //mMetroSpriteManage->setMetro(mMoveLayer);
    mMetroChildManager->setMetro(mMoveLayer);
}


















