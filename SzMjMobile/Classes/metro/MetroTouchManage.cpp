//
//  MetroTouchManage.cpp
//  SzMjMobile
//
//  Created by gongxun on 15/8/16.
//
//

#include "MetroTouchManage.h"
#include "XHelper.h"

MetroTouchManage::MetroTouchManage()
: mSelectMetroSprite(nullptr)
, mEventListenerMove(nullptr)
, mEventListenerChange(nullptr)
{
    
}

MetroTouchManage::~MetroTouchManage()
{
    
}

void MetroTouchManage::setInfo(Node *mainNode, EventDispatcher *eventDispatcher, Node *moveLayer, MetroSpriteManage *metroSpriteManage)
{
    mMainNode = mainNode;
    mEventDispatcher = eventDispatcher;
    mMoveLayer = moveLayer;
    mMetroSpriteManage = metroSpriteManage;
    
    //移动
    static Point gTouchStartPoint = Point::ZERO;
    static Point gMoveLayerStartPoint = mMoveLayer->getPosition();
    
    mEventListenerMove = EventListenerTouchOneByOne::create();
    mEventListenerMove->retain();
    mEventListenerMove->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        gTouchStartPoint = touch->getLocation();
        gMoveLayerStartPoint = mMoveLayer->getPosition();
        
        onSelectBegan(gTouchStartPoint);
        return true;
    };
    
    mEventListenerMove->onTouchMoved = [this](Touch* touch, Event  *event)
    {
        Point local = touch->getLocation();
        float offsetx = local.x - gTouchStartPoint.x;
        mMoveLayer->setPosition(gMoveLayerStartPoint + Point(offsetx, 0));
        
        
        onSelectBegan(local);
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

    //拖动
    static Point gChangeSpriteStartPoint = Point::ZERO;
    static Point gChangeStartPoint = Point::ZERO;
    static BaseMetroSprite *gChangeSprite = nullptr;
    
    mEventListenerChange = EventListenerTouchOneByOne::create();
    mEventListenerChange->retain();
    mEventListenerChange->onTouchBegan = [this](Touch* touch, Event  *event)
    {
        gChangeSprite = nullptr;
        gChangeStartPoint = touch->getLocation();
        if (getSpriteForPoint(gChangeStartPoint, gChangeSprite))
        {
            gChangeSpriteStartPoint = gChangeSprite->getPosition();
            gChangeSprite->setZOrder(1);
            
            mMetroSpriteManage->setChangeUpdataStart(getPointForMove(touch->getLocation()), gChangeSprite);
            return true;
        }
        else
        {
            return false;
        }
    };
    
    mEventListenerChange->onTouchMoved = [this](Touch* touch, Event  *event)
    {
        Point local = touch->getLocation();
        gChangeSprite->setPosition(gChangeSpriteStartPoint + local - gChangeStartPoint);
        
        Point realP = getPointForMove(local);
        mMetroSpriteManage->setChangeUpdata(realP, gChangeSprite);
    };
    
    mEventListenerChange->onTouchEnded = [this](Touch* touch, Event  *event)
    {
        Point realP = getPointForMove(touch->getLocation());
        mMetroSpriteManage->resetUpdata();
        gChangeSprite->setZOrder(0);
        
        mMetroSpriteManage->setChangeUpdataEnd(realP, gChangeSprite);
    };
    
    mEventListenerChange->onTouchCancelled = [this](Touch* touch, Event  *event)
    {
        Point realP = getPointForMove(touch->getLocation());
        mMetroSpriteManage->resetUpdata();
        gChangeSprite->setZOrder(0);
        
        mMetroSpriteManage->setChangeUpdataEnd(realP, gChangeSprite);
    };
}

void MetroTouchManage::setTouchMove()
{
    mEventDispatcher->removeEventListener(mEventListenerMove);
    mEventDispatcher->removeEventListener(mEventListenerChange);
    
    mEventDispatcher->addEventListenerWithSceneGraphPriority(mEventListenerMove, mMainNode);
}

void MetroTouchManage::setTouchChange()
{
    mEventDispatcher->removeEventListener(mEventListenerMove);
    mEventDispatcher->removeEventListener(mEventListenerChange);
    
    mEventDispatcher->addEventListenerWithSceneGraphPriority(mEventListenerChange, mMainNode);
}

bool MetroTouchManage::getSpriteForPoint(Point p, BaseMetroSprite *&sprite)
{
    Vector<Node *> &nodes = mMoveLayer->getChildren();
    Point realP = getPointForMove(p);
    for (auto it : nodes)
    {
        BaseMetroSprite *s = static_cast<BaseMetroSprite*>(it);
        if (s->getBoundingBox().containsPoint(realP))
        {
            sprite = s;
            return true;
        }
    }
    
    return false;
}

Point MetroTouchManage::getPointForMove(Point p)
{
    return p - mMoveLayer->getPosition();
}

void MetroTouchManage::onSelectBegan(Point p)
{
    BaseMetroSprite *sprite;
    if (getSpriteForPoint(p, sprite))
    {
        if (sprite != mSelectMetroSprite && mSelectMetroSprite)
        {
            mSelectMetroSprite->onSelectLeave();
        }
        
        mSelectMetroSprite = sprite;
        mSelectMetroSprite->onSelect();
    }
}

void MetroTouchManage::onSelectEnd(Point p)
{
    BaseMetroSprite *sprite;
    if (getSpriteForPoint(p, sprite))
    {
        if (sprite != mSelectMetroSprite && mSelectMetroSprite)
        {
            mSelectMetroSprite->onSelectLeave();
        }
        
        sprite->onSelectLeave();
    }
    mSelectMetroSprite = nullptr;
}

void MetroTouchManage::onTouchEnd()
{
    Size size = mMoveLayer->getContentSize();
    Point p = mMoveLayer->getPosition();
    
    float time = 0.3f;
    if (p.x > 0 || size.width < getSizeWin().width)
    {
        mMoveLayer->runAction(Sequence::create(MoveTo::create(time, Point::ZERO), NULL));
    }
    else if (getSizeWin().width - p.x > size.width)
    {
        mMoveLayer->runAction(Sequence::create(MoveTo::create(time, Point(getSizeWin().width - size.width, 0)), NULL));
    }
}











