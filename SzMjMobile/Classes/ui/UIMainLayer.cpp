//
//  UIMainLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#include "UIMainLayer.h"
#include "CocosHelper.h"
#include "UILogin1Layer.h"

UIMainLayer *UIMainLayer::gUIMainLayer = nullptr;

UIMainLayer::UIMainLayer()
: mCurrentLayer(nullptr)
, mLastLayer(nullptr)
{
    gUIMainLayer = this;
}

UIMainLayer::~UIMainLayer()
{
    gUIMainLayer = nullptr;
}

bool UIMainLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    this->addChild(UILogin1Layer::create());
    
    return true;
}

void UIMainLayer::intoMain()
{
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_main.csb", this, 2);
    
    Panel_tools = CocosHelper::getWidgetByName(mLayout, "Panel_tools");
    
    CocosHelper::getWidgetByName(mLayout, "Button_mote")->addTouchEventListener
    (
     [this](Ref* sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             intoModelLayer();
         }
     }
    );
    
    CocosHelper::getWidgetByName(mLayout, "Button_fabu")->addTouchEventListener
    (
     [this](Ref* sender, Widget::TouchEventType type)
     {
         if (type == Widget::TouchEventType::ENDED)
         {
             intoPublishLayer();
         }
     }
     );
    
    mUIModelMainLayer = UIModelMainLayer::create();
    this->addChild(mUIModelMainLayer);
    mLayers.push_back(mUIModelMainLayer);
    
    mUIPublishMainLayer = UIPublishMainLayer::create();
    this->addChild(mUIPublishMainLayer);
    mLayers.push_back(mUIPublishMainLayer);
    
    for (auto it : mLayers)
    {
        it->setVisible(false);
    }
    
    intoModelLayer();
}

void UIMainLayer::intoModelLayer()
{
    if (mCurrentLayer == mUIModelMainLayer)
    {
        return;
    }
    
    if (mCurrentLayer)
    {
        changeAction(mUIModelMainLayer);
    }
    else
    {
        mUIModelMainLayer->setVisible(true);
        mCurrentLayer = mUIModelMainLayer;
    }
}

void UIMainLayer::intoPublishLayer()
{
//    for (auto it : mLayers)
//    {
//        it->setVisible(false);
//    }
    if (mCurrentLayer == mUIPublishMainLayer)
    {
        return;
    }
    
    if (mCurrentLayer)
    {
        changeAction(mUIPublishMainLayer);
    }
    else
    {
        mUIPublishMainLayer->setVisible(true);
        mCurrentLayer = mUIPublishMainLayer;
    }
}

void UIMainLayer::changeAction(UIBaseCenterLayer *sender)
{
    sender->setVisible(true);
    sender->setZOrder(0);
    
    mCurrentLayer->setZOrder(1);
    
    Panel_tools->setPosition(Point(0, 0));
    Panel_tools->runAction
    (
     Sequence::create
     (
      MoveTo::create(0.2, Point(0, 0)),
      CallFunc::create([this, sender]()
                       {
                           mCurrentLayer->runAction
                           (
                            Sequence::create
                            (
                             FadeOutBLTiles::create(1.0f, Size(12, 18)),
                             StopGrid::create(),
                             CallFunc::create([this, sender]()
                                              {
                                                  mCurrentLayer->setVisible(false);
                                                  mCurrentLayer = sender;
                                              }),
                             NULL));
                           
                       }),
      DelayTime::create(1.0f),
      MoveTo::create(0.2, Point(0, 0)),
      NULL));

}















