//
//  MetroMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/13.
//
//

#include "MetroMainLayer.h"

#include <functional>
#include <vector>

#include "XHelper.h"
#include "MetroTextSprite.h"
#include "MetroImageSprite.h"

using namespace std;

MetroMainLayer::MetroMainLayer()
{
    mMetroSpriteManage = new MetroSpriteManage();
    mMetroTouchManage = new MetroTouchManage();
}

MetroMainLayer::~MetroMainLayer()
{
    delete mMetroSpriteManage;
    delete mMetroTouchManage;
}

bool MetroMainLayer::init()
{
    if (!BaseLayer::init())
    {
        return false;
    }
    
    auto bgLayer = LayerColor::create(Color4B(255, 255, 255, 255), getSizeWin().width, getSizeWin().height);
    this->addChild(bgLayer);
    
    mMoveLayer = Layer::create();
    this->addChild(mMoveLayer);
    
    testAddChild();
    
    //touch move layer
    setTouch();
    
    //切换按钮
    auto menuChangeTouch = MenuItemFont::create("移动模式", [this](Ref *sender)
                                            {
                                                static int menuTouchStage = 0;
                                                if (menuTouchStage == 0)
                                                {
                                                    static_cast<MenuItemFont*>(sender)->setString("排列模式");
                                                    mMetroTouchManage->setTouchChange();
                                                    menuTouchStage = 1;
                                                }
                                                else
                                                {
                                                    static_cast<MenuItemFont*>(sender)->setString("移动模式");
                                                    mMetroTouchManage->setTouchMove();
                                                    menuTouchStage = 0;
                                                }
                                            });
    menuChangeTouch->setPosition(getPointHalf(getSizeWin()) - Point(80, 30
                                                                    ));
    menuChangeTouch->setColor(Color3B::BLACK);
    menuChangeTouch->setFontSize(26);
    this->addChild(Menu::create(menuChangeTouch, NULL));
    
    
    this->scheduleUpdate();
    return true;
}

void MetroMainLayer::onEnter()
{
    BaseLayer::onEnter();
}

void MetroMainLayer::onExit()
{
    BaseLayer::onExit();
}

void MetroMainLayer::setTouch()
{
    mMetroTouchManage->setInfo(this, _eventDispatcher, mMoveLayer, mMetroSpriteManage);
    mMetroTouchManage->setTouchMove();
}

void MetroMainLayer::update(float dt)
{
    BaseLayer::update(dt);
}

void MetroMainLayer::testAddChild()
{
    mMetroSpriteManage->setMetro(mMoveLayer);
}


















