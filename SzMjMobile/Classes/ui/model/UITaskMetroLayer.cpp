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
    
    
    DrawNode* shap = DrawNode::create();
    Point point[4] = {Point(0, 0), Point(1080, 0), Point(1080, 1388), Point(0, 1388)};
    shap->drawPolygon(point, 4, Color4F(255, 255, 255, 255), 2, Color4F(255, 255, 255, 255));
    ClippingNode *mClippingNode = ClippingNode::create();
    mClippingNode->setStencil(shap);
    mClippingNode->setAnchorPoint(Point(0.0f, 0.0f));
    mClippingNode->setPosition(Point(0, 0));
    this->addChild(mClippingNode);
    
    mMoveLayer = Layer::create();
    mClippingNode->addChild(mMoveLayer);
    
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

void UITaskMetroLayer::onTouchSwitch(bool isTouch)
{
    if (isTouch)
    {
        mMetroTouchManage->setTouchMove();
    }
    else
    {
        mMetroTouchManage->setTouchNull();
    }
}

void UITaskMetroLayer::setTouch()
{
    //mMetroTouchManage->setInfo(this, _eventDispatcher, mMoveLayer, mMetroSpriteManage);
    mMetroTouchManage->setInfo(this, _eventDispatcher, mMoveLayer, mMetroChildManager);
    mMetroTouchManage->setOffsetPoint(Point(0, 165));
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


















