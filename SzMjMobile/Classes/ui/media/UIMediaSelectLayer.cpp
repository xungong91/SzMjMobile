//
//  UIMediaSelectLayer.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/19.
//
//

#include "UIMediaSelectLayer.h"
#include "UIModelAddLayer.h"
#include "XHelper.h"
#include "UIMediaLayer.h"
#include "UIInfoManage.h"

UIMediaSelectLayer::UIMediaSelectLayer()
: mSelectMediaItem(nullptr)
{
    
}

UIMediaSelectLayer::~UIMediaSelectLayer()
{
    
}

bool UIMediaSelectLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_mediaSelect.csb", this);
    CocosHelper::getNodeByName(mLayout, "Panel_center")->setZOrder(1);
    
    addPanelTouch(static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_cancel")), [this]()
                  {
                      this->getParent()->removeChild(this);
                  });
    
    addPanelTouch(static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Panel_ok")), [this]()
                  {
                      vector<UIImageStruct> types;
                      for (int i = 0; i < mSelectSprites.size(); ++i)
                      {
                          types.push_back(mSelectSprites[i]->getType());
                      }
                      auto layer = UIMediaLayer::create();
                      layer->setMediaInfo(types);
                      //this->getParent()->addChild(layer);
                      
                      
                      UIImageStruct imageStruct = mSelectSprites[0]->getType();
                      string filePath = imageStruct.file;
                      ((UIModelAddLayer*)this->getParent())->AddImage(filePath);
                      
                      this->getParent()->removeChild(this);
                  });
    
    mMoveLayer = Layer::create();
    mMoveLayer->setAnchorPoint(Point(0, 1));
    mMoveLayer->setPosition(Point(0, getSizeWin().height));
    CocosHelper::getNodeByName(mLayout, "Panel")->addChild(mMoveLayer);
    
    int cardCount = 13;
    
    mMoveLayer->setContentSize(Size(0, (cardCount / 2) * 540 + (cardCount % 2 == 0 ? 0 : 540)));
    
    for (int i = 0; i < cardCount; ++i)
    {
        if (i <= 0)
        {
            auto video = UIMediaSelectItemLayer::create();
            video->setResInfo(__String::createWithFormat("card/vdo%d.mp4", i)->getCString(), UIMediaType::video);
            Point p = Point(i % 2 * 540, -(int)(i / 2) * 540 - 540);
            video->setPosition(p);
            mMoveLayer->addChild(video);
        }
        else
        {
            auto item = UIMediaSelectItemLayer::create();
            item->setResInfo(__String::createWithFormat("card/img%d.jpg", i - 1)->getCString(), UIMediaType::image);
            Point p = Point(i % 2 * 540, -(int)(i / 2) * 540 - 540);
            item->setPosition(p);
            mMoveLayer->addChild(item);
        }
    }
    
    setOkButtonStatas();
    
    return true;
}

void UIMediaSelectLayer::onEnter()
{
    UIBaseLayer::onEnter();
    
    auto mEventListenerMove = EventListenerTouchOneByOne::create();
    mEventListenerMove->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        mTouchStartPoint = touch->getLocation();
        mMoveLayerStartPoint = mMoveLayer->getPosition();
        
        onSelectBegan(mTouchStartPoint);
        return true;
    };
    
    mEventListenerMove->onTouchMoved = [this](Touch* touch, Event  *event)
    {
        Point local = touch->getLocation();
        float offsety = local.y - mTouchStartPoint.y;
        mMoveLayer->setPosition(mMoveLayerStartPoint + Point(0, offsety));
        
        onSelectMove(local);
    };
    
    mEventListenerMove->onTouchEnded = [this](Touch* touch, Event  *event)
    {
        onTouchEnd();
        onSelectEnd(touch->getLocation());
    };
    
    mEventListenerMove->onTouchCancelled = [this](Touch* touch, Event  *event)
    {
        onTouchEnd();
        onSelectEnd(touch->getLocation());
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mEventListenerMove, this);
}

void UIMediaSelectLayer::onSelectBegan(Point p)
{
    mTouchSelectPoint = p;
    mIsSelect = true;
    
    UIMediaSelectItemLayer *sprite;
    if (getSpriteForPoint(p, sprite))
    {
        if (sprite != mSelectMediaItem && mSelectMediaItem)
        {
            mSelectMediaItem->onSelectLeave();
        }
        
        mSelectMediaItem = sprite;
        mSelectMediaItem->onSelect();
    }
}

void UIMediaSelectLayer::onSelectMove(Point p)
{
    Rect rect(mTouchSelectPoint.x - 100, mTouchSelectPoint.y - 100, 200, 200);
    if (!rect.containsPoint(p))
    {
        mIsSelect = false;
    }
    
    UIMediaSelectItemLayer *sprite;
    if (getSpriteForPoint(p, sprite))
    {
        if (sprite != mSelectMediaItem && mSelectMediaItem)
        {
            mSelectMediaItem->onSelectLeave();
        }
        
        mSelectMediaItem = sprite;
        mSelectMediaItem->onSelect();
    }
}

void UIMediaSelectLayer::onSelectEnd(Point p)
{
    UIMediaSelectItemLayer *sprite;
    if (getSpriteForPoint(p, sprite))
    {
        if (sprite != mSelectMediaItem && mSelectMediaItem)
        {
            mSelectMediaItem->onSelectLeave();
        }
        
        sprite->onSelectLeave();
        if (mIsSelect)
        {
            sprite->selectThis();
        }
    }
    mSelectMediaItem = nullptr;
    setOkButtonStatas();
}

void UIMediaSelectLayer::onTouchEnd()
{
    Size size = mMoveLayer->getContentSize();
    Point p = mMoveLayer->getPosition();
    
    float time = 0.3f;
    if (p.y < getSizeWin().height || size.height < getSizeWin().height)
    {
        mMoveLayer->runAction(Sequence::create(MoveTo::create(time, Point(0, getSizeWin().height)), NULL));
    }
    else if (p.y > size.height + 200)
    {
        mMoveLayer->runAction(Sequence::create(MoveTo::create(time, Point(0, size.height + 200)), NULL));
    }
}

bool UIMediaSelectLayer::getSpriteForPoint(Point p, UIMediaSelectItemLayer *&sprite)
{
    Vector<Node *> &nodes = mMoveLayer->getChildren();
    Point realP = p - mMoveLayer->getPosition();
    for (auto it : nodes)
    {
        UIMediaSelectItemLayer *s = static_cast<UIMediaSelectItemLayer*>(it);
        if (s->getBoundingBox().containsPoint(realP))
        {
            sprite = s;
            return true;
        }
    }
    
    return false;
}

void UIMediaSelectLayer::setOkButtonStatas()
{
    mSelectSprites.clear();
    
    Vector<Node *> &nodes = mMoveLayer->getChildren();
    for (auto it : nodes)
    {
        UIMediaSelectItemLayer *s = static_cast<UIMediaSelectItemLayer*>(it);
        if (s->mIsSelect)
        {
            mSelectSprites.push_back(s);
        }
    }
    
    if (mSelectSprites.size() > 0)
    {
        CocosHelper::getWidgetByName(mLayout, "Panel_ok")->setTouchEnabled(true);
        CocosHelper::getWidgetByName(mLayout, "Panel_ok")->setColor(Color3B::GREEN);
    }
    else
    {
        CocosHelper::getWidgetByName(mLayout, "Panel_ok")->setTouchEnabled(false);
        CocosHelper::getWidgetByName(mLayout, "Panel_ok")->setColor(Color3B::RED);
    }
}














