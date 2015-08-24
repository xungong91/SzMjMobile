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
    //字界面容器
    mChildLayer = Layer::create();
    this->addChild(mChildLayer);
    
    //字界面容器
    mMainLayer = Layer::create();
    pushLayer(mMainLayer);
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_main.csb", mMainLayer, 2);
    
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
    mMainLayer->addChild(mUIModelMainLayer);
    mLayers.push_back(mUIModelMainLayer);
    
    mUIPublishMainLayer = UIPublishMainLayer::create();
    mMainLayer->addChild(mUIPublishMainLayer);
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
    mCurrentLayer->runAction
    (
     Sequence::create
     (
      FadeOutDownTiles::create(1.0f, Size(12, 18)),
      StopGrid::create(),
      CallFunc::create([this, sender]()
                       {
                           mCurrentLayer->setVisible(false);
                           mCurrentLayer = sender;
                       }),
      NULL));

}

void UIMainLayer::pushLayer(Node *layer)
{
    if (mChildLayers.size() == 0)
    {
        mChildLayer->addChild(layer);
        mChildLayers.push_back(layer);
    }
    else
    {
        //动画
        Node *back = mChildLayers.back();
        
        mChildLayer->addChild(layer);
        mChildLayers.push_back(layer);
        
        back->setPosition(Point(0, 0));
        layer->setPosition(Point(1080, 0));
        
        back->runAction(Sequence::create(MoveTo::create(0.2, Point(-540, 0)), NULL));
        layer->runAction(Sequence::create(MoveTo::create(0.2, Point(0, 0)), NULL));
    }
}

void UIMainLayer::popLayer()
{
    if (mChildLayers.size() != 0)
    {
        Node *back = mChildLayers.back();
        mChildLayers.pop_back();
        
        Node *secondBack = mChildLayers.back();
        
        secondBack->setPosition(Point(-540, 0));
        back->setPosition(Point(0, 0));
        
        secondBack->runAction(Sequence::create(MoveTo::create(0.2, Point(0, 0)), NULL));
        back->runAction(Sequence::create(MoveTo::create(0.2, Point(1080, 0)),
                                         CallFunc::create([back, this]()
                                                          {
                                                              mChildLayer->removeChild(back);
                                                          }),
                                         NULL));
    }
}













