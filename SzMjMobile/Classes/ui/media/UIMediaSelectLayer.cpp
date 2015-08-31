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
#include "UIMainLayer.h"
#include "UIWidgetMsgSprite.h"

UIMediaSelectLayer *UIMediaSelectLayer::gUIMediaSelectLayer = nullptr;

UIMediaSelectLayer::UIMediaSelectLayer()
: mSelectMediaItem(nullptr)
, mSelectCallFunc(nullptr)
, mMaxSelectCount(9)
{
    gUIMediaSelectLayer = this;
}

UIMediaSelectLayer::~UIMediaSelectLayer()
{
    gUIMediaSelectLayer = nullptr;
}

bool UIMediaSelectLayer::init()
{
    if (!UIBaseLayer::init())
    {
        return false;
    }
    
    mLayout = CocosHelper::singleton()->getScaleLayout("CCS_mediaSelect.csb", this);
    CocosHelper::getNodeByName(mLayout, "Image_bg")->setZOrder(1);
    
    addPanelTouch(static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Button_cencel")), [this]()
                  {
                      this->getParent()->removeChild(this);
                  });
    
    addPanelTouch(static_cast<Layout*>(CocosHelper::getNodeByName(mLayout, "Button_ok")), [this]()
                  {
                      vector<UIImageStruct> types;
                      for (int i = 0; i < mSelectSprites.size(); ++i)
                      {
                          types.push_back(mSelectSprites[i]->getType());
                      }
                      
                      if (mSelectCallFunc)
                      {
                          mSelectCallFunc(types);
                      }
                      else
                      {
                          auto layer = UIMediaLayer::create();
                          layer->setMediaInfo(types);
                          
                          UIImageStruct imageStruct = mSelectSprites[0]->getType();
                          if(imageStruct.type == UIMediaType::image)
                          {
                              string filePath = imageStruct.file;
                              ((UIModelAddLayer*)this->getParent())->AddImage(filePath);
                          }
                          else if(imageStruct.type == UIMediaType::video)
                          {
                              ((UIModelAddLayer*)this->getParent())->AddVideo(imageStruct);
                          }
                      }
                      
                      this->getParent()->removeChild(this);
                  });
    
    mMoveLayer = Layer::create();
    mMoveLayer->setAnchorPoint(Point(0, 1));
    mMoveLayer->setPosition(Point(0, getSizeWin().height - 215));
    CocosHelper::getNodeByName(mLayout, "Panel")->addChild(mMoveLayer);
    
    int cardCount = 37;
    
    mMoveLayer->setContentSize(Size(0, (cardCount / 3) * 360 + (cardCount % 3 == 0 ? 0 : 360)));
    
    for (int i = 0; i < cardCount; ++i)
    {
        if (i == cardCount - 1)
        {
            auto video = UIMediaSelectItemLayer::create();
            video->setResInfo(__String::createWithFormat("card/vdo%d.mp4", 0)->getCString(), UIMediaType::video);
            Point p = Point(i % 3 * 360, -(int)(i / 3) * 360 - 360);
            video->setPosition(p);
            mMoveLayer->addChild(video);
        }
        else
        {
            auto item = UIMediaSelectItemLayer::create();
            item->setResInfo(__String::createWithFormat("card/img%d.jpg", i)->getCString(), UIMediaType::image);
            Point p = Point(i % 3 * 360, -(int)(i / 3) *360 - 360);
            item->setPosition(p);
            mMoveLayer->addChild(item);
        }
    }
    
    setOkButtonStatas();
    
    if(UIMainLayer::gUIMainLayer)
    {
        UIMainLayer::gUIMainLayer->addChild(this, 10);
    }
    
    return true;
}

void UIMediaSelectLayer::setSelectCallFunc(function<void (vector<UIImageStruct> files)> func)
{
    mSelectCallFunc = func;
}

void UIMediaSelectLayer::onEnter()
{
    UIBaseLayer::onEnter();
    
    mEventListenerMove = EventListenerTouchOneByOne::create();
    mEventListenerMove->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        mTouchStartPoint = touch->getLocation();
        if (mTouchStartPoint.y > 1705)
        {
            return false;
        }
        
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
    
    _eventDispatcher->addEventListenerWithFixedPriority(mEventListenerMove, -1);
}

void UIMediaSelectLayer::onExit()
{
    _eventDispatcher->removeEventListener(mEventListenerMove);
    UIBaseLayer::onExit();
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
            if (mSelectSprites.size() >= mMaxSelectCount && !sprite->mIsSelect)
            {
                UIWidgetMsgSprite::setMsg(__String::createWithFormat("最多选择%d张照片", mMaxSelectCount)->getCString());
            }
            else
            {
                sprite->selectThis();
            }
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
    if (p.y < getSizeWin().height - 215 || size.height < getSizeWin().height - 215)
    {
        mMoveLayer->runAction(Sequence::create(MoveTo::create(time, Point(0, getSizeWin().height - 215)), NULL));
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
    
    static_cast<Text*>(CocosHelper::getNodeByName(mLayout, "Text_count"))->setString(__String::createWithFormat("%lu", mSelectSprites.size())->getCString());
    
    if (mSelectSprites.size() > 0)
    {
        CocosHelper::getWidgetByName(mLayout, "Button_ok")->setTouchEnabled(true);
    }
    else
    {
        CocosHelper::getWidgetByName(mLayout, "Button_ok")->setTouchEnabled(false);
    }
}














