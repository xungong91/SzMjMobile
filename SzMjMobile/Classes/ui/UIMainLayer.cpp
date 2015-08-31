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
#include "UIMediaSelectLayer.h"

UIMainLayer *UIMainLayer::gUIMainLayer = nullptr;

UIMainLayer::UIMainLayer()
: mCurrentLayer(nullptr)
, mChildLayer(nullptr)
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
    
    //TODO
//    this->addChild(UILogin1Layer::create());
    intoMain();
    
    mListenerkeyPad = EventListenerKeyboard::create();
    mListenerkeyPad->onKeyReleased = CC_CALLBACK_2(UIMainLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(mListenerkeyPad, -10);
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
    
    mUIIncomeMainLayer = UIIncomeMainLayer::create();
    mMainLayer->addChild(mUIIncomeMainLayer);
    mLayers.push_back(mUIIncomeMainLayer);
    
    mUIGrabMainLayer = UIGrabMainLayer::create();
    mMainLayer->addChild(mUIGrabMainLayer);
    mLayers.push_back(mUIGrabMainLayer);
    
    mUIManageMainLayer = UIManageMainLayer::create();
    mMainLayer->addChild(mUIManageMainLayer);
    mLayers.push_back(mUIManageMainLayer);
    
    for (auto it : mLayers)
    {
        it->setVisible(false);
    }
    
    intoModelLayer();
}

void UIMainLayer::intoModelLayer()
{
    removeAllChiLayer();
    mBtnModel->loadTextures("hall/Model_1.png", "hall/Model_1.png");
    mBtnModel->setTouchEnabled(false);
    
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
    removeAllChiLayer();
    mBtnPublish->loadTextures("hall/Publish_1.png", "hall/Publish_1.png");
    mBtnPublish->setTouchEnabled(false);
    
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

void UIMainLayer::intoIncomeLayer()
{
    removeAllChiLayer();
    mBtnProfit->loadTextures("hall/Profit_1.png", "hall/Profit_1.png");
    mBtnProfit->setTouchEnabled(false);
    
    UIBaseCenterLayer *temp = mUIIncomeMainLayer;
    if (mCurrentLayer == temp)
    {
        return;
    }
    
    if (mCurrentLayer)
    {
        changeAction(temp);
    }
    else
    {
        temp->setVisible(true);
        mCurrentLayer = temp;
    }
}

void UIMainLayer::intoGrabLayer()
{
    removeAllChiLayer();
    mBtnGrab->loadTextures("hall/Grab_1.png", "hall/Grab_1.png");
    mBtnGrab->setTouchEnabled(false);
    
    UIBaseCenterLayer *temp = mUIGrabMainLayer;
    if (mCurrentLayer == temp)
    {
        return;
    }
    
    if (mCurrentLayer)
    {
        changeAction(temp);
    }
    else
    {
        temp->setVisible(true);
        mCurrentLayer = temp;
    }
}

void UIMainLayer::intoManageLayer()
{
    removeAllChiLayer();
    mBtnUpdate->loadTextures("hall/Update_1.png", "hall/Update_1.png");
    mBtnUpdate->setTouchEnabled(false);
    
    UIBaseCenterLayer *temp = mUIManageMainLayer;
    if (mCurrentLayer == temp)
    {
        return;
    }
    
    if (mCurrentLayer)
    {
        changeAction(temp);
    }
    else
    {
        temp->setVisible(true);
        mCurrentLayer = temp;
    }
}

void UIMainLayer::removeAllChiLayer()
{
    mBtnModel->loadTextures("hall/Model_0.png", "hall/Model_0.png");
    mBtnModel->setTouchEnabled(true);
    
    mBtnPublish->loadTextures("hall/Publish_0.png", "hall/Publish_0.png");
    mBtnPublish->setTouchEnabled(true);
    
    mBtnProfit->loadTextures("hall/Profit_0.png", "hall/Profit_0.png");
    mBtnProfit->setTouchEnabled(true);
    
    mBtnGrab->loadTextures("hall/Grab_0.png", "hall/Grab_0.png");
    mBtnGrab->setTouchEnabled(true);
    
    mBtnUpdate->loadTextures("hall/Update_0.png", "hall/Update_0.png");
    mBtnUpdate->setTouchEnabled(true);
    
    
    bool isRemove(false);
    
    if (mChildLayers.size() != 1)
    {
        for (auto it = mChildLayers.begin(); it != mChildLayers.end(); )
        {
            if ((*it) == mMainLayer)
            {
                ++it;
            }
            else
            {
                mChildLayer->removeChild(*it);
                it = mChildLayers.erase(it);
                isRemove = true;
            }
        }
    }
    
    if (isRemove)
    {
        mMainLayer->setPosition(Point(0, 0));
    }
}

void UIMainLayer::changeAction(UIBaseCenterLayer *sender)
{
    sender->setVisible(true);
    mCurrentLayer->setVisible(false);
    mCurrentLayer = sender;
    return;
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
        if(sender == mBtnModel)
        {
            intoModelLayer();
        }
        else if(sender == mBtnPublish)
        {
            intoPublishLayer();
        }
        else if(sender == mBtnProfit)
        {
            intoIncomeLayer();
        }
        else if (sender == mBtnGrab)
        {
            intoGrabLayer();
        }
        else if (sender == mBtnUpdate)
        {
            intoManageLayer();
        }
    }
}

void UIMainLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
    {
        onKeyReturn();
    }
}

void UIMainLayer::onKeyReturn()
{
    if (UIMediaSelectLayer::gUIMediaSelectLayer)
    {
//        UIMediaSelectLayer::gUIMediaSelectLayer->getParent()->removeChild(UIMediaSelectLayer::gUIMediaSelectLayer);
        return;
    }
    else
    {
        if (!mChildLayer)
        {
            Director::getInstance()->end();
        }
        else
        {
            if (mChildLayer->getChildrenCount() > 1)
            {
                popLayer();
            }
            else
            {
                Director::getInstance()->end();
            }
        }
    }
}











