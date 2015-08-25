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
        return false;
    
    this->addChild(UILogin1Layer::create());
    
    return true;
}

void UIMainLayer::intoMain()
{
    //子界面容器
    mChildLayer = Layer::create();
    this->addChild(mChildLayer);
    
    //子界面容器
    mMainLayer = Layer::create();
    pushLayer(mMainLayer);
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_main.csb", mMainLayer, 2);
    
    Panel_tools = CocosHelper::getWidgetByName(mLayout, "Panel_tools");
    
    mBtnModel = (Button*)CocosHelper::getNodeByName(mLayout, "Button_mote");
    mBtnModel->addTouchEventListener(CC_CALLBACK_2(UIMainLayer::CallbackMenu, this));
    mBtnModel->loadTextures("hall/Model_1.png", "hall/Model_1.png");
    mBtnModel->setPressedActionEnabled(false);
    
    mBtnPublish = (Button*)CocosHelper::getNodeByName(mLayout, "Button_fabu");
    mBtnPublish->addTouchEventListener(CC_CALLBACK_2(UIMainLayer::CallbackMenu, this));
    
    mBtnProfit = (Button*)CocosHelper::getNodeByName(mLayout, "Button_qian");
    mBtnProfit->addTouchEventListener(CC_CALLBACK_2(UIMainLayer::CallbackMenu, this));
    
    mBtnGrab = (Button*)CocosHelper::getNodeByName(mLayout, "Button_qiangdan");
    mBtnGrab->addTouchEventListener(CC_CALLBACK_2(UIMainLayer::CallbackMenu, this));
    
    mBtnUpdate = (Button*)CocosHelper::getNodeByName(mLayout, "Button_gengxin");
    mBtnUpdate->addTouchEventListener(CC_CALLBACK_2(UIMainLayer::CallbackMenu, this));
    
    
    /*
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
    */
    
    /*
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
     */
    
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

//菜单按钮事件
void UIMainLayer::CallbackMenu(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        mBtnModel->loadTextures("hall/Model_0.png", "hall/Model_0.png");
        mBtnModel->setPressedActionEnabled(true);
        
        mBtnPublish->loadTextures("hall/Publish_0.png", "hall/Publish_0.png");
        mBtnPublish->setPressedActionEnabled(true);
        
        mBtnProfit->loadTextures("hall/Profit_0.png", "hall/Profit_0.png");
        mBtnProfit->setPressedActionEnabled(true);
        
        mBtnGrab->loadTextures("hall/Grab_0.png", "hall/Grab_0.png");
        mBtnGrab->setPressedActionEnabled(true);
        
        mBtnUpdate->loadTextures("hall/Update_0.png", "hall/Update_0.png");
        mBtnUpdate->setPressedActionEnabled(true);
        
        if(sender == mBtnModel)
        {
            mBtnModel->loadTextures("hall/Model_1.png", "hall/Model_1.png");
            mBtnModel->setPressedActionEnabled(false);
            intoModelLayer();
        }
        else if(sender == mBtnPublish)
        {
            mBtnPublish->loadTextures("hall/Publish_1.png", "hall/Publish_1.png");
            mBtnPublish->setPressedActionEnabled(false);
            intoPublishLayer();
        }
        else if(sender == mBtnProfit)
        {
            mBtnProfit->loadTextures("hall/Profit_1.png", "hall/Profit_1.png");
            mBtnProfit->setPressedActionEnabled(false);
        }
        else if (sender == mBtnGrab)
        {
            mBtnGrab->loadTextures("hall/Grab_1.png", "hall/Grab_1.png");
            mBtnGrab->setPressedActionEnabled(false);
        }
        else if (sender == mBtnUpdate)
        {
            mBtnUpdate->loadTextures("hall/Update_1.png", "hall/Update_1.png");
            mBtnUpdate->setPressedActionEnabled(false);
        }
    }
}












