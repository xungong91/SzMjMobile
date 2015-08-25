//
//  MetroTouchManage.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/16.
//
//

#ifndef __SzMjMobile__MetroTouchManage__
#define __SzMjMobile__MetroTouchManage__

#include "cocos2d.h"
#include "BaseMetroSprite.h"
#include "MetroSpriteManage.h"
#include "TaskMetroChildManager.h"

USING_NS_CC;

class MetroTouchManage
{
public:
    MetroTouchManage();
    ~MetroTouchManage();
    void setInfo(Node *mainNode, EventDispatcher *eventDispatcher, Node *moveLayer, MetroSpriteManage *metroSpriteManage);
    void setInfo(Node *mainNode, EventDispatcher *eventDispatcher, Node *moveLayer, TaskMetroChildManager *metroSpriteManage);
    
    void setTouchMove();
    void setTouchChange();
private:
    Node *mMoveLayer;
    BaseMetroSprite *mSelectMetroSprite;
    Node *mMainNode;
    EventDispatcher *mEventDispatcher;
    MetroSpriteManage *mMetroSpriteManage;
    TaskMetroChildManager *mMetroChildManager;
    
    //滑动
    EventListenerTouchOneByOne *mEventListenerMove;
    //拖动
    EventListenerTouchOneByOne *mEventListenerChange;
    
    //选择
    void onSelectBegan(Point p);
    void onSelectEnd(Point p);
    void onTouchEnd();
    
    //返回选择到的精灵
    bool getSpriteForPoint(Point p, BaseMetroSprite *&sprite);
    //返回相对于movelayer的point
    Point getPointForMove(Point p);
};

#endif /* defined(__SzMjMobile__MetroTouchManage__) */
